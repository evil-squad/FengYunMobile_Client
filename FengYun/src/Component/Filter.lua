--
-- Author: MokyLin Bluce Nong <nongjinxia@mokylin.com>
-- Date: 2017-02-15 20:51:25
--

local _M = {}

local filters = {}

local function fastRemove(t, v)
   for i = 1, #t do
      if t[i] == v then
         t[i] = t[#t]
         t[#t] = nil
         return
      end
   end
end

function _M.registerFilter(name, filter)
   local fs = filters[name]
   if not fs then
      fs = {}
      filters[name] = fs
   end
   fs[#fs+1] = filter
end

function _M.unregisterFilter(name, filter)
   local fs = filters[name]
   if fs then
      if filter then
         fastRemove(fs, filter)
         if #fs == 0 then
            filters[name] = nil
         end
      else
         filters[name] = nil
      end
   end
end

function _M.checkFilter(name)
   local fs = filters[name]
   if fs then
      for _, checker in ipairs(fs) do
         if not checker() then
            return false
         end
      end
   end
   return true
end

return _M
