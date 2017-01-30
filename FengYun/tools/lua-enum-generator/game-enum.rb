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
	end

	output("../../src/GameConstants.lua")
end