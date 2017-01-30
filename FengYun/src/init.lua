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
	local bg = cc.Sprite:create("ui/bg.png")
	bg:setPosition(cc.p(size.width * 0.5, size.height * 0.5))
	win:addChild(bg)

	win:setAnchorPoint(cc.p(0.5, 0.5))
	win:setPosition(cc.p(uirect.width * 0.5, uirect.height * 0.5))
	uilayer:addChild(win)

	local tip = cc.Label:createWithSystemFont("点击屏幕继续", "Helvetica", "24")
	tip:setPosition(cc.p(size.width * 0.5, size.height * 0.5))
	win:addChild(tip)
	tip:setColor(cc.c3b(0, 255, 0))

	local s1 = cc.ScaleTo:create(0.5, 1.5)
	local s2 = cc.ScaleTo:create(0.5, 1.0)
	local seq = cc.Sequence:create(s1, s2)
	tip:runAction(cc.RepeatForever:create(seq))

	local function onTouchBegan(touch, event)
		game.sendEvent("goto_game_scene")
		return true
	end

	local listener = cc.EventListenerTouchOneByOne:create()
   listener:setSwallowTouches(true)
   listener:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCH_BEGAN )
   win:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, win)
end

main()