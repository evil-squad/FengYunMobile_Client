--
-- Author: MokyLin Bluce Nong <nongjinxia@mokylin.com>
-- Date: 2017-02-03 01:32:15
--

require "Component.Buttons"
local timer = require "Component.Timer"
local Utils = require "Component.Utils"

require "DebugUtils"

local grey = cc.c4b(120, 120, 120, 255)
local white = cc.c4b(255, 255, 255, 255)

local function clamp(v, min, max)
	if v < min then return min end
	if v > max then return max end
	return v
end

local function addButtonInputEvent(input)
	game.addGameInputEvent(game.INPUT_EVENT_TYPE_BUTTON_EVENT, input[1], input[3])
end

local function registerKeyBoard(self, buttons)
	local keyMap = 
	{
	   ["KEY_J"] = "Jump",
	   ["KEY_K"] = "Attack",
	   ["KEY_P"] = "Anger",
	   ["KEY_U"] = "Skill1",
	   ["KEY_I"] = "Skill2",
	   ["KEY_O"] = "Skill3",
	   ["KEY_B"] = "Skill4",
	   ["KEY_N"] = "Skill5",
	   ["KEY_M"] = "Skill6"
	}

	local function onKeyPressed(keyCode, event)
		local k = cc.KeyCodeKey[keyCode + 1]
		local key = keyMap[k]
		if key then
			buttons[key][2] = true
			addButtonInputEvent(buttons[key])
		end
	end

	local function onKeyReleased(keyCode, event)
		local key = keyMap[cc.KeyCodeKey[keyCode + 1]]
		if key then
			buttons[key][2] = false
			addButtonInputEvent(buttons[key])
		end
	end

	local listener = cc.EventListenerKeyboard:create()
	listener:registerScriptHandler(onKeyPressed, cc.Handler.EVENT_KEYBOARD_PRESSED)
	listener:registerScriptHandler(onKeyReleased, cc.Handler.EVENT_KEYBOARD_RELEASED)

	self:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, self)
end

local function createActionButton(shallow, onPress)
	local function onPress_(btn, pressed)
		onPress(pressed)
		if pressed then
			btn:setScale(0.95)
		else
			btn:setScale(1)
		end
	end
	return createButton(shallow, onPress_, nil)
end

local function pForAngle(a)
	return { x = math.cos(math.rad(a)), y = math.sin(math.rad(a)) }
end

local function createSkillDish(buttons, skillDefs)
	local radius = 120
	local anglePerSkill = 60

	local minVaildTouchDist = 80
	local maxVaildTouchDist = 230

	local size = cc.size((120 + 40) * 2, (120 + 40) * 2 + 10)
	local center = cc.p(size.width * 0.5, size.height * 0.5)
	local clipRect = cc.rect(center.x - 257, center.y - 77, 269, 341)
	local respRect = cc.rect(center.x - 257, center.y - 77, 322, 312)

	local node = cc.ClippingNode:create()
	node:setAnchorPoint(cc.p(0.5, 0.5))
	node:setContentSize(size)

	local drawNode = cc.DrawNode:create()
	local drawPos = {
		cc.p(0, 0),
		cc.p(size.width / 3, 0),
		cc.p(size.width * 2 / 3, size.height),
		cc.p(0, size.height)
	}

	drawNode:drawSolidPoly(drawPos, 4, cc.c4f(1, 1, 1, 1))

	node:setStencil(drawNode)

	local anchor = cc.Node:create()

	local function onClick(btn, skillDef)
		local loc = node:convertToNodeSpace(anchor:convertToWorldSpace(cc.p(btn:getPosition())))

		if cc.rectContainsPoint(respRect, loc) then
			buttons[skillDef[1]][2] = true
			addButtonInputEvent(buttons[skillDef[1]])
			local action = cc.Sequence:create(
				cc.DelayTime:create(0.5),
				cc.CallFunc:create(function()
					buttons[skillDef[1]][2] = false
					addButtonInputEvent(buttons[skillDef[1]])
				end)
			)
			node:runAction(action)
		end
	end

	local btns = {}
	local btn, p
	local majPadSkill, minPadSkill = false, false
	for i, v in ipairs(skillDefs) do
		btn = createScaleButton(false, 0.95, function(btn) onClick(btn, v) end)
		local _, memb = initButtonWithImageAndLabel(btn, "actionpad/skill_btn.png", "11", "fonts/cd.fnt", 20)
		btn.sprite = memb.sprite
		btn.label = memb.label

		btn.label:setLocalZOrder(2)
		btn.onClick = function() onClick(btn, v) end

		local btnSize = btn:getContentSize()
		-- local greyBtn = 
		p = pForAngle(- (i - 1) * anglePerSkill + 180)
		btn:setPosition(cc.p(cc.pMul(p, radius)))
		anchor:addChild(btn)
		btns[#btns + 1] = btn

		if v[3] == 0 then
			btn.sprite:setOpacity(77)
			btn.label:setVisible(false)
			btn:setEnabled(false)
		else
			if i < 4 then
				minPadSkill = true
			else
				majPadSkill = true
			end

			local size = btn.sprite:getContentSize()
			local icon = cc.Sprite:create("skill/spell_icon_100215.png")
			icon:setPosition(cc.p(size.width * 0.5, size.height * 0.5))
			icon:setScaleX(0.9)
			icon:setScaleY(0.9)
			icon:setOpacity(255 * 0.75)
			btn.icon = icon
			btn:addChild(icon)

			local mask = cc.ProgressTimer:create(cc.Sprite:create("actionpad/cd_mask.png"))
			mask:setType(cc.PROGRESS_TIMER_TYPE_RADIAL)
			mask:setPosition(cc.p(size.width * 0.5, size.height * 0.5))
			btn.cdMask = mask
			btn:addChild(mask)

			btn.cdMask:setVisible(false)
		end
	end

	local function setAnchorRotation(rotation)
		anchor:setRotation(rotation)
		for _, v in ipairs(btns) do
			v:setRotation(-rotation)
		end
	end

	local maxRotation = -38
	local stepRotation = anglePerSkill * 3
	local minRotation = maxRotation - (math.ceil(#skillDefs / 3) - 1) * stepRotation
	local initRotation = rememberedSkillDishAngle and rememberedSkillDishAngle or (maxRotation - stepRotation)
	if not (majPadSkill and minPadSkill) then
		if majPadSkill then
			initRotation = maxRatation - stepRotation
		elseif minPadSkill then
			initRotation = maxRotation
		end
	end

	rememberedSkillDishAngle = initRotation
	anchor:setRotation(initRotation)
	for _, v in ipairs(btns) do
		v:setRotation(-initRotation)
	end

	local action = cc.RotateTo:create(0.3, initRotation)
	local seq = cc.Sequence:create(cc.DelayTime:create(0.2), action)
	anchor:runAction(seq)

	anchor:setPosition(center)
	node:addChild(anchor)

	local beganRotation, beganTime, lastPos
	local canTouch = true
	local beganTouch = nil
	local function onTouchBegan(touch, event)
		if not canTouch then return false end
		local target = event:getCurrentTarget()
		local location = target:convertToNodeSpace(touch:getLocation())
		local dist = cc.pGetDistance(center, location)
		if location.x < 210 and (dist > minVaildTouchDist and dist < maxVaildTouchDist) and beganTouch == nil then
			lastPos = cc.pSub(location, center)
			beganRotation = anchor:getRotation()
			beganTime = timer.getTime()
			anchor:stopAllActions()
			if beganTouch == nil then beganTouch = touch end
			return true
		end
		return false
	end

	local function onTouchMoved(touch, event)
	end

	local function onTouchEnded(touch, event)
	end

	local listener = cc.EventListenerTouchOneByOne:create()
	listener:setSwallowTouches(true)
	listener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN)
	listener:registerScriptHandler(onTouchMoved, cc.Handler.EVENT_TOUCH_MOVED)
	listener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
	node:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, node)

	local function onUpdate(dt)

	end

	node:scheduleUpdateWithPriorityLua(onUpdate, 1)

	return node
end

local function createAngerButton(angerId, onPress)
	local size = cc.size(102, 123)

	local btn = createActionButton(true, onPress)
	btn:setContentSize(size)

	local icon = cc.Sprite:create("actionpad/anger_btn_bg.png")

	btn:addChild(icon)

	return btn
end

function openActionPad()
	local uirect = game.getUIRect()

	local size = cc.size(276, 294)
	local pos = cc.p(uirect.width, 0)

	local buttons = {}

	local panel = gui.Panel:create(pos.x, pos.y, size.width, size.height, 1)
	panel:setAnchorPoint(cc.p(1, 0))

	local skillDefs = {
		{ "Skill1", "skill/spell_icon_100215.png", 1 },
		{ "Skill2", "skill/spell_icon_100215.png", 1 },
		{ "Skill3", "skill/spell_icon_100215.png", 1 },
		{ "Skill4", "skill/spell_icon_100215.png", 1 },
		{ "Skill5", "skill/spell_icon_100215.png", 1 },
		{ "Skill6", "skill/spell_icon_100215.png", 1 }
	}

	local skillDish = createSkillDish(buttons, skillDefs)
	skillDish:setAnchorPoint(cc.p(0.5, 0.5))
	skillDish:setPosition(cc.p(size.width - 160, 140))
	panel:addChild(skillDish)

	local function onAttackPress(pressed)
		buttons["Attack"][2] = pressed
		addButtonInputEvent(buttons["Attack"])
	end

	local aImage = cc.Sprite:create("actionpad/soldier_attack_btn.png")
	local attackBtn = createActionButton(true, onAttackPress)
	initButtonWithSprite(attackBtn, aImage)

	attackBtn:setPosition(cc.p(size.width - 30, 30))
	attackBtn:setAnchorPoint(cc.p(1, 0))
	panel:addChild(attackBtn)

	local function onAngerPress(pressed)
		buttons["Anger"][2] = pressed
		addButtonInputEvent(buttons["Anger"])
	end

	local angerBtn = createAngerButton(0, onAngerPress)
	angerBtn:setPosition(cc.p(size.width - 30, 376))
	panel:addChild(angerBtn)

	local platform = cc.Application:getInstance():getTargetPlatform()
	if platform == cc.PLATFORM_OS_MAC or platform == cc.PLATFORM_OS_WINDOWS then
		registerKeyBoard(panel, buttons)
	end

	local buttonDefs = {
		"Jump",
		"Attack",
		"Anger",
		"Skill1",
		"Skill2",
		"Skill3",
		"Skill4",
		"Skill5",
		"Skill6"
	}

	for _, v in ipairs(buttonDefs) do
		buttons[v] = { game.getInputButtonId(v), false }
		addButtonInputEvent(buttons[v])
	end

	-- debugDraw(panel)

	game.getUILayer():addChild(panel)
end























