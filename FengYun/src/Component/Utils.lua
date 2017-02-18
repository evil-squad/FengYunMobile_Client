--
-- Author: MokyLin Bluce Nong <nongjinxia@mokylin.com>
-- Date: 2017-01-17 10:16:50
--

local Layout = require "Component.Layout"
local ScrollView = require "Component.ScrollView"
local timer = require "Component.Timer"
local Filter = require "Component.Filter"

local _M = {}

function _M.formatNumber(n)
	local str = string.format("%d", n)
	local len = #str
	local rest = len % 3

	local t = {}
	if rest ~= 0 then t[#t + 1] = string.sub(str, 1, rest) end

	local offset = rest + 1
	while offset + 2 <= len do
		t[#t + 1] = string.sub(str, offset, offset + 2)
		offset = offset + 3
	end

	return table.concat(t, ",")
end

function _M.formatAsset(n)
	local str = string.format("%d", n)
	local len = #str
	if len > 5 then
		if len > 8 then
			local w = tonumber(string.sub(str, len - 7, len - 4))
			if w == 0 then
				return string.format("%d亿", string.sub(str, 1, len - 8))
			else
				return string.format("%d亿%d万", string.sub(str, 1, len-8), w)
			end
		else
			return string.sub(str, 1, len-4).."万"
		end
	else
		return _M.formatNumber(n)
	end
end

function _M.formatDate(second)
	return os.date("%F", second)
end

function _M.formatTime(seconds)
	local s = seconds % 60
	local m = math.floor((seconds / 60)) % 60
	local h = math.floor((seconds / 3600)) % 24
	return string.format("%02d:%02d:%02d", h, m, s)
end

return _M






