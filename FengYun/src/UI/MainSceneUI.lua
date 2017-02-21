--
-- Author: MokyLin Bluce Nong <nongjinxia@mokylin.com>
-- Date: 2017-02-18 16:41:31
--

local function getRes(path)
	return "mainSceneUI/" .. path
end

local function createHeroInfoPanel()
	local size = cc.size(100, 100)
	local panel = gui.Panel:create(0, 0, size.width, size.height)

	local heroInfoBg = cc.Sprite:create(getRes("hero_info_bg.png"))
	heroInfoBg:setPosition(cc.p(0, size.height))
	heroInfoBg:setAnchorPoint(cc.p(0, 1))
	panel:addChild(heroInfoBg)

	return panel
end


function openMainSceneUI()
	local uirect = game.getUIRect()
	local uilayer = game.getUILayer()

	local heroPanel = createHeroInfoPanel()
	heroPanel:setPosition(cc.p(0, uirect.height))
	heroPanel:setAnchorPoint(cc.p(0, 1))
	uilayer:addChild(heroPanel)
end