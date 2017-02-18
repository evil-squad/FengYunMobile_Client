# -*- coding: utf-8 -*-
Builder.define do
	namespace "gui" do
		enum WindowType do
			value FLOAT
			value FIXED
		end
	end

	namespace "game" do
		enum Result do
      value SUCCESS
      value NO_USER_ERROR
      value USER_NAME_EXISTS
      value WRONG_USER_PASSWORD
      value USER_PROHIBIT
      value NO_ROLE_ERROR
      value ROLE_NAME_EXISTS
      value NETWORK_ERROR
      value UNKNOW_ERROR
      value VERSION_DEBUG_ERROR
      value VERSION_PROTOCOL_ERROR
      value VERSION_PROTOCOL_WRONG
      value VERSION_RESOURCE_WRONG
    end
    
		enum InputEventType do
			value AXIS_EVENT, 1
			value BUTTON_EVENT
		end

		enum JoystickDir do
			value NONE, 0
			value FRONT
			value RIGHT_DOWN
			value RIGHT
			value RIGHT_UP
			value BACK
			value LEFT_UP
			value LEFT
			value LEFT_DOWN
		end
	end

	output("../../src/GameConstants.lua")
end