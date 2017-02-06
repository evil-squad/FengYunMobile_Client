--
-- Author: MokyLin Bluce Nong <nongjinxia@mokylin.com>
-- Date: 2017-02-04 21:56:31
--

local _M = {}

local scheduler = cc.Director:getInstance():getScheduler()

local handle
local time = 0

local function update(dt)
end

function _M.init()
	if not handle then
		time = 0
		handle = scheduler:sheduleScriptFunc(update, 0, false)
	end
end

function _M.release()
	if handle then
		scheduler:unscheduleScriptEntry(handle)
		handle = nil
	end
end

function _M.getTime()
	return time
end

return _M