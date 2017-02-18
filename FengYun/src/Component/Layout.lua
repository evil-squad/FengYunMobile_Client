--
-- Author: MokyLin Bluce Nong <nongjinxia@mokylin.com>
-- Date: 2017-02-15 20:39:11
--

local _M = {}

local UI_ACTION_DELAY_TIME = 0.03
local UI_ACTION_RUN_TIME = 1500
local function getOffsets(offsets)
   if offsets == nil then
      return 0, 0
   else
      return offsets.col or 0, offsets.row or 0
   end
end

local function getPads(pads)
   if pads == nil then
      return 0, 0, 0, 0
   else
      return pads.left or 0, pads.right or 0, pads.top or 0, pads.bottom or 0
   end
end

function _M.createHBox(nodes, offset, pads, align)
   if align == nil then align = "center" end

   local container = cc.Node:create()

   local width , height = 0, 0
   local rowXs = {}

   if offset == nil then offset = 0 end

   local x, size = 0
   for i, node in ipairs(nodes) do
      size = node:getContentSize()

      rowXs[i] = x + size.width * 0.5
      x = x + size.width + offset

      width = width + size.width
      if size.height > height then height = size.height end
   end

   local padLeft, padRight, padTop, padBottom = getPads(pads)

   width = width + padLeft + padRight + (#nodes-1) * offset

   local offsetY = 0
   if align == "center" then
      offsetY = height/2
   elseif align == "top" then
      offsetY = height
   elseif align == "down" then
      offsetY = 0
   end

   for i, node in ipairs(nodes) do
      node:setPosition(padLeft + rowXs[i], padBottom + offsetY)
      node:setTag(i)
      container:addChild(node)
   end

   height = height + padTop + padBottom
   container:setContentSize(cc.size(width, height))

   function container:getElement(idx)
      return nodes[idx]
   end

   function container:getElementCount()
      return #nodes
   end

   function container:runUIAction(type)
      if type == "tip" then
         for i,node in ipairs(nodes) do
            local s = node:getContentSize()
            local p = cc.p(node:getPosition())
            local distance = width + s.width*i
            node:setPosition(p.x + distance, p.y)

            local callback = node.actionCallback
            local seq = cc.Sequence:create(cc.DelayTime:create(i * UI_ACTION_DELAY_TIME),
               cc.EaseSineOut:create(cc.MoveBy:create(distance / UI_ACTION_RUN_TIME, cc.p(-distance, 0))),
               cc.CallFunc:create(function ()
                  if callback then callback() end
            end))
            node:runAction(seq)
         end
      elseif type == "stick" then
         for i,node in ipairs(nodes) do
            local s = node:getContentSize()
            local p = cc.p(node:getPosition())
            local distance = height
            node:setPosition(p.x, p.y + distance)

            local callback = node.actionCallback
            local seq = cc.Sequence:create(cc.DelayTime:create(i * UI_ACTION_DELAY_TIME),
               cc.EaseBackOut:create(cc.MoveBy:create(distance / UI_ACTION_RUN_TIME, cc.p(0, -distance))),
               cc.CallFunc:create(function ()
                  if callback then callback() end
            end))
            node:runAction(seq)
         end
      end
   end

   return container
end

function _M.createVBox(nodes, offset, pads, align)
   if align == nil then align = "center" end

   local container = cc.Node:create()

   local width, height = 0, 0
   local rowYs = {}

   if offset == nil then offset = 0 end

   local y, size = 0

   local padLeft, padRight, padTop, padBottom = getPads(pads)

   local function setNodesPos()
      width, height = 0, 0
      y, size = 0, nil
      for i, node in ipairs(nodes) do
         size = node:getContentSize()

         rowYs[i] = y - size.height * 0.5
         y = y - size.height - offset

         if size.width > width then width = size.width end
         height = height + size.height
      end

      height = height + padTop + padBottom + (#nodes-1) * offset

      for i, node in ipairs(nodes) do
          node:setAnchorPoint(cc.p(0.5,0.5))
         local alignPos = 0
         if align == "center" then
            alignPos = width/2
         elseif align == "left" then
            alignPos = node:getContentSize().width/2
         else
            alignPos = width-node:getContentSize().width/2
         end

         node:setPosition(padLeft + alignPos, height - padTop + rowYs[i])
         node:setTag(i)
         if not node:getParent() then
            container:addChild(node)
         end
      end

      width = width + padLeft + padRight
      container:setContentSize(cc.size(width, height))
   end

   setNodesPos()

   function container:getElement(idx)
      return nodes[idx]
   end

   function container:getElementCount()
      return #nodes
   end
   
   function container:addElement(e, pos)
      if pos == nil or pos < 1 then pos = #nodes+1 end
      if pos > #nodes + 1 then pos = #nodes + 1 end
      table.insert(nodes, pos, e)
      setNodesPos()
   end

   function container:removeElement(pos)
      for i, v in ipairs(nodes) do
         if i==pos then
            v:removeFromParent()
            table.remove(nodes, i)
            break
         end
      end

      setNodesPos()
   end

   function container:runUIAction(type)
      if type == "tip" then
         for i,node in ipairs(nodes) do
            local s = node:getContentSize()
            local p = cc.p(node:getPosition())
            local distance = height + s.height*i

            node:setPosition(p.x, p.y - distance)

            local callback = node.actionCallback
            local seq = cc.Sequence:create(cc.DelayTime:create(i * UI_ACTION_DELAY_TIME),
               cc.EaseSineOut:create(cc.MoveBy:create(distance / UI_ACTION_RUN_TIME, cc.p(0, distance))),
               cc.CallFunc:create(function ()
                  if callback then callback() end
            end))
            node:runAction(seq)
         end
      elseif type == "stick" then
         for i,node in ipairs(nodes) do
            local s = node:getContentSize()
            local p = cc.p(node:getPosition())
            local distance = width
            node:setPosition(p.x + distance, p.y)

            local callback = node.actionCallback
            local seq = cc.Sequence:create(cc.DelayTime:create(i * UI_ACTION_DELAY_TIME),
               cc.EaseBackOut:create(cc.MoveBy:create(distance / UI_ACTION_RUN_TIME, cc.p(-distance, 0))),
               cc.CallFunc:create(function ()
                  if callback then callback() end
            end))
            node:runAction(seq)
         end
      end
   end

   return container
end

function _M.createTBox(type, rows, cols, nodes, offsets, pads, direction)
   local calcXY
   if type == "row" then
      calcXY = function (i) return (i-1) % cols + 1, math.ceil(i / cols) end
   elseif type == "column" then
      calcXY = function (i) return math.ceil(i / rows), (i-1) % rows + 1 end
   else
      error("Unsupport Table Box type!")
   end

   local container = cc.Node:create()

   local width, height = 0, 0
   local colWidths, rowHeights = {}, {}

   local x, y, size
   for i, node in ipairs(nodes) do
      x, y = calcXY(i)
      size = node:getContentSize()
      if colWidths[x] == nil then colWidths[x] = 0 end
      if colWidths[x] < size.width then colWidths[x] = size.width end
      if rowHeights[y] == nil then rowHeights[y] = 0 end
      if rowHeights[y] < size.height then rowHeights[y] = size.height end
   end

   local colXs, rowYs = { 0 }, { 0 }
   local offsetX, offsetY = getOffsets(offsets)

   x, y = 0, 0
   for i, v in ipairs(colWidths) do
      colXs[i] = x + v * 0.5
      x = x + v + offsetX
      width = width + v
   end
   if direction == "up" then
      for i, v in ipairs(rowHeights) do
         rowYs[i] = y + v * 0.5
         y = y + v + offsetY
         height = height + v
      end
   else
      for i, v in ipairs(rowHeights) do
         rowYs[i] = y - v * 0.5
         y = y - v - offsetY
         height = height + v
      end
   end

   local padLeft, padRight, padTop, padBottom = getPads(pads)

   width = width + padLeft + padRight + (#colWidths-1) * offsetX
   height = height + padTop + padBottom + (#rowHeights-1) * offsetY

   local baseVal = direction == "up" and padBottom or height - padTop
   for i, node in ipairs(nodes) do
      x, y = calcXY(i)
      node:setPosition(padLeft + colXs[x], baseVal + rowYs[y])
      node:setTag(i)
      container:addChild(node)
   end

   container:setContentSize(cc.size(width, height))

   function container:getElement(idx)
      return nodes[idx]
   end

   return container
end

return _M
