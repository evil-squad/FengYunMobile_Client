--
-- Author: MokyLin Bluce Nong <nongjinxia@mokylin.com>
-- Date: 2017-01-17 10:09:12
--
local Utils = require "Component.Utils"
local scheduler = cc.Director:getInstance():getScheduler()
local _M = {}

local function IsLocationInNode(node, loc)
	local pos = node:convertToNodeSpace(loc)
	local s = node:getContentSize()
	local rect = cc.rect(0, 0, s.width, s.height)
	local ret = cc.rectContainsPoint(rect, pos)
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

	local beganPoint
	local handle

	function releaseHandle(handle)
		if handle then
			scheduler:unscheduleScriptEntry(handle)
			handle = nil
			return true
		else
			return false
		end
	end

	local function onTouchBegan(touch, event)
		if not btn.enabled then return false end

		local target = event:getCurrentTarget()
		if not target:isVisible() then return false end

		local location = touch:getLocation()

		if IsLocationInNode(target, location) then
			beganPoint = location
			if onPress then onPress(btn, true) end

			return true
		end
		return false
	end

	local function onTouchMoved(touch, event)
		local location = touch:getLocation()
		if not IsLocationInNode(event:getCurrentTarget(), location) then
			releaseHandle(handle)
		end
	end

	local function onTouchEnded(touch, event)
		local target = event:getCurrentTarget()
		local location = touch:getLocation()

		if onPress then onPress(btn, false) end

		releaseHandle(handle)
		local d = cc.pGetDistance(location, beganPoint)
		if d < 30 then
			local pos = target:convertToWorldSpace(cc.p(0, 0))
			local size = target:getContentSize()
			if onClick then onClick(btn) end
		end
	end

	local function onTouchCancelled(touch, event)
		releaseHandle(handle)
	end

	local listener = cc.EventListenerTouchOneByOne:create()
	listener:setSwallowTouches(swallow)
	listener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN)
	listener:registerScriptHandler(onTouchMoved, cc.Handler.EVENT_TOUCH_MOVED)
	listener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
	listener:registerScriptHandler(onTouchCancelled, cc.Handler.EVENT_TOUCH_CANCELLED)
	btn:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, btn)

	function btn:isEnabled()
		return self.enabled
	end

	function btn:setEnabled(enabled)
		self.enabled = enabled
	end

	function btn:setOnClick(oc)
		onClick = oc
	end

	btn:setEnabled(true)
	return btn
end

local function initButtonWithNode(btn, node)
	local size = node:getContentSize()
	node:setPosition(size.width * 0.5, size.height * 0.5)
	btn:addChild(node)
	btn:setContentSize(size)
	return true
end

local function initButtonWithSprite(btn, sprite)
	local succ = initButtonWithNode(btn, sprite)
	return succ, { sprite = sprite }
end

local function initButtonWithSpriteAndLabel(btn, sprite, text, font, fontSize, fontColor)
	local label = cc.Label:createWithTTF(text, font, fontSize)
	label:enableShow()

	local size = sprite:getContentSize()
	sprite:setPosition(size.width * 0.5, size.height * 0.5)
	btn:addChild(sprite)
	label:setPosition(cc.p(size.width * 0.5, size.height * 0.5))
	if fontColor then label:setColor(fontColor) end
	btn:addChild(label)
	btn:setContentSize(size)

	return true, { sprite = sprite, label = label }
end

local function initButtonWithImage(btn, imgName)
	return initButtonWithSprite(btn, cc.Sprite:create(imgName))
end

local function initButtonWithSpriteFrameName(btn, imgName)
	return initButtonWithSprite(btn, cc.Sprite:createWithSpriteFrameName(imgName))
end

local function initButtonWithLabel(btn, labelText, font, fontSize, fontColor)
	local label = cc.Label:createWithTTF(labelText, font, fontSize)
	label:enableShadow()
	if fontColor then label:setColor(fontColor) end
	local succ = initButtonWithNode(btn, label)
	return succ, { label = label }
end

local function initButtonWithImageAndLabel(btn, imgName, labelText, font, fontSize, fontColor)
	local sprite = cc.Sprite:create(imgName)
	local label = cc.Label:createWithTTF(labelText, font, fontSize)
	label:enableShadow()

	local size = sprite:getContentSize()
	sprite:setPosition(cc.p(size.width * 0.5, size.height * 0.5))
	btn:addChild(sprite)
	label:setPosition(cc.p(size.width * 0.5, size.height * 0.5))
	if fontColor then label:setColor(fontColor) end
	btn:addChild(label)
	btn:setContentSize(size)

	return true, { sprite = sprite, label = label }
end

local function initButtonWithImageAndBmfLabel(btn, imgName, labelText, font)
	local sprite = cc.Sprite:create(imgName)
	local label = cc.Label:createWithBMFont(font, labelText)
	label:enableShadow()

	local size = sprite:getContentSize()
	sprite:setPosition(cc.p(size.width * 0.5, size.height * 0.5))
	btn:addChild(sprite)
	label:setPosition(cc.p(size.width * 0.5, size.height * 0.5))
	btn:addChild(label)
	btn:setContentSize(size)
	return true, { sprite = sprite, label = label }
end

local function createScaleButton(swallow, scale, onClick)
	local function onPress(btn, pressed)
		if pressed then
			btn:setScale(scale)
		else
			btn:setScale(1)
		end
	end
	return createButton(swallow, onPress, onClick)
end

local function createImageButton(swallow, normalImg, pressedImg, onClick)
	local sprite

	local function onPressed(btn, pressed)
		if pressed then
			sprite:setTexture(pressedImg)
		else
			sprite:setTexture(normalImg)
		end
	end

	local btn = createButton(swallow, onPress, onClick)
	local _, members = initButtonWithImage(btn, normalImg)
	sprite = members.sprite
	return btn
end

local function createImageTurnButton(swllow, normaObj, turnObj, onClicked)
	-- local normalImg, isTurn = nil, false

	-- local normalImg, normalScale = normalObj, 1
	-- local turnImg, turnScale = turnObj, 1

	-- if type(normlaObj) == "table" then
	-- 	normalImg = normalObj.img
	-- 	if normalObj.scale ~= nil then normalScale = normalObj.sale end
	-- end
end

_M.IsLocationInNode = IsLocationInNode
_M.createButton = createButton
_M.createScaleButton = createScaleButton
_M.initButtonWithImage = initButtonWithImage
_M.initButtonWithNode = initButtonWithNode
_M.initButtonWithSprite = initButtonWithSprite
_M.initButtonWithSpriteAndLabel = initButtonWithSpriteAndLabel
_M.initButtonWithLabel = initButtonWithLabel
_M.initButtonWithSpriteFrameName = initButtonWithSpriteFrameName
_M.initButtonWithImageAndLabel = initButtonWithImageAndLabel
_M.initButtonWithImageAndBmfLabel = initButtonWithImageAndBmfLabel
_M.createImageButton = createImageButton
_M.createTouchMaskNode = createTouchMaskNode
_M.createImageTurnButton = createImageTurnButton

-- register to global
for k, v in pairs(_M) do
	_G[k] = v
end

return _M

