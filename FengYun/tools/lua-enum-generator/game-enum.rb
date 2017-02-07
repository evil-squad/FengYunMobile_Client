# -*- coding: utf-8 -*-
Builder.define do
	namespace "gui" do
		enum WindowType do
			value FLOAT
			value FIXED
		end
	end

	namespace "game" do
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