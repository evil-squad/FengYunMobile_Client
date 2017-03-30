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
