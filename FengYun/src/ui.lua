--
-- Author: MokyLin Bluce Nong <nongjinxia@mokylin.com>
-- Date: 2017-01-30 18:10:38
--
require "UI.Joystick"

local function main()
	collectgarbage("collect")
	collectgarbage("setpause", 100)
	collectgarbage("setstepmul", 5000)

	local function enterCityScene()
		openJoystick()
	end

	local function leaveCityScene()
	end

	game.registerEvent("enter_city_scene", enterCityScene)
	game.registerEvent("leave_city_scene", leaveCityScene)
end

main()