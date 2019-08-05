# Start
点兔主题的综合小程序

这是一个综合小程序，包含以下几个部分：
Start：主窗口模块
Notepad：记事本，窗口大小固定为1000*600，支持各种基本功能，关联文件类型，以及简易的二进制文件查看与修改（无对照）和编码切换
Tools：悬浮插件，允许多种样式设置，支持简易的截图、便签、计时、录音等功能
Lock：加解密程序，允许进行基本的加解密操作，以及查看指定文件的散列值
Desktop：桌面图标插件，可以在桌面上悬浮一系列小图标，并为图标进行基本设置
该程序会写入注册表信息，但卸载时可以完全清除。

项目说明：文件夹名称和各模块对应，Notepad和Lock中各有1和2个dll工程，因为这两个模块的部分功能需要dll实现。该项目用到了非常多的图片资源，下载时请保证图片资源的完整性，否则可能无法编译成功
项目结构：
        |--Notepad--FileReadAndWrite
        |          
        |--Tools
 start--|        |--LockSimple
        |--Lock--|  
        |        |--LockNormal
        |--Desktop
