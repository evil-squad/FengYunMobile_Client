--
-- Author: MokyLin Bluce Nong <nongjinxia@mokylin.com>
-- Date: 2017-02-15 20:42:05
--

local Layout = require "Component.Layout"

local UI_ACTION_DELAY_TIME = 0.05
local UI_ACTION_RUN_TIME = 2000
local _M = {}

local function getRes(path)
   return "common/"..path
end


local function createSprite(path, anchorPos, pos, parent)
   local sp = cc.Sprite:create(path)
   if anchorPos then sp:setAnchorPoint(anchorPos) end
   if pos then sp:setPosition(pos) end
   if parent then parent:addChild(sp) end
   return sp
end

local function createHScrollView(size, nodes, arrowOffset, offset, pads, actionType)
   if arrowOffset == nil then arrowOffset = 0 end
   local node = cc.Node:create()
   node:setContentSize(size)

   local leftArrow = nil
   local rightArrow = nil

   local container = Layout.createHBox(nodes, offset, pads)

   local scrollView = cc.ScrollView:create()
   scrollView:setDirection(cc.SCROLLVIEW_DIRECTION_HORIZONTAL)
   scrollView:setViewSize(size)
   scrollView:setContainer(container)
   scrollView:setContentOffset(cc.p(0,0))
   scrollView:setBounceable(false)
   scrollView:setName("ScrollView")

   local function addArrow()
      leftArrow = cc.Node:create()
      leftArrow:setPosition(cc.p(-arrowOffset, size.height*0.5 ))
      leftArrow:setRotation(90)
      node:addChild(leftArrow,1)

      rightArrow = cc.Node:create()
      rightArrow:setPosition(cc.p(size.width + arrowOffset, size.height*0.5))
      rightArrow:setRotation(-90)
      node:addChild(rightArrow,1)

      function node:replaceArrow_(arrowIconPath)
         leftArrow:removeAllChildren()
         rightArrow:removeAllChildren()

         local leftIcon = createSprite(arrowIconPath)
         leftArrow:addChild(leftIcon)
         leftIcon:runAction(cc.RepeatForever:create(cc.Sequence:create(cc.EaseIn:create(cc.MoveBy:create(0.6, cc.p(0, -10)), 0.8),
                                                                     cc.DelayTime:create(0.2),
                                                                     cc.EaseIn:create(cc.MoveBy:create(0.6, cc.p(0, 10)), 0.8),
                                                                     cc.DelayTime:create(0.2))))

         local rightIcon = createSprite(arrowIconPath)
         rightArrow:addChild(rightIcon)
         rightIcon:runAction(cc.RepeatForever:create(cc.Sequence:create(cc.EaseIn:create(cc.MoveBy:create(0.6, cc.p(0, -10)), 0.8),
                                                                      cc.DelayTime:create(0.2),
                                                                      cc.EaseIn:create(cc.MoveBy:create(0.6, cc.p(0, 10)), 0.8),
                                                                      cc.DelayTime:create(0.2))))
      end
      node:replaceArrow_(getRes("arrow_icon.png"))

      function node:setSound(sound_)
          node.sound = sound_
      end
      node:setSound("sounds/ui/fanye.mp3")

      local isSound = false
      local function scrollViewDisScroll()
         leftArrow:setVisible(true)
         rightArrow:setVisible(true)

         if scrollView:minContainerOffset().x >= scrollView:getContentOffset().x then
            rightArrow:setVisible(false)
         elseif scrollView:maxContainerOffset().x <= scrollView:getContentOffset().x then
            leftArrow:setVisible(false)
         end

         if node.sound then
             if scrollView:isDragging() and not isSound then
                 isSound = true
                 game.playSound(node.sound)
             elseif scrollView:isTouchMoved() and isSound then
             elseif isSound then
                 isSound = false
             end
         end
      end

      scrollView:setDelegate()
      scrollView:registerScriptHandler(scrollViewDisScroll, cc.SCROLLVIEW_SCRIPT_SCROLL)

      scrollViewDisScroll()
   end

   if container:getContentSize().width > size.width then
      addArrow()
   end

   function node:setClippingToBounds(val)
      scrollView:setClippingToBounds(val)
   end

   function node:replaceArrow(arrowIconPath)
      if node.replaceArrow_ then
         self:replaceArrow_(arrowIconPath)
      end
   end

   function node:getArrow()
      return leftArrow, rightArrow
   end

   function node:runUIAction(type, startIdx, endIdx)
      if not startIdx or startIdx < 1 then startIdx = 1 end
      if not endIdx or endIdx > #nodes then endIdx = #nodes end

      local node
      local actionIdx = 1
      if type == "tip" then
         for i,node in ipairs(nodes) do
            node = nodes[i]
            local s = node:getContentSize()
            local p = cc.p(node:getPosition())
            local distance = size.width + s.width*i
            node:setPosition(p.x + distance, p.y)

            local callback = node.actionCallback
            local seq = cc.Sequence:create(cc.DelayTime:create(i * UI_ACTION_DELAY_TIME),
               cc.EaseSineOut:create(cc.MoveBy:create(distance / UI_ACTION_RUN_TIME, cc.p(-distance, 0))),
               cc.CallFunc:create(function ()
                  if callback then callback() end
            end))
            node:runAction(seq)
            actionIdx = actionIdx + 1
         end
      elseif type == "stick" then
         for i,node in ipairs(nodes) do
            node = nodes[i]
            local s = node:getContentSize()
            local p = cc.p(node:getPosition())
            local distance = size.height
            node:setPosition(p.x, p.y + distance)

            local callback = node.actionCallback
            local seq = cc.Sequence:create(cc.DelayTime:create(i * UI_ACTION_DELAY_TIME),
               cc.EaseBackOut:create(cc.MoveBy:create(distance / UI_ACTION_RUN_TIME, cc.p(0, -distance))),
               cc.CallFunc:create(function ()
                  if callback then callback() end
            end))
            node:runAction(seq)
            actionIdx = actionIdx + 1
         end
      end
   end
   node:runUIAction(actionType or "tip")

   function node:setTouchEnabled(b)
      scrollView:setTouchEnabled(b)
   end

   function node:setContentOffset(contentOffset, animated)
      scrollView:setContentOffset(contentOffset, animated)
   end

   function node:setViewSize(size)
      local cursize = self:getContentSize()
      self:setContentSize(size)
      scrollView:setViewSize(size)
   end

   function node:setViewSizeScrollView(size)
      scrollView:setViewSize(size)
   end

   function node:setContainerSize(size)
      scrollView:setContentSize(size)
      scrollView:setContentOffset(cc.p(0, 0))
   end

   function node:getContainerSize()
      return container:getContentSize()
   end

   function node:getContentOffset()
      return scrollView:getContentOffset()
   end

   function node:resetContainer(nodes, offset)
      container = Layout.createHBox(nodes, offset)
      scrollView:setContainer(container)

      if container:getContentSize().width > size.width then
         addArrow()
      end
   end

   function node:resetContainerNode(node, offset)
      if container ~= node then
         container = node
         scrollView:setContainer(container)

         if container:getContentSize().width > size.width then
            addArrow()
         end
      end
   end

   function node:minContainerOffset()
      return scrollView:minContainerOffset()
   end

   node:addChild(scrollView)
   return node
end

-- type = "vertical" or "horizontal"
function _M.create(type, size, nodes, arrowOffset, offset, pads, align, actionType)
   if type == "horizontal" then return createHScrollView(size, nodes, arrowOffset, offset, pads, actionType) end

   local callback1 = nil
   if arrowOffset == nil then arrowOffset = 0 end
   local node = cc.Node:create()
   node:setContentSize(size)

   local container = Layout.createVBox(nodes, offset, pads, align, ancho)
   local scrollView = cc.ScrollView:create()
   scrollView:setDirection(cc.SCROLLVIEW_DIRECTION_VERTICAL)
   scrollView:setViewSize(size)
   scrollView:setContainer(container)
   scrollView:setContentOffset(scrollView:minContainerOffset())
   scrollView:setBounceable(false)
   scrollView:setName("ScrollView")

   local upArrow = cc.Node:create()
   upArrow:setPosition(cc.p(size.width*0.5, size.height + arrowOffset))
   upArrow:setName("upArrow")
   upArrow:setScaleY(-1)
   node:addChild(upArrow,1)

   local downArrow = cc.Node:create()
   downArrow:setPosition(cc.p(size.width*0.5, -arrowOffset))
   downArrow:setName("downArrow")
   node:addChild(downArrow,1)

   function node:replaceArrow_(arrowIconPath)
      upArrow:removeAllChildren()
      downArrow:removeAllChildren()

      local upIcon = createSprite(arrowIconPath)
      upArrow:addChild(upIcon)
      upIcon:runAction(cc.RepeatForever:create(cc.Sequence:create(cc.EaseIn:create(cc.MoveBy:create(0.6, cc.p(0, -10)), 0.8),
                                                                   cc.DelayTime:create(0.2),
                                                                   cc.EaseIn:create(cc.MoveBy:create(0.6, cc.p(0, 10)), 0.8),
                                                                   cc.DelayTime:create(0.2))))

      local downIcon = createSprite(arrowIconPath)
      downArrow:addChild(downIcon)
      downIcon:runAction(cc.RepeatForever:create(cc.Sequence:create(cc.EaseIn:create(cc.MoveBy:create(0.6, cc.p(0, -10)), 0.8),
                                                                   cc.DelayTime:create(0.2),
                                                                   cc.EaseIn:create(cc.MoveBy:create(0.6, cc.p(0, 10)), 0.8),
                                                                   cc.DelayTime:create(0.2))))
   end
   node:replaceArrow_(getRes("arrow_icon.png"))

   function node:setSound(sound_)
       node.sound = sound_
   end
   node:setSound("sounds/ui/fanye.mp3")

   local isSound = false
   local function scrollViewDisScroll()
      if scrollView:getContentSize().height > scrollView:getViewSize().height then
         upArrow:setVisible(true)
         downArrow:setVisible(true)
         if scrollView:minContainerOffset().y >= scrollView:getContentOffset().y  then
            upArrow:setVisible(false)
         elseif scrollView:maxContainerOffset().y <= scrollView:getContentOffset().y then
            downArrow:setVisible(false)
         end
      else
         upArrow:setVisible(false)
         downArrow:setVisible(false)
      end

      if node.sound then
          if scrollView:isDragging() and not isSound then
              isSound = true
              game.playSound(node.sound)
          elseif scrollView:isTouchMoved() and isSound then
          elseif isSound then
              isSound = false
          end
      end
   end

   scrollView:setDelegate()
   scrollView:registerScriptHandler(scrollViewDisScroll, cc.SCROLLVIEW_SCRIPT_SCROLL)

   scrollViewDisScroll()

   function node:setClippingToBounds(val)
      scrollView:setClippingToBounds(val)
   end
   
   function node:replaceArrow(arrowIconPath)
      if node.replaceArrow_ then
         self:replaceArrow_(arrowIconPath)
      end
   end

   function node:runUIAction(type, startIdx, endIdx)
      if not startIdx or startIdx < 1 then startIdx = 1 end
      if not endIdx or endIdx > #nodes then endIdx = #nodes end

      local node
      local actionIdx = 1
      if type == "tip" then
         for i = startIdx, endIdx do
            node = nodes[i]
            local s = node:getContentSize()
            local p = cc.p(node:getPosition())
            local distance = size.height + s.height*actionIdx

            node:setPosition(p.x, p.y - distance)

            local callback = node.actionCallback
            local seq = cc.Sequence:create(cc.DelayTime:create(actionIdx * UI_ACTION_DELAY_TIME),
               cc.EaseSineOut:create(cc.MoveBy:create(distance / UI_ACTION_RUN_TIME, cc.p(0, distance))),
               cc.CallFunc:create(function ()
                  if callback then callback() end
                  if callback1 then
                     callback1()
                     callback1 = nil
                  end
            end))
            node:runAction(seq)
            actionIdx = actionIdx + 1
         end
      elseif type == "stick" then
         for i = startIdx, endIdx do
            node = nodes[i]
            local s = node:getContentSize()
            local p = cc.p(node:getPosition())
            local distance = size.width
            node:setPosition(p.x + distance, p.y)

            --local callback = node.actionCallback
            local seq = cc.Sequence:create(cc.DelayTime:create(actionIdx * UI_ACTION_DELAY_TIME),
               cc.EaseBackOut:create(cc.MoveBy:create(distance / UI_ACTION_RUN_TIME, cc.p(-distance, 0))),
               cc.CallFunc:create(function ()
                  if callback then callback() end
                  if callback1 then
                     callback1()
                     callback1 = nil
                  end
            end))
            node:runAction(seq)
            actionIdx = actionIdx + 1
         end
      end
   end
   node:runUIAction(actionType or "tip")

   function node:setTouchEnabled(b)
      scrollView:setTouchEnabled(b)
   end

   function node:resetContainer(nodes, offset, pads)
      container = Layout.createVBox(nodes, offset, pads)
      scrollView:setContainer(container)
      scrollView:setContentOffset(scrollView:minContainerOffset())
      scrollViewDisScroll()
   end

   function node:getContainer()
      return container
   end

   function node:setViewSize(size)
      local cursize = self:getContentSize()
      self:setContentSize(size)
      scrollView:setViewSize(size)
      scrollView:setContentOffset(cc.p(0, scrollView:getContentOffset().y - (cursize.height - size.height)))
      upArrow:setPosition(cc.p(size.width*0.5, size.height + arrowOffset))
      scrollViewDisScroll()
   end

   function node:setContainerSize(size)
      local curContentSize = scrollView:getContentSize()
      scrollView:setContentSize(size)
      scrollView:setContentOffset(cc.p(0, scrollView:getContentOffset().y - (curContentSize.height - size.height)))
      scrollViewDisScroll()
   end

   function node:resetContainerNode(node, offset)
      if container ~= node then
         container = node
         
         scrollView:setContainer(container)
         scrollView:setContentOffset(scrollView:minContainerOffset())
         scrollViewDisScroll()
      end
   end

   function node:getContentOffset()
      return scrollView:getContentOffset()
   end

   function node:isNodeVisible(node)
      return scrollView:isNodeVisible(node)
   end

   function node:setContentOffset(x)
      scrollView:setContentOffset(x)
      scrollViewDisScroll()
   end

   function node:minContainerOffset()
      return scrollView:minContainerOffset()
   end

   function node:maxContainerOffset()
      return scrollView:maxContainerOffset()
   end

   function node:getContainer()
      return scrollView:getContainer()
   end

   function node:addItem(item)
      container:addElement(item)
      scrollViewDisScroll()
   end

   function node:removeItem(pos)
      container:removeElement(pos)
      scrollViewDisScroll()
   end

   function node:setBounceable(isBounce)
       scrollView:setBounceable(isBounce)
   end

   function node:getViewSize()
      return scrollView:getViewSize()
   end

   function node:setCallback1(fun)
      callback1 = fun
   end

   node:addChild(scrollView)
   return node
end

return _M
