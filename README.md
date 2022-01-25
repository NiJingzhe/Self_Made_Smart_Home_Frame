# Self_Made_Smart_Home_Frame

#### 介绍

全栈自建的智能家庭框架

#### 实现原理
##### 一、服务端
1.  首先是建立了`home,device`两个类。`home`含有`device_list`,而`device`则内含自身的`control_type`(这个东西决定了该设备的控制方式)。
2.  在Home Control Center的webapp中选择设备,并更新设备状态后，作为家庭中枢的树莓派向局域网中广播消息，由对应的智能设备认领，并处理命令。
3.  经过以上几个步骤实现前端webapp控制家庭设备的目的。

##### 二、硬件端
1. 抽象出`device`类，类中包括两个udp服务器（发送和接收）,一个命令解析器（`command_processer`），一个ROM（`eeprom`）。
2. 抽象出`set_wifi_service`类，即配网服务器，运行配网界面。
3. 首先，`device`会检查`eeprom`中是否存有已知的WiFi信息，若果有就连上。然后无条件打开AP和配网服务器，为随时可以切换WiFi。然后是设备引脚初始化。接着是用`device`的`bind`函数绑定命令和回调函数。 最后就是在`loop`函数中run起`device`和`service`。
4. `device`的`run`函数中，会监听局域网内的udp数据包，然后按照json格式解包，判断`"device"`属性是否和自己匹配，如果是的那么将`"command"`属性放到`processer`的`process`函数中进行处理，即按照指令在`processer`的`action_list`中找到对应的回调函数并执行，最后构建feedback数据包发送会服务端。

#### 安装教程
暂时没有呢。。。。
1.  xxxx
2.  xxxx
3.  xxxx

#### 使用说明
暂时没有呢。。。。
1.  xxxx
2.  xxxx
3.  xxxx

#### 参与贡献

1. master分支: 倪旌哲(Lil-Dino$aur)


#### 特技(模板自带的我也不知道这是什么。。。。)

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
