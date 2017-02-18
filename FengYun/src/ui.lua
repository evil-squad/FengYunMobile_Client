--
-- Author: MokyLin Bluce Nong <nongjinxia@mokylin.com>
-- Date: 2017-01-30 18:10:38
--
require "UI.Joystick"
require "UI.ActionPad"
require "UI.LoginUI"
require "UI.LoadingUI"

local function registerGameWindowEvent(ev, win_name, onClick, data)
	game.registerEvent(ev, function()

	end)
end

local function main()
	collectgarbage("collect")
	collectgarbage("setpause", 100)
	collectgarbage("setstepmul", 5000)

	local function enterCityScene()
		openJoystick()
		openActionPad()
	end

	local function leaveCityScene()
	end

	game.registerEvent("enter_city_scene", enterCityScene)
	game.registerEvent("leave_city_scene", leaveCityScene)

	game.registerEvent("open_login_ui", openLoginUI)
	game.registerEvent("open_load_scene_ui", openLoadSceneUI)
end

main()