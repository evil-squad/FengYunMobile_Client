# FengYunMobileClient
风云页转手，17888

==============================
文件结构说明
==============================
|- FengYun 
  |- .settings // cocos自动生成文件 
  |- framenworks  
  |- cocos2d-x // cocos2d-x 库目录  
  |- extenal  //工程需要添加的第三方库   
    |- asio //asio异步网络库   
    |- protobuf //google protobuf 库  
  |- runtime-src //cocos2d-x 生成的各个平台工程   
    |- Classes  // 所需要编写的C++文件    
      |- ECS // 角色的封装    
      |- FSM //角色fsm的封装    
      |- GUI //UI底层的封装    
      |- lua //C++绑定到lua    
      |- managers //为各个模块提供数据的封装    
      |- misc //各种杂项    
      |- Net //网络接口的封装    
      |- Scenes //场景部分的封装   
    |- proj.android //android工程目录   
    |- proj.android //Android STD工程目录   
    |- proj.ios_mac //ios与mac工程目录   
    |- proj.linux // linux工程目录   
    |- proj.win32 //win32 工程目录 
  |- res //资源目录 
  |- runtime  
  |- simulator //变异后的debug目录 
  |- src // lua脚本的目录  
    |- app //可忽略  
    |- cocos //cocos2d 的lua脚本目录  
    |- Component //封装的基础，公用组件  
    |- packages //可忽略  |- UI // UI脚本  
    |- config.lua //cocos默认的配置脚本,里面的参数可以修改  
    |- GameConstants.lua //定义的lua的枚举常量值，次文件不可编辑，由根目录的tools lua-enum-genertor 直接脚本生成  
    |- GameUtils.lua //定义一些lua公用的方法  
    |- init.lua //lua的入口文件  
    |- main.lua //可忽略  
    |- ui.lua //UI的入口文件 
  |- tools  
    |- imagesplitter //切割地图的Python脚本，可传参数  
    |- lua-enum-generator //定义lua的枚举变量   
      |- game-enum.rb //定义枚举常量于此   
      |- generator.rb //自动生成lua的常量的命令，自动输出为GameConstants.lua文件 用法：进入本目录， 然后 ./generator.rb game-enum.rb ,然后就会自动生成文件 
    |- .cocos-project.json  // cocos自动生成文件 
    |- .project  // cocos自动生成文件 
    |- config.json // cocos自动生成文件 
    |- MokyLinFengYun.keystore //编译 Android 所需的keystore文件
    
    
-----------------------------------
架构说明
-----------------------------------
1.GameApp 为程序入口
2.GameModule 为各个Manager 的基类
3.GameInput 为遥感输入以及技能的输入，并通过 lua/input.inc.hpp绑定相应的方法到lua脚本
4.GameConfigLoader 为解析策划配置用，以及misc目录下的ConfigReader.h和ConfigReaderPlist.h
5.*Types.h 这类文件主要用来定义各类数据结构，以struct的方式定义，主要是易于公开数据访问
6.LuaHelpUtils.h　封装以及定义了一些C++绑定到lua的方法以及宏定义
7.为了降低耦合，每个模块各自有各自的manager来管理数据，每个模块的网络数据， \
    将继承NetManager的Listener管理网络的监听和Processor管理网络的接收，以及继承RoleManager的Listener，用来管理玩家的数据



----------------------------------
一些命令与工具
----------------------------------
1.切割地图，在tools/imagesplitter下， 用 python imgesplitter.py 进行切割，相应的会有参数说明
2.生成lua的常量文件，在tools/lua-enum-generator 目录下，进入当前目录， 使用 ./gemeratp.rb game-enum.rb  \
    对应的会直接生成在src目录下的GameConstants.lua 的文件
3.使用cocos命令来编译，在工程的根目录，用 cocos compile -p 相应的平台， -m 相应的模式，默认为debug \
    如：cocos compile -p android -m release 表示编译android的版本，相应的是release模式