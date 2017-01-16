--
-- Author: MokyLin Bluce Nong <nongjinxia@mokylin.com>
-- Date: 2017-01-16 10:34:56
--
game = game or {}

local eventHandlers = {}
local textEventHandlers = {}

local function fastRemove(t, v)
	for i = 1, #t do
		if t[i] == v then
			t[i] = t[#t]
			t[#t] = nil
			return
		end
	end
end

function game.getNodeWorldBox(node)
	local size = node:getContentSize()
	local lb = cc.p(0, 0)
	local rt = cc.p(size.width, size.height)
	lb = node:convertToWorldSpace(lb)
	return cc.rect(lb.x, lb.y, rt.x, rt.y)
end

function game.registerEvent(ev, func)
	local t = eventHandlers[ev]
	if not t then
		t = {}
		eventHandlers[ev] = t
		local function onTrigger()
			for _, fun in ipairs(t) do
				fun()
			end
		end
		game.setEventHandler(ev, onTrigger)
	end
	t[#t + 1] = func
end

function game.unregisterEvent(ev, func)
	local t = eventHandlers[ev]
	if t then
		fastRemove(t, func)
		if #t == 0 then
			game.setEventHandler(ev, nil)
			eventHandlers[ev] = nil
		end
	end
end

function game.clearEvent(ev)
	eventHandlers[ev] = nil
end