--
-- Author: BluceNong <nongjinxia@mokylin.com>
-- Date: 2017-01-15 00:03:25
--

require "config"
require "cocos.init"
require "GameUtils"
require "DebugUtils"

local function mergeTable(a, b)
	for k, v in pairs(b) do
		if a[k] == nil then
			a[k] = b[k]
		end
	end
end

local function initPlatForm()
end

local function main()
	if type(COCOS2D_DEBUG) ~= "number" then COCOS2D_DEBUG = 0 end

	DEBUG = COCOS2D_DEBUG

	cc.Director:getInstance():getOpenGLView():setDesignResolutionSize(1136, 640, cc.ResolutionPolicy.FIXED_HEIGHT)
	cc.FileUtils:getInstance():setPopupNotify(false)
	game.registerEvent("open_init_ui", openInitUI)
	game.sendEvent("start_game")
end

function openInitUI()
	local uirect = game.getUIRect()
	local uilayer = game.getUILayer()
	local size = cc.size(uirect.width, uirect.height)
	local win = gui.Panel:create(0, 0, size.width, size.height)
	print("open init ui=======>", tostring(uilayer))
	local bg = cc.Sprite:create("builtin/ui/bg.png")
	bg:setPosition(cc.p(size.width * 0.5, size.height * 0.5))
	win:addChild(bg)

	win:setAnchorPoint(cc.p(0.5, 0.5))
	win:setPosition(cc.p(uirect.width * 0.5, uirect.height * 0.5))
	uilayer:addChild(win)

	rPrint(uirect)
end

main()