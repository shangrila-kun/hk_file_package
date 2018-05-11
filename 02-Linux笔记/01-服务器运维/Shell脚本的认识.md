## Shell脚本

### Shell、内核、操作系统的介绍

![img](https://pic1.zhimg.com/80/416d6b469bda642f1edf7ff56c1aea4d_hd.jpg)

**Shell**

> 一般是指跟用户直接交互的界面，可以是命令行，也可以是窗口，用户通过shell访问并控制计算机。
>
> 对于Windows来说，Shell应该是资源管理器（也就是我的电脑）。
>
> 对于Linux来说，就是命令行。
>
> 系统软件、应用软件和用户通过shell来操纵内核，控制整个计算机硬件。

**内核(**kernel**)**

> 操作系统最核心的部分，一般来说，内核特指某一个或者几个文件。进程管理、进程通信、存储器管理、设备管理、中断处理和时钟管理。

**操作系统（Operating System）**

> 管理和控制计算机硬件与软件资源的计算机程序。

### Shell脚本的介绍

> Shell Script ，Shell脚本与Windows/Dos下的批处理相似，也就是用各类命令预先放入到一个文件中，方便一次性执行的一个程序文件，主要是方便管理员进行设置或者管理用的。

### 脚本

> 脚本简单地说就是一条条的文字命令，这些文字命令是可以看到的（如可以用记事本打开查看、编辑），脚本程序在执行时，是由系统的一个解释器，将其一条条的翻译成机器可识别的指令，并按程序顺序执行。

### 脚本启动方式

**方法一**

> 将脚本作为sh的命令行参数。
>
> sh startsh.sh

**方法二**

> 将脚本作为具有执行权限的可执行文件。
>
> chmod a+x ascript.sh
>
> drwx rwx rwx

###实例

#### Hello,World

~~~shell
#! /bin/bash
echo "Hello,World"
~~~

###语法

####变量

#####局部变量（本地变量）



~~~shell
#！ /bin/bash
name=hk #变量赋值
echo $name
echo ${name}
length=${#name} #获取字符串长度
echo #SHELL


~~~

####数组

~~~shell
#定义数组两种方式：
#第一种
name=(tom lucy lili)#一对括号表示是数组，元素用空格分割，如果是逗号或者其他分割，数组中只有一个元素
#第二种
#直接通过 数组名[下标] 就可以对其进行引用赋值，如果下标不存在，自动添加新一个数组元素
#用${#数组名[@或*]} 可以得到数组长度
#用${数组名[下标]} 下标是从0开始  下标是：*或者@ 得到整个数组内容

#基本数组操作
a=(1 2 3)   ##()表示空数组
echo "所有元素: "${a[@]} #数组
echo "数组长度: "${#a[@]}
#给函数传数组，
function $array #此种方法只会把数组的第一个参数值传给函数，
function $array[*] #此种方法把数组中的所有参数值传给函数
~~~

####数字比较

~~~shell
#!/bin/bash
if [ $1 -gt $2 ]
then echo "参数$1大于参数$2"
else echo "参数$1小于参数$2"
fi
#数字判断一些命令：
#-gt是大于 [greater than]
#-lt是小于 [less than]
#-eq是等于 
#-ne是不等于 [Not equal to]
#-ge是大于等于
#le是小于等于 
~~~

####判断语句

一、单分支if语句

~~~

if 判断条件；then
statement1
statement2
....
fi
~~~

二、双分支语句

~~~
if 判断条件; then
statement1
statement2
...
else
statementN
...
fi
~~~

三、多分支语句

~~~
if 判断条件1；then
statement1
...
elif 判断条件2; then
statement2
...
elif 判断条件3; then
statement3
...
else
statement4
...
fi
~~~

四、case语句

~~~
case 变量 in
PATTERN1)
statement
...
;;
PATTERN2)
statement
... 
;;
*)
statement
...
;;
esac
~~~

####函数和递归函数

~~~shell
#！ /bin/bash
#定义函数方式一
name=hk #全局变量
function print_hello()
{
	local sex="男" #局部变量
	echo $sex #访问局部变量
	echo `date "+%Y-%m-%d  %H-%M-%S"`
    echo "hello"
}
print_hello()
echo $sex #非法访问
~~~

> $name 是第一个参数\$1 ,\$sex是第二个参数\$2,以此内推。

####时间格式

~~~shell
#输出当前日期和时间
date +"%Y-%m-%d %H:%M:%S"
时间搓转datetime格式
date -d @1398004852 +"%Y-%m-%d %H:%M:%S" 
~~~

####递归

~~~

~~~

#### 重定向

在linux脚本中，总是有三个文件处于打开状态，标准输入（键盘输入）、标准输出（输出到屏幕）、标准错误（也是输出到屏幕），他们分别对应的文件描述符是0,1,2.

> **>  默认为标准输出重定向，与 1> 相同2>&1  **意思是把 标准错误输出 重定向到 标准输出.
>
> **&>file**  意思是把**标准输出** 和 **标准错误输出** 都重定向到文件file中
>
> **/dev/null是一个文件，这个文件比较特殊，所有传给它的东西它都丢弃掉**



#### 清空脚本内容

~~~shell
#方法一 通过重定向清空文件内容,即不存在的事物到该文件上。
> filename
#方法二 通过/dev/null设备来清空文件
cat /dev/null > filename
cp /dev/null > filename #cp命令复制/dev/null的内容到某个文件来达到清空该文件的目的。
#方法三 使用echo命令清空文件 可以使用echo命令将空字符串的内容重定向到文件中
echo "" > filename 
echo > access.log


~~~



### 调试

> shell脚本不需要什么特殊的工具。bash本身就包含了一些选项，能够打印出脚本接受的参数和输入。



