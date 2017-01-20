--
-- Author: MokyLin Bluce Nong <nongjinxia@mokylin.com>
-- Date: 2017-01-17 10:09:12
--

local scheduler = cc.Director:getInstance():getScheduler()
local _M = {}

local function IsLocationInNode(node, loc)
	local pos = node:convertToNodeSpace(loc)
	local s = node:getContentSize()
	local rect = cc.rect(0, 0, s.width, s.height)
	local ret = cc.rectContainPoint(rect, pos)
	return ret
end

local function createTouchMaskNode(onTouch)
	local node = cc.Node:create()

	local function onTouchBegan(touch, event)
		local target = event:getCurrentTarget()
		local localtion = touch:getLocation()
		if IsLocationInNode(target, location) then
			if onTouch == nil then
				return true
			else
				return onTouch(location)
			end
		end
		return false
	end

	local listener = cc.EventListenerTouchOneByOne:create()
	listener:setSwallowTouches(true)
	listener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN)
	node:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, node)

	return node
end

local function createButton(swallow, onPress, onClick)
	local btn = cc.Node:create()
	btn:setAnchorPoint(cc.p(0.5, 0.5))
end