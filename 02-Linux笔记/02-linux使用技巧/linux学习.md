# linux基础命令

## 导读

> 程序员在写程序几乎都是面向操作系统的，也可以面向硬件写程序，但是需要辅助写很多底层程序。
>
> os:operating system
>
> 软件程序  通用目的
>
> 		>硬件驱动、进程管理、内存管理、网络管理、安全管理。
>
> > System Call.系统调用。调用操作系统的接口。
>
> > 编程层次：
> >
> > > 硬件规格：hardware specifiacation.面向硬件写，不同厂商可能不一样了
> > >
> > > 系统调用：给的越底层，你可以变化的越多，但离最终需要实现的功能可能需要越多的步骤。
> > >
> > > 给的越高层，你可以变化的越小，但离最终需要实现的功能可能需要的步骤越少。
> > >
> > > 库调用（library call):把非常多得底层功能提取出来，整个成一个离最终功能比较近的一个借口。
>
> CPU架构类型：
>
> > x86  x64 arm(只做设计，不做产品)
>
> 操作系统
>
> > Windows
> >
> > linux :(从哪来，早期只有dos,unix ,apple system，乔布斯从bell lab实验室拿了一份做苹果，微软比尔盖茨从乔布斯手里拿了一版图像界面，做微软)
> >
> > ​	
> >
> > Unix:
> >
> > > System(嫡出 Bell Lab)
> > >
> > > > AIX(IBM)
> > > >
> > > > Solaris(SUN)
> > > >
> > > > HP-UX(HP)
> > >
> > > BSD:Berkeley System distribution（庶出）
> > >
> > > > NetBSD
> > > >
> > > > OpenBSD
> > > >
> > > > FreeBSD

> 计算机的基础知识：
>
> CPU,memory,i/o
>
> 程序运行模式：
>
> > 用户空间：user space, us
> >
> > 内核空间：system space
>
> 编程语言：
>
> > 汇编语言：微码编程  系统中某些与 硬件相关的特有代码，驱动程序开发
> >
> > 高级语言c,c++; 系统级应用、驱动程序
> >
> > 高级应用java,python,php:应用程序。

[先有操作系统，还是先有汇编器？](http://blog.csdn.net/ad_xi/article/details/51783188)

## Linux的发行版

> linux的主流发行版
>
> 
>
> > slackware: suse(商业维护)
> >
> > > opensuse(二次发行版)（华为主要用，欧州主要用）
> >
> > debian:最接近原汁原味的linux，黑客维护，linux中最难的一种
> >
> > > ubuntu(二次发行版)
> >
> > redhat
> >
> > > rhel:redhat enterprise linux(企业版)（每18个月发行一个新版本）
> > >
> > > CentOS:兼容rhel的格式，纯粹是开源社区维护，只要rhel新版本发不来了，CentOS社区一个月后就推出新版本，后来rhel把CentOS招安了，现在由redhat公司服务。服务器建议选择centos或者rhel.

> 补充：android: kernel +busybox+java虚拟机
>
> 问题：CentOS和Linux是什么关系？CentOS和RHEL是什么关系？
>
> 问题：各种开源协议的具体细节？
>
> ​	GPL,LGPL,Apache,BSD

## 程序包管理器

> rpm:
>
> ​	RHEL,Fedora,,CentOs
>
> dpt:
>
> ​	Debian,Ubuntu

## Linux的哲学思想

> 自由软件：
>
> ​	自由使用：自由学习和修改；自由分发：自由创建衍生生版；
>
> 哲学思想：
>
> > 1、一切皆文件；把几乎所有的资源，包括硬件设备都组织为文件格式;
> >
> > 2、由众多单一的小程序组成，一个程序只实现一个功能，而且要做好；组合小程序完成复杂任务；
> >
> > 3、尽量避免跟用户交互；目标在于实现脚本编程，以自动完成某些功能；
> >
> > 4、使用纯文本文件保存配置信息；目标在于一款合用的文本编辑器即能完成系统配置工作；

## 目录相关的命令：

> 当前目录或工作目录
>
> 主目录，家目录：home
>
> root:/root
>
> 普通用户：/home/username
>
> ~:用户的主目录

> cd 或 cd ~：回到当前用户的主目录。
>
> cd ~username:切换到指定目录的主目录
>
> cd -:在上一个目录和当前目录之间来回切换。

> 相关的环境变量：
>
> ​	pwd:保存了当前目录的路径；
>
> ​	OLDPWD:上一次所在目录路径；

> ls：list
>
> ​	显示指定路劲下的文件列表
>
> ​	ls -a, -all :显示所有文件，包括隐藏文件；-l，长格式
>
> drwxrwxr-x. 2 hk hk 32 12月 16 22:32 ccode

> stat  filename  获取指定文件的原数据。

> file查看内容类型相关的命令：file  

> echo 回声定位
>
> echo -n 禁止换行
>
> \t制表符，一个tab键  echo -e:表示允许使用转义符。 echo -e how /tare you 

## 登录关机

>关机：halt,poweroff,shutdown,init 0
>
>重启：reboot,shutdown,init 6

## 跟用户登录相关

> who,whoami,w

