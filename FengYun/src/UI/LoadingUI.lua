--
-- Author: MokyLin Bluce Nong <nongjinxia@mokylin.com>
-- Date: 2017-02-17 21:49:30
--

local function createProgressBar(panel)
	local uirect = game.getUIRect()
	local progressBg = cc.Sprite:create("common/progress_bg.png")
	progressBg:setPosition(cc.p(uirect.width * 0.5, 100))
	panel:addChild(progressBg)

	local sprite = cc.Sprite:create("common/progress_img.png")
	local progressBar = cc.ProgressTimer:create(sprite)
	progressBar:setType(cc.PROGRESS_TIMER_TYPE_BAR)
	progressBar:setMidpoint(cc.p(0, 0))
	progressBar:setBarChangeRate(cc.p(1, 0))
	progressBar:setPosition(cc.p(progressBg:getContentSize().width * 0.5, progressBg:getContentSize().height * 0.5))
	progressBg:addChild(progressBar)

	local a1 = cc.ProgressTo:create(2, 100)
	local a2 = cc.CallFunc:create(function() 
		game.sendEvent("load_scene_ui_done")
	end)

	local seq = cc.Sequence:create(a1, a2)
	progressBar:runAction(seq)
end

function openLoadSceneUI()
	local uirect = game.getUIRect()
	local uilayer = game.getUILayer()
	local panel = gui.Panel:create(0, 0, uirect.width, uirect.height)
	uilayer:addChild(panel)

	local bg = cc.Sprite:create("common/loading_bg.png")
	bg:setPosition(cc.p(uirect.width * 0.5, uirect.height * 0.5))
	bg:setAnchorPoint(cc.p(0.5, 0.5))
	panel:addChild(bg)

	createProgressBar(panel)
end