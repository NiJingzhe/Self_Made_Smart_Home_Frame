# Self_Made_Smart_Family_Frame

#### 介绍

全栈自建的智能家庭框架

#### 实现原理

1.  首先是建立了`home,room,device`三个类。
    `home`含有`room_list`,`room`有`device_list`,而`device`则内涵自身的`control_type`(这个东西决定了该设备的控制方式)
2.  在HHC的webapp中选择房间,设备,并更新设备状态后,作为家庭中枢的树莓派向局域网中广播消息 `{room_name,device_name,state}`,并加入任务队列;由对应的RoomGate(一块arduino)认领,并加入任务队列.
3.  于是RoomGate根据消息,向对应的device_Controller(又是一块arduino)发送状态更新的指令,完成后返回完成消息,RoomGate接收到后更新任务队列并向中枢返回消息.
4.  中枢接收到RoomGate的完成消息后更新任务队列.
5.  经过以上几个步骤实现前端webapp控制家庭设备的目的.

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
