--
-- Author: MokyLin Bluce Nong <nongjinxia@mokylin.com>
-- Date: 2017-01-30 11:46:24
--

local Utils = require "Component.Utils"

local function getRes(path)
	return "joystick/" .. path
end

local ARROW_RADIUS = 55
local MAX_RADIUS = 50
local EXPAND_ARROW_RADIUS = MAX_RADIUS + 10

local ARROW_POSITIONS = 
{
	cc.p(ARROW_RADIUS, 0), --right
	cc.p(0, -ARROW_RADIUS), --down
	cc.p(-ARROW_RADIUS, 0), --left
	cc.p(0, ARROW_RADIUS) --up
}

local function registKeyboard(self, handleInputEvent)
	local inputVector = cc.p(0, 0)
	local function onKeyPressed(keyCode, event)
		local key = cc.KeyCodeKey[keyCode + 1]
		if key == "KEY_W" then
			inputVector.y = 1
		elseif key == "KEY_A" then
			inputVector.x = -1
		elseif key == "KEY_S" then
			inputVector.y = -1
		elseif key == "KEY_D" then
			inputVector.x = 1
		end
		handleInputEvent(inputVector)
	end

	local function onKeyReleased(keyCode, event)
		local key = cc.KeyCodeKey[keyCode + 1]
		if key == "KEY_W" then
			inputVector.y = 0
		elseif key == "KEY_A" then
			inputVector.x = 0
		elseif key == "KEY_S" then
			inputVector.y = 0
		elseif key == "KEY_D" then
			inputVector.x = 0
		end
		handleInputEvent(inputVector)
	end

	local listener = cc.EventListenerKeyboard:create()
	listener:registerScriptHandler(onKeyPressed, cc.Handler.EVENT_KEYBOARD_PRESSED)
	listener:registerScriptHandler(onKeyReleased, cc.Handler.EVENT_KEYBOARD_RELEASED)

	self:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, self)
end

local function createArrow(pos, angle)
	local s = cc.Sprite:create(getRes("arrow.png"))
	s:setAnchorPoint(cc.p(0, 0.5))
	s:setPosition(pos)
	s:setRotation(angle)

	return s
end

local function createJoystickDish(defaultPos, scale)
	local node = cc.Node:create()
	node:setPosition(defaultPos)
	node:setScale(scale)

	local opacity, expandOpacity = 255, 255

	local circle = cc.Sprite:create(getRes("circle.png"))
	circle:setOpacity(opacity)
	node:addChild(circle)

	local arrows = {}
	for i = 1, 4 do
		arrows[i] = createArrow(ARROW_POSITIONS[i], (i - 1) * 90)
		arrows[i]:setOpacity(opacity)
		node:addChild(arrows[i])
	end

	local lightArrow = cc.Sprite:create(getRes("arrow_light.png"))
	lightArrow:setAnchorPoint(cc.p(0, 0.5))
	lightArrow:setVisible(false)
	node:addChild(lightArrow)

	local input = cc.p(0, 0)

	local isStart = false
	function node:start(pos)
		isStart = true

		circle:setOpacity(expandOpacity)
		for i, v in ipairs(arrows) do
			v:setVisible(false)
		end
		self:setFinger(pos)
	end

	function node:stop()
		isStart = false
		self:setPosition(defaultPos)
		input = cc.p(0, 0)
		circle:setOpacity(opacity)
		circle:setPosition(cc.p(0, 0))
		for i, v in ipairs(arrows) do
			v:setVisible(true)
		end
		lightArrow:setVisible(false)
	end

	function node:setFinger(pos)
		if not isStart then return end
		local p = cc.pSub(pos, cc.p(self:getPosition()))
		local len = cc.pGetLength(p)
		local radius = MAX_RADIUS * scale
		if len > radius then
			p = cc.pMul(p, 1 / len)
		else
			p = cc.pMul(p, 1 / radius)
		end

		input = p
		circle:setPosition(cc.pMul(p, MAX_RADIUS / 5))
		if p.x == 0 and p.y == 0 then
			lightArrow:setVisible(false)
		else
			lightArrow:setVisible(true)
			lightArrow:setPosition(cc.pMul(cc.pNormalize(p), EXPAND_ARROW_RADIUS))
			lightArrow:setRotation(-math.deg(cc.pToAngleSelf(p)))
		end
	end

	function node:getInput()
		return input
	end

	return node
end

local function createJoystickPanel(size, respRect, defaultPos, joystickScale)
	local panel = gui.Panel:create(size.width, size.height, 1)

	local dish = createJoystickDish(defaultPos, joystickScale)
	panel:addChild(dish)

	local horizontalId = game.getInputAxisId("Horizontal")
	local verticalId = game.getInputAxisId("Vertical")

	local curVec = {}
	local function addAxisInputEvent(vec)
		if vec.x ~= curVec.x then
			curVec.x = vec.x
			game.addGameInputEvent(game.INPUT_EVENT_TYPE_AXIS_EVENT, horizontalId, vec.x)
		end
		if vec.y ~= curVec.y then
			curVec.y = vec.y
			game.addGameInputEvent(game.INPUT_EVENT_TYPE_AXIS_EVENT, verticalId, vec.y)
		end
	end

	local function onTouchBegan(touch, event)
		local target = event:getCurrentTarget()
		if not dish:isVisible() then return false end
		local loc = target:convertToNodeSpace(touch:getLocation())

		if cc.rectContainsPoint(respRect, loc) then
			dish:start(loc)
			local input = dish:getInput()
			addAxisInputEvent(input)
			return true
		end
		return false
	end

	local function onTouchMoved(touch, event)
		local target = event:getCurrentTarget()
		local loc = target:convertToNodeSpace(touch:getLocation())
		dish:setFinger(loc)
		local input =dish:getInput()
		addAxisInputEvent(input)
	end

	local function onTouchEnded(touch, event)
		dish:stop()
		addAxisInputEvent(cc.p(0, 0))
	end

	local listener = cc.EventListenerTouchOneByOne:create()
	listener:setSwallowTouches(true)
	listener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN )
	listener:registerScriptHandler(onTouchMoved, cc.Handler.EVENT_TOUCH_MOVED )
	listener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED )
	panel:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, panel)

	local platform = cc.Application:getInstance():getTargetPlatform()
	if platform == cc.PLATFORM_OS_MAC or platform == cc.PLATFORM_OS_WINDOWS or platform == cc.PLATFORM_OS_LINUX then
		registKeyboard(panel, addAxisInputEvent)
	end

	addAxisInputEvent(cc.p(0, 0))

	return panel
end

function openJoystick()
	local uirect = game.getUIRect()

	local size = cc.size(uirect.width /2, uirect.height)
	local respRect = cc.rect(0, 0, size.width - 150, size.height - 195)
	local panel = createJoystickPanel(size, respRect, cc.p(160, 180), 1.0)
	panel:setAnchorPoint(cc.p(0, 0))
	panel:setPosition(cc.p(0, 0))

	game.getUILayer():addChild(panel)
end





















