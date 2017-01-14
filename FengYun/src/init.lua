--
-- Author: BluceNong <nongjinxia@mokylin.com>
-- Date: 2017-01-15 00:03:25
--

require "cocos.init"

local function mergeTable(a, b)
	for k, v in pairs(b) do
		if a[k] == nil then
			a[k] = b[k]
		end
	end
end

local function initPlatForm()
end

local function main()
	if type(COCOS2D_DEBUG) ~= "number" then COCOS2D_DEBUG = 0 end

	DEBUG = COCOS2D_DEBUG

	cc.Director::getInstance():getOpenGLView():setDesignResolutionSize(1136, 640, cc.ResolutionPolicy.FIXED_HEIGHT)
	cc.FileUtils:getInstance():setPopupNotify(false)
end

main()