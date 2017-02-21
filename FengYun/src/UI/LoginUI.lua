--
-- Author: MokyLin Bluce Nong <nongjinxia@mokylin.com>
-- Date: 2017-02-15 16:00:41
--

require "Component.Buttons"
local Layout = require "Component.Layout"

local function getRes(path)
	return "login/" .. path
end

local function randomList(list)
	return list[math.random(#list)]
end

local function readNames(fn)
	local array = {}
	local map = cc.FileUtils:getInstance():getValueMapFromFile(fn)
	for _, v in pairs(map) do array[#array + 1] = v end
	return array
end

local HERONAMS = {
	manFirst = readNames("login/man_first_name.plist"),
   manLast = readNames("login/man_last_name.plist"),
   womanFirst = readNames("login/woman_first_name.plist"),
   womanLast = readNames("login/woman_last_name.plist")
}

local function createInputBox(labelText)
	local size = cc.size(300, 50)
	local node = cc.Node:create()
	node:setAnchorPoint(cc.p(0.5, 0.5))
	node:setContentSize(size)

	local bg = ccui.Scale9Sprite:create(cc.rect(10, 10, 64, 64), "common/input_box_bg.png")
	bg:setContentSize(size)
	bg:setPosition(cc.p(size.width * 0.5, size.height * 0.5))
	node:addChild(bg)

	local label = cc.Label:createWithTTF(labelText, "fonts/SimHei.ttf", 22)
	label:setAnchorPoint(cc.p(0, 0.5))
	label:setPosition(cc.p(6, size.height * 0.5))
	node:addChild(label)

	local offset = label:getContentSize().width + 9
	local boxSize = cc.size(size.width - offset, size.height - 10)
	local emptyBg = ccui.Scale9Sprite:create(cc.rect(1, 1, 1, 1), "common/empty.png")
	local box = ccui.EditBox:create(boxSize, emptyBg)
	box:setInputMode(cc.EDITBOX_INPUT_MODE_SINGLELINE)
	box:setAnchorPoint(cc.p(0, 0.5))
	box:setPosition(cc.p(offset, size.height * 0.5))
	node:addChild(box)

	return node, box
end

local function createCreateRolePanel()
	local uirect = game.getUIRect()
	local panel = gui.Panel:create(0, 0, uirect.width, uirect.height)
	local heroNames = {"步惊云", "第二梦", "聂风", "楚楚"}
	local desces = {"我是步惊云", "我是第二梦", "我是聂风", "我是楚楚"}
	local btns = {}
	local tip = cc.Label:createWithTTF("", "fonts/SimHei.ttf", 22)
	tip:setPosition(cc.p(uirect.width * 0.5, 20))
	panel:addChild(tip)

	local index = 1

	local editBg = cc.Sprite:create(getRes("login_kuang_4.png"))
	editBg:setPosition(cc.p(uirect.width * 0.5, 180))
	panel:addChild(editBg)

	local editNode, nameBox = createInputBox(" ")
	editNode:setPosition(cc.p(editBg:getContentSize().width * 0.5 + 70, editBg:getContentSize().height * 0.5))
	editBg:addChild(editNode)

	local function diceClick(btn)
		math.randomseed(os.time())
		local sex = index % 2 == 0 and "woman" or "man"
		local name = randomList(HERONAMS[sex .. "First"]) .. randomList(HERONAMS[sex .. "Last"])
		nameBox:setText(name)
	end

	local function selectHero(btn)
		index = btn:getTag()
		tip:setString("选择了" .. heroNames[index])
		diceClick(diceBtn)
	end
	for i = 1, 4 do
		local btn = createScaleButton(true, 0.95, function(btn) 
			selectHero(btn)
		end)

		initButtonWithImage(btn, string.format("login/hero_%02d.png", i))
		btn:setTag(i)
		local name = cc.Label:createWithTTF(heroNames[i], "fonts/SimHei.ttf", 24)
		local size = btn:getContentSize()
		name:setPosition(cc.p(size.width * 0.5, size.height * 0.5))
		btn:addChild(name)

		local descTip = cc.Label:createWithTTF(desces[i], "fonts/SimHei.ttf", 22)
		descTip:setPosition(cc.p(size.width * 0.5, size.height * 0.5 - 20))
		btn:addChild(descTip)

		btns[#btns + 1] = btn
	end

	local layout = Layout.createHBox(btns, 6)
	layout:setPosition(cc.p(uirect.width * 0.5, uirect.height * 0.5 + 50))
	layout:setAnchorPoint(cc.p(0.5, 0.5))
	panel:addChild(layout)

	local diceBtn = createScaleButton(true, 0.95, diceClick)
	initButtonWithImage(diceBtn, getRes("login_icon_dice.png"))
	diceBtn:setAnchorPoint(cc.p(0.5, 0.5))
	diceBtn:setPosition(cc.p(editBg:getContentSize().width, editBg:getContentSize().height * 0.5))
	editBg:addChild(diceBtn)

	selectHero(btns[1])

	local function enterGameClick(btn)
		game.createRole(nameBox:getText(), index, function(r)
			if r == game.RESULT_SUCCESS then
				game.gotoScene(1, function() 
					print("goto scene------->")
				end)
			else
				print("create role error");
			end
		end)
	end

	local enterBtn = createImageButton(true, "common/btn_red_normal.png", "common/btn_red_normal.png", enterGameClick)
	enterBtn:setPosition(cc.p(uirect.width * 0.5, 100))
	enterBtn:setAnchorPoint(cc.p(0.5, 0.5))
	panel:addChild(enterBtn)

	local enterText = cc.Label:createWithTTF("进入游戏", "fonts/SimHei.ttf", 22)
	enterText:setPosition(cc.p(enterBtn:getContentSize().width * 0.5, enterBtn:getContentSize().height * 0.5))
	enterBtn:addChild(enterText)

	return panel
end

local function updateServerList(callback)
	game.updateServerList(function(result)
		if result == game.RESULT_SUCCESS then
			print("get server list success")
			callback()
		else
			print("get server list failed :", result)
		end
	end)
end

local function createServerList(panel)
	local btns = {}
	local servers = game.getServers()
	local function clickServer(btn)
		panel.serverId = btn:getTag()
	end
	for _, v in ipairs(servers) do
		local btn = createScaleButton(true, 0.95, clickServer)
		local sprite = cc.Sprite:create(getRes("server_name_bg.png"))
		initButtonWithSprite(btn, sprite)
		btn:setTag(v.id)
		local text = cc.Label:createWithTTF(string.format("【第%d区】%s", v.id, v.name), "fonts/SimHei.ttf", 20)
		text:setPosition(cc.p(sprite:getContentSize().width * 0.5, sprite:getContentSize().height * 0.5))
		btn:addChild(text)
		btns[#btns + 1] = btn
	end

	if #btns > 0 then
		local layout = Layout.createVBox(btns, 10)
		layout:setPosition(cc.p(1136 * 0.5, 640 * 0.5))
		layout:setAnchorPoint(cc.p(0.5, 0.5))
		panel:addChild(layout)
		clickServer(btns[1])
	end
end

local function createConnection()
	local uirect = game.getUIRect()
	local uilayer = game.getUILayer()
	local namePanel = gui.Panel:create(0, 0, uirect.width * 0.5, uirect.height * 0.5)
	uilayer:addChild(namePanel)

	local nameNode, nameBox = createInputBox("名字：")
	nameNode:setPosition(cc.p(1136 * 0.5, 170))
	namePanel:addChild(nameNode)
	nameBox:setText(string.format("a%d",math.random(300000)))

	local pswNode, pswBox = createInputBox("密码：")
	pswNode:setPosition(cc.p(1136 * 0.5, 120))
	namePanel:addChild(pswNode)

	local btn = createImageButton(true, "common/btn_red_normal.png", "common/btn_red_pressed.png", function(btn)
		local servers = game.getServers()
		if #servers == 0 then
			print("no server to connect")
			return
		end

		game.setTestUser(nameBox:getText())
		game.connectServer(namePanel.serverId, function(result)
			print("connect to server-->", result, namePanel.serverId)
			if result == game.RESULT_NO_ROLE_ERROR then
				namePanel:removeFromParent()
				local rolePanel = createCreateRolePanel()
				uilayer:addChild(rolePanel)
			elseif result == game.RESULT_SUCCESS then
				game.gotoScene(1, function() 
					print("enter scene------->")
				end)
			end
		end)
	end)
	btn:setPosition(cc.p(1136 * 0.5, 50))
	btn:setAnchorPoint(cc.p(0.5, 0.5))
	namePanel:addChild(btn)

	local text = cc.Label:createWithTTF("登录", "fonts/SimHei.ttf", 24)
	text:setPosition(cc.p(btn:getContentSize().width * 0.5, btn:getContentSize().height * 0.5))
	btn:addChild(text)

	createServerList(namePanel)
end

function openLoginUI()
	local uirect = game.getUIRect()
	local uilayer = game.getUILayer()
	local size = cc.size(uirect.width, uirect.height)

	local bg = cc.Sprite:create("ui/second_bg.png")
	bg:setPosition(cc.p(size.width * 0.5, size.height * 0.5))
	local panel = gui.Panel:create(0, 0, size.width, size.height)
	panel:addChild(bg)
	uilayer:addChild(panel)

	updateServerList(function()
		print("update server list callback")
		createConnection(panel)
	end)
	print("open login ui")
end