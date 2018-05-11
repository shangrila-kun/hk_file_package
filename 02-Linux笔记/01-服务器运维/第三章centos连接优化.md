## centos连接管理及优化

### ssh用法及命令

#### 什么是ssh? 

>~~~
>SSH（Secure Shell Protocol）是一种网络协议，用于计算机之间的加密登录。如果一个用户从本地计算机，使用SSH协议登录另一台远程计算机，我们就可以认为，这种登录是安全的，即使被中途截获，密码也不会泄露。最早的时候，互联网通信都是明文通信，一旦被截获，内容就暴露无疑。1995年，芬兰学者Tatu Ylonen设计了SSH协议，将登录信息全部加密，成为互联网安全的一个基本解决方案，迅速在全世界获得推广，目前已经成为Linux系统的标准配置。
>~~~

#### SSH之所以能够保证安全，原因在于它采用了公钥加密

>~~~
>整个过程是这样的：（1）远程主机收到用户的登录请求，把自己的公钥发给用户。（2）用户使用这个公钥，将登录密码加密后，发送回来。（3）远程主机用自己的私钥，解密登录密码，如果密码正确，就同意用户登录。
>这个过程本身是安全的，但是实施的时候存在一个风险：如果有人截获了登录请求，然后冒充远程主机，将伪造的公钥发给用户，那么用户很难辨别真伪。因为不像https协议，SSH协议的公钥是没有证书中心（CA）公证的，也就是说，都是自己签发的。
>可以设想，如果攻击者插在用户与远程主机之间（比如在公共的wifi区域），用伪造的公钥，获取用户的登录密码。再用这个密码登录远程主机，那么SSH的安全机制就荡然无存了。这种风险就是著名的"中间人攻击"（Man-in-the-middle attack）。
>~~~

#### ssh安装

>~~~
>SSH分客户端openssh-client和openssh-server
>如果你只是想登陆别的机器的SSH只需要安装openssh-client（ubuntu有默认安装，如果没有则sudoapt-get install openssh-client），如果要使本机开放SSH服务就需要安装openssh-server。
>Ubuntu缺省已经安装了ssh client。
>~~~

#### ssh远程登录

##### 口令登录

>> ~~~
>> 假定你要以用户名user，登录远程主机host，只要一条简单命令就可以了。
>>     　　$ ssh user@host  如：ssh pika@192.168.0.111
>> 如果本地用户名与远程用户名一致，登录时可以省略用户名。
>>     　　$ ssh host
>> SSH的默认端口是22，也就是说，你的登录请求会送进远程主机的22端口。使用p参数，可以修改这个端口。
>>     　　$ ssh -p 2222 user@host
>> 上面这条命令表示，ssh直接连接远程主机的2222端口。
>> 如果你是第一次登录对方主机，系统会出现下面的提示：
>>     　　$ ssh user@host
>>     　　The authenticity of host 'host (12.18.429.21)' can't be established.
>>     　　RSA key fingerprint is 98:2e:d7:e0:de:9f:ac:67:28:c2:42:2d:37:16:58:4d.
>>     　　Are you sure you want to continue connecting (yes/no)?
>> 这段话的意思是，无法确认host主机的真实性，只知道它的公钥指纹，问你还想继续连接吗？
>> 所谓"公钥指纹"，是指公钥长度较长（这里采用RSA算法，长达1024位），很难比对，所以对其进行MD5计算，将它变成一个128位的指纹。上例中是98:2e:d7:e0:de:9f:ac:67:28:c2:42:2d:37:16:58:4d，再进行比较，就容易多了。
>> 很自然的一个问题就是，用户怎么知道远程主机的公钥指纹应该是多少？回答是没有好办法，远程主机必须在自己的网站上贴出公钥指纹，以便用户自行核对。
>> 假定经过风险衡量以后，用户决定接受这个远程主机的公钥。
>>     　　Are you sure you want to continue connecting (yes/no)? yes
>> 系统会出现一句提示，表示host主机已经得到认可。
>>     　　Warning: Permanently added 'host,12.18.429.21' (RSA) to the list of known hosts.
>> 然后，会要求输入密码。
>>     　　Password: (enter password)
>> 如果密码正确，就可以登录了。
>> 当远程主机的公钥被接受以后，它就会被保存在文件$HOME/.ssh/known_hosts之中。下次再连接这台主机，系统就会认出它的公钥已经保存在本地了，从而跳过警告部分，直接提示输入密码。
>> 每个SSH用户都有自己的known_hosts文件，此外系统也有一个这样的文件，通常是/etc/ssh/ssh_known_hosts，保存一些对所有用户都可信赖的远程主机的公钥。
>> ~~~

##### 公钥登录

>> ~~~
>> 使用密码登录，每次都必须输入密码，非常麻烦。好在SSH还提供了公钥登录，可以省去输入密码的步骤。
>> 所谓"公钥登录"，原理很简单，就是用户将自己的公钥储存在远程主机上。登录的时候，远程主机会向用户发送一段随机字符串，用户用自己的私钥加密后，再发回来。远程主机用事先储存的公钥进行解密，如果成功，就证明用户是可信的，直接允许登录shell，不再要求密码。
>> 这种方法要求用户必须提供自己的公钥。如果没有现成的，可以直接用ssh-keygen生成一个：
>> 　$ ssh-keygen
>> 运行上面的命令以后，系统会出现一系列提示，可以一路回车。其中有一个问题是，要不要对私钥设置口令（passphrase），如果担心私钥的安全，这里可以设置一个。
>> ssh-copy-id命令可以把本地主机的公钥复制到远程主机的authorized_keys文件上，ssh-copy-id命令也会给远程主机的用户主目录（home）和~/.ssh, 和~/.ssh/authorized_keys设置合适的权限。
>>
>> 语法
>> ssh-copy-id [-i [identity_file]] [user@]machine
>> 选项
>> -i：指定公钥文件
>> 实例
>> 1、把本地的ssh公钥文件安装到远程主机对应的账户下：
>>
>> ssh-copy-id user@server
>> ssh-copy-id -i ~/.ssh/id_rsa.pub user@server
>> 好了，从此你再登录，就不需要输入密码了。
>> 如果还是不行，就打开远程主机的/etc/ssh/sshd_config这个文件，检查下面几行前面"#"注释是否取掉。
>> 　　RSAAuthentication yes
>> 　　PubkeyAuthentication yes
>> 　　AuthorizedKeysFile .ssh/authorized_keys
>> 然后，重启远程主机的ssh服务。
>> 　　// ubuntu系统
>> 　　service ssh restart
>> 　　// debian系统
>> 　　/etc/init.d/ssh restart
>> ~~~
>>
>> authorized_keys文件
>>
>> ~~~
>> 远程主机将用户的公钥，保存在登录后的用户主目录的$HOME/.ssh/authorized_keys文件中。公钥就是一段字符串，只要把它追加在authorized_keys文件的末尾就行了。
>>
>> 这里不使用上面的ssh-copy-id命令，改用下面的命令，解释公钥的保存过程：
>> 　　$ ssh user@host 'mkdir -p .ssh && cat >> .ssh/authorized_keys' < ~/.ssh/id_rsa.pub
>> 这条命令由多个语句组成，依次分解开来看：（1）"$ ssh user@host"，表示登录远程主机；（2）单引号中的mkdir .ssh && cat >> .ssh/authorized_keys，表示登录后在远程shell上执行的命令：（3）"$ mkdir -p .ssh"的作用是，如果用户主目录中的.ssh目录不存在，就创建一个；（4）'cat >> .ssh/authorized_keys' < ~/.ssh/id_rsa.pub的作用是，将本地的公钥文件~/.ssh/id_rsa.pub，重定向追加到远程文件authorized_keys的末尾。
>> 写入authorized_keys文件后，公钥登录的设置就完成了。
>> ~~~

#### 使用ssh在远程后台不中断的跑程序

>> ~~~
>> Linux关闭ssh（关闭终端等）后运行的程序或者服务自动停止，如python3 a.py &。
>> 解决：使用nohup命令让程序在关闭窗口（切换SSH连接）的时候程序还能继续在后台运行。
>> nohup python3 a.py &
>> ~~~
>>
>> > [[linux进程管理与SELinux](http://blog.csdn.net/pipisorry/article/details/23376005)] 
>> >
>> > [皮皮blog](http://blog.csdn.net/pipisorry)

#### SSH数据传输

>> ~~~
>> SSH不仅可以用于远程主机登录，还可以直接在远程主机上执行操作。
>>     　　$ ssh user@host 'mkdir -p .ssh && cat >> .ssh/authorized_keys' < ~/.ssh/id_rsa.pub
>> 单引号中间的部分，表示在远程主机上执行的操作；后面的输入重定向，表示数据通过SSH传向远程主机。
>> 这就是说，SSH可以在用户和远程主机之间，建立命令和数据的传输通道，因此很多事情都可以通过SSH来完成。
>> 下面看几个例子。
>> 【例1】
>> 将$HOME/src/目录下面的所有文件，复制到远程主机的$HOME/src/目录。
>>     　　$ cd && tar czv src | ssh user@host 'tar xz'
>> 【例2】
>> 将远程主机$HOME/src/目录下面的所有文件，复制到用户的当前目录。
>>     　　$ ssh user@host 'tar cz src' | tar xzv
>> 【例3】
>> 查看远程主机是否运行进程httpd。
>>     　　$ ssh user@host 'ps ax | grep [h]ttpd'
>> lz建议使用scp进行远程copy：
>> ~~~

#### scp 跨机远程拷贝

>> ~~~
>> scp是secure copy的简写，用于在Linux下进行远程拷贝文件的命令，和它类似的命令有cp，不过cp只是在本机进行拷贝不能跨服务器，而且scp传输是加密的。可能会稍微影响一下速度。两台主机之间复制文件必需得同时有两台主机的复制执行帐号和操作权限。
>> scp命令参数
>> -1 强制scp命令使用协议ssh1
>> -2 强制scp命令使用协议ssh2
>> -4 强制scp命令只使用IPv4寻址
>> -6 强制scp命令只使用IPv6寻址
>> -B 使用批处理模式（传输过程中不询问传输口令或短语）
>> -C 允许压缩。（将-C标志传递给ssh，从而打开压缩功能）
>> -p 留原文件的修改时间，访问时间和访问权限。
>> -q 不显示传输进度条。
>> -r 递归复制整个目录。
>> -v 详细方式显示输出。scp和ssh(1)会显示出整个过程的调试信息。这些信息用于调试连接，验证和配置问题。
>> -c cipher 以cipher将数据传输进行加密，这个选项将直接传递给ssh。
>> -F ssh_config 指定一个替代的ssh配置文件，此参数直接传递给ssh。
>> -i identity_file 从指定文件中读取传输时使用的密钥文件，此参数直接传递给ssh。
>> -l limit 限定用户所能使用的带宽，以Kbit/s为单位。
>> -o ssh_option 如果习惯于使用ssh_config(5)中的参数传递方式，
>> -P port 注意是大写的P, port是指定数据传输用到的端口号
>> -S program 指定加密传输时所使用的程序。此程序必须能够理解ssh(1)的选项。
>> scp一般有六种使用方法
>> 本地复制远程文件：（把远程的文件复制到本地）
>> scp root@www.test.com:/val/test/test.tar.gz /val/test/test.tar.gz
>> 远程复制本地文件：（把本地的文件复制到远程主机上）
>> scp /val/test.tar.gz root@www.test.com:/val/test.tar.gz
>> 本地复制远程目录：（把远程的目录复制到本地）
>> scp -r root@www.test.com:/val/test/ /val/test/
>> 远程复制本地目录：（把本地的目录复制到远程主机上）
>> scp -r ./ubuntu_env/ root@192.168.0.111:/home/pipi
>> pika:/media/pika/files/machine_learning/datasets$scp -r SocialNetworks/ piting@192.168.0.172:/media/data/pipi/datasets
>> 本地复制远程文件到指定目录：（把远程的文件复制到本地）
>> scp root@www.test.com:/val/test/test.tar.gz /val/test/
>> 远程复制本地文件到指定目录：（把本地的文件复制到远程主机上）
>> scp /val/test.tar.gz root@www.test.com:/val/
>> ps: scp复制文件时只指定服务器地址不加路径默认复制到哪里???
>> ~~~
>>
>> > [[12个scp传输文件的命令栗子](http://www.cnblogs.com/voidy/p/4215891.html)]
>> >
>> > [[scp 跨机远程拷贝](http://linuxtools-rst.readthedocs.io/zh_CN/latest/tool/scp.html)]

#### 绑定本地端

>> ~~~
>> 既然SSH可以传送数据，那么我们可以让那些不加密的网络连接，全部改走SSH连接，从而提高安全性。
>> 假定我们要让8080端口的数据，都通过SSH传向远程主机，命令就这样写：
>>     　　$ ssh -D 8080 user@host
>> SSH会建立一个socket，去监听本地的8080端口。一旦有数据传向那个端口，就自动把它转移到SSH连接上面，发往远程主机。可以想象，如果8080端口原来是一个不加密端口，现在将变成一个加密端口。本地端口转发
>> ~~~

#### 本地端口转发

> ~~~
> 有时，绑定本地端口还不够，还必须指定数据传送的目标主机，从而形成点对点的"端口转发"。为了区别后文的"远程端口转发"，我们把这种情况称为"本地端口转发"（Local forwarding）。
> 假定host1是本地主机，host2是远程主机。由于种种原因，这两台主机之间无法连通。但是，另外还有一台host3，可以同时连通前面两台主机。因此，很自然的想法就是，通过host3，将host1连上host2。
> 我们在host1执行下面的命令：
>     　　$ ssh -L 2121:host2:21 host3
> 命令中的L参数一共接受三个值，分别是"本地端口:目标主机:目标主机端口"，它们之间用冒号分隔。这条命令的意思，就是指定SSH绑定本地端口2121，然后指定host3将所有的数据，转发到目标主机host2的21端口（假定host2运行FTP，默认端口为21）。
> 这样一来，我们只要连接host1的2121端口，就等于连上了host2的21端口。
>     　　$ ftp localhost:2121
> "本地端口转发"使得host1和host3之间仿佛形成一个数据传输的秘密隧道，因此又被称为"SSH隧道"。
> 下面是一个比较有趣的例子。
>     　　$ ssh -L 5900:localhost:5900 host3
> 它表示将本机的5900端口绑定host3的5900端口（这里的localhost指的是host3，因为目标主机是相对host3而言的）。
> 另一个例子是通过host3的端口转发，ssh登录host2。
>     　　$ ssh -L 9001:host2:22 host3
> 这时，只要ssh登录本机的9001端口，就相当于登录host2了。
>     　　$ ssh -p 9001 localhost
> 上面的-p参数表示指定登录端口。
> ~~~

#### 远程端口转发

~~~
既然"本地端口转发"是指绑定本地端口的转发，那么"远程端口转发"（remote forwarding）当然是指绑定远程端口的转发。
还是接着看上面那个例子，host1与host2之间无法连通，必须借助host3转发。但是，特殊情况出现了，host3是一台内网机器，它可以连接外网的host1，但是反过来就不行，外网的host1连不上内网的host3。这时，"本地端口转发"就不能用了，怎么办？
解决办法是，既然host3可以连host1，那么就从host3上建立与host1的SSH连接，然后在host1上使用这条连接就可以了。
我们在host3执行下面的命令：
    　　$ ssh -R 2121:host2:21 host1
R参数也是接受三个值，分别是"远程主机端口:目标主机:目标主机端口"。这条命令的意思，就是让host1监听它自己的2121端口，然后将所有数据经由host3，转发到host2的21端口。由于对于host3来说，host1是远程主机，所以这种情况就被称为"远程端口绑定"。
绑定之后，我们在host1就可以连接host2了：
    　　$ ftp localhost:2121
这里必须指出，"远程端口转发"的前提条件是，host1和host3两台主机都有sshD和ssh客户端。
~~~

#### SSH远程连接故障排查示例

> 1、利用ping命令检查（客户端执行）、确定物理链路是否通畅。【判断路是否通】
>
> > 也可以使用tracert -d ip (仅适合windows)或traceroute ip -n 适合linux，命令跟踪路由情况，
>
> 2、利用telent或nmap命令检查（客户端执行）【SSH服务是否有问题，判断旅游景点是否开放】
>
> >telent 115.159.33.102 22或nmap 115.159.33.102 -p 22,查看22端口是否开放
>
> 3、检查iptables等防火墙策略是否阻挡了连接（服务端执行）【是不是防火墙阻挡了，即是不是下雪封路，高速路遇阻无法通行了】
>
> > 具体命令为：
> >
> > /etc/init.d/iptables status,初学者最好关掉iptables，等日后学习了iptables后再开启。

### linux系统应用管理

#### 查看linux系统信息

>cat /etc/redhat-release 系统版本信息
>
>> CentOS Linux release 7.4.1708 (Core)
>
>uname -r 内核版本号
>
>> 4.15.0-1.el7.elrepo.x86_64

#### 账号管理

> **添加账号**
>
> useradd  sb
>
> passwd sb
>
> > Changing password for user sbtest.
> > New password: 123456asdfg
>
> 尝试切换用户角色，命令如下
>
> ~~~
> su - sbtest 由root管理员切换到普通用户sbtest
> whami
> [root@VM_250_91_centos init.d]# su - sbtest
> [sbtest@VM_250_91_centos ~]$ whoami
> sbtest
> [sbtest@VM_250_91_centos ~]$ su - root
> Password: 
> ~~~
>
> **删除账号**
>
> ~~~
>    -r：删除用户的同时，清除用户的家目录
>     示例：# userdel -r hk
>            意为：此命令删除用户hk在系统文件（主要是/etc/passwd，/etc/shadow，/etc/group等）中的记录，同时删除用户的主目录。
> ~~~
>
> #### 修改账号信息
>
> ~~~
>  -c, --comment‘COMMENT’；修改用户的注释信息；
>
>        -g, --gid GROUPNAME：修改用户的主要组
>
>        -G, --groupsGROUP1[,GROUP2,...[,GROUPN]]]：修改用户的附加组为列表中的组；
>
>        -a, --append；与-G选项同时使用，给用户添加新的附加组；
>
>        -d, --home /PATH/TO/HOME_DIR:修改用户的家目录；
>
>        -m, --move-home：与-d选项同时使用，将旧的家目录中的数据移动至新家之中；
>
>        -l, --login NEW_LOGIN：更改用户账户的登录名；
>
>        -s, --shell /PATH/TO/SHELL:修改用户账户的登录shell
>
>        -u, --uid UID:修改用户的UID 
>
>        -L, --lock:锁定用户密码；
>
>        -U, --unlock:解锁用户密码；
>
>    示例：# usermod gentoo -G bin,root -s /bin/csh -c "Gentoo Distribution"
>
>    意为：将用户gentoo的附加组修改为bin和root，默认shell为/bin/csh，注释信息为"Gentoo Distribution"；
>
>        # usermod fedora -aG centos
>
>    意为：为用户fedora添加新的附属组centos
> ~~~
>
> 
>
> **提示，在企业生产环境中应尽量避免直接到root用户下操作，除非有超越普通用户权限的系统需要维护需求**
>
> **说明，超级用户切换到普通用户下面，是无需输入对应用户密码，这相当于皇帝去大臣家里。普通用户切换到root或者其他普通用户下，需要输入切换的对应用户密码。普通用户的权限比较小，只能进行基本的系统信息查看等操作，无法更改系统配置和管理服务。$符号是普通用户的命令行提示符，#是超级管理员的提示符。提示符@前面的代表当前用户（可用whoami查询），后面的为主机名（可用hostname查询），~所在的位置是窗口当前用户所在的路径。**
>
> **说明，touch创建一个已经存在的文件时，不会提示也不会覆盖，会更新这个文件的时间戳。**

#### 组管理

> **添加用户组groupadd**
>
> ~~~
> -g gid:在创建组账户的时候，指定组账户的GID；如果不使用该选项指定，系统会选择在组解析文件中出现在的不大于60000最大的GID加1；
> -r：创建系统组，意思就是创建一个GID在1~999（1~499）之间的组；
> 示例：# groupadd -g 1001 group2
> 意为：此命令向系统中增加了一个新组group2，同时指定新组的组标识号是1001。
> ~~~
>
> **删除用户组groupdel**
>
> ~~~
>  # groupdel group1
> 此命令从系统中删除组group1。
> ~~~
>
> **修改用户组的属性gorupmod**
>
> ~~~
> -g gid：修改组账户的ID；
> -n ：修改组名；
> 示例：# groupmod mydisk -g 808
> 意为：将组mydisk的标识号修改为808
> ~~~
>
> **gpasswd 命令：给组加密码**
>
> ~~~
> gpasswd GROUPNAME
> 给组添加密码的作用
> 为什么需要给组添加密码呢？不妨先说一下用户的基本组，好像到现在我们还没有讲基本组的情况吧，嘿嘿。基本组很简单，Linux 规定每个用户都需要在某一个组中，因此在创建用户的时候，我们可以指定用户的基本组（默认组）：useradd -g GROUPNAME USERNAME。如果我们不手动指定用户的基本组，系统会默认创建一个和当前用户名一致的组，然后将这个组设置为用户的基本组。基本组的 GID 默认和用户 UID 一致（如果不被占用的话）。
>
> 　　为啥用户必须要有一个组呢？因为 Linux 规定，一个文件的需要具备三种权限：文件所属主的权限，文件所属主所在组的权限，以及其他用户的权限。因此文件的所属主要是没有基本组的话，那是不是非常尴尬呢。这个问题先说到这里。
>
> 　　回头看一下 gpasswd 的作用，一般情况下我们是不需要为组设置密码的。现在提一个需求：在执行某项操作的时候，要使用到其他组的权限，就需要临时切换到其他组，又不想改变现有组，那么就需要使用 newgrp 命令，newgrp 命令就是用来临时切换用户基本组，注意此操作只对当前登录有效。在使用 newgrp 的时候，可能需要我们输入组密码。为什么是可能呢？因为在将额外组临时设置为用户的基本组时，是不需要密码的。只有将此前和用户毫不相关的组临时设置为基本组才会需要密码。如需还原基本组：exit 或者 logout。
> ~~~
>
> 
>
> **组的认证管理**
>
> ~~~
>       -a, --add user：向名为 group 的组中添加用户 user。
>       -d, --delete user：从名为 group 的组中移除用户 user。
>       -r, 删除密码
>       -R,限制用户登入组，只有组中的成员才可以用newgrp加入该组
> [root@izwz91bjjyezq97zmsrd3iz ~]# groupadd  ywgroup
> [root@izwz91bjjyezq97zmsrd3iz ~]# gpasswd -a ywManageweb01 ywgroup
> Adding user ywManageweb01 to group ywgroup
> [root@izwz91bjjyezq97zmsrd3iz ~]# 
>
> ~~~
>
> 

### 安装Linux系统后调优及安全设置

#### SELinux关闭和开启功能

> selinux介绍
>
> ~~~
> SELinux(Security-Enhanced Linux) 是美国国家安全局（NSA）对于强制访问控制的实现，是 Linux历史上最杰出的新安全子系统。NSA是在Linux社区的帮助下开发了一种访问控制体系，在这种访问控制体系的限制下，进程只能访问那些在他的任务中所需要文件。
> ~~~

> 查看SELinux状态：
>
> 1、/usr/sbin/sestatus -v      ##如果SELinux status参数为enabled即为开启状态
>
> SELinux status:                 enabled
>
> 2、getenforce                 ##也可以用这个命令检查
>
> 关闭SELinux：
>
> 1、临时关闭（不用重启机器）：
>
> setenforce 0                  ##设置SELinux 成为permissive模式
>
> ​                              ##setenforce 1 设置SELinux 成为enforcing模式
>
> 2、修改配置文件需要重启机器：
>
> 修改/etc/selinux/config 文件
>
> 将SELINUX=enforcing改为SELINUX=disabled
>
> 重启机器即可

> 为什么要关闭selinux
>
> ~~~
> 原因有几个。1. 如余虹建所说，麻烦确实是一个因素2. 圈子里的人都会关掉它，我们看到的文章，书里，使用SELinux的真的非常少。因为关掉它造成的损失可以有解释说别人也是这么做的3. 不确定性，因为一直没有搞过，然后所有的软件的文档里也没有写SELinux相关的配置，遇到相关问题时不好解决按照这个惯性下来，装完系统的第一件事就是它关，就没什么奇怪了除非因为某个大事件，因为它一个大公司的资料泄露或是被攻入，引起这个圈子的人的大讨论，这个传统会是一直继续下去的
> 作者：刘长元
> 链接：https://www.zhihu.com/question/20559538/answer/15493077
> 来源：知乎
> 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
> ~~~

#### 修改Linux主机名

> Linux操作系统的hostname是一个kernel变量,可以通过hostname命令来查看本机的hostname。也可以直接cat /proc/sys/kernel/hostname查看，感兴趣的朋友可以参考下本文的linux的hostname修改介绍。
>
> hostname newname 
> newname即要设置的新的hostname，运行后立即生效，但是在系统重启后会丢失所做的修改，如果要永久更改系统的hostname，就要修改相关的设置文件。 
>
> **永久更改Linux的hostname**
>
> ~~~
> man hostname里有这么一句话，”The host name is usually set once at system startup in /etc/rc.d/rc.inet1 or /etc/init.d/boot (normally by reading the contents of a file which contains the host name, e.g. /etc/hostname).” RedHat里没有这个文件，而是由/etc/rc.d/rc.sysinit这个脚本负责设置系统的hostname，它读取/etc /sysconfig/network这个文本文件，RedHat的hostname就是在这个文件里设置。 
> 所以，如果要永久修改RedHat的hostname，就修改/etc/sysconfig/network文件，将里面的HOSTNAME这一行修改成HOSTNAME=NEWNAME，其中NEWNAME就是你要设置的hostname。 
> Debian发行版的hostname的配置文件是/etc/hostname。 
> 修该配置文件后，重启系统就会读取配置文件设置新的hostname。 
> ~~~
>
> **hostname与/etc/hosts的关系** 
>
> ~~~
> 很过人一提到更改hostname首先就想到修改/etc/hosts文件，认为hostname的配置文件就是/etc/hosts。其实不是的。 
> hosts文件的作用相当如DNS，提供IP地址到hostname的对应。早期的互联网计算机少，单机hosts文件里足够存放所有联网计算机。不过随着互联网的发展，这就远远不够了。于是就出现了分布式的DNS系统。由DNS服务器来提供类似的IP地址到域名的对应。具体可以man hosts。 
> Linux系统在向DNS服务器发出域名解析请求之前会查询/etc/hosts文件，如果里面有相应的记录，就会使用hosts里面的记录。/etc/hosts文件通常里面包含这一条记录 .
> 127.0.0.1 localhost.localdomain localhost 
> hosts文件格式是一行一条记录，分别是IP地址 hostname aliases，三者用空白字符分隔，aliases可选。 
> 127.0.0.1到localhost这一条建议不要修改，因为很多应用程序会用到这个，比如sendmail，修改之后这些程序可能就无法正常运行。 
>
> 修改hostname后，如果想要在本机上用newhostname来访问，就必须在/etc/hosts文件里添加一条newhostname的记录。比如我的eth0的IP是192.168.1.61，我将hosts文件修改如下： 
> #hostname blog.infernor.net 
> # cat /etc/hosts 
> 127.0.0.1 localhost.localdomain localhost 
> 192.168.1.61 blog.infernor.net blog 
> 这样，我就可以通过blog或者blog.infernor.net来访问本机。 
> 从上面这些来看，/etc/hosts于设置hostname是没直接关系的，仅仅当你要在本机上用新的hostname来访问自己的时候才会用到/etc/hosts文件。两者没有必然的联系。 
> RHEL还有个问题。 
>
> 我开始在测试的时候，只修改/etc/hosts，里面添加 192.168.1.61 blog.infernor.net blog，而/etc/sysconfig/network维持原状，也就是里面的HOSTNAME=localhost.localdomain。我重启系统后居然发现hostname给修改成了blog.infernor.net。这样看的话，倒真觉得/etc/hosts是hostname的配置文件。后来终于在/etc/rc.d/rc.sysinit这个启动脚本里发现了问题的所在。 
> rc.sysinit文件里一开始就设置了hostname 
> if [ -f /etc/sysconfig/network ]; then 
> . /etc/sysconfig/network 
> fi 
> if [ -z "$HOSTNAME" -o "$HOSTNAME" = "(none)" ]; then 
> HOSTNAME=localhost 
> fi 
> 确实使用了/etc/sysconfig/network里的hostname值。不过后面还有一段关于设置hostname的 
> ipaddr= 
> if [ "$HOSTNAME" = "localhost" -o "$HOSTNAME" = "localhost.localdomain" ] 
> ; then 
> ipaddr=$(ip addr show to 0/0 scope global | awk '/[[:space:]]inet 
> / { print gensub("/.*","","g",$2) }') 
> if [ -n "$ipaddr" ]; then 
> eval $(ipcalc -h $ipaddr 2>/dev/null) 
> hostname ${HOSTNAME} 
> fi 
> fi 
> 脚本判断hostname是否为localhost或者localhost.localdomain，如果是的话，将会使用接口IP地址对应的 hostname来重新设置系统的hostname。问题就出在这里，我的/etc/sysconfig/network默认的hostname是 localhost.localdomain，eth0的IP是192.168.1.61，而/etc/hosts里有192.168.1.61的记录。于是就用192.168.1.61这条记录来替换了hostname。 
> 估计这也是很多人将/etc/hosts误以为是hostname的配置文件的原因。
> ~~~
>
> 

#### 精简开机自启动

必须要保留的开机自启动的服务有5个。

> sshd：远程连接linux服务器时需要用到这个服务程序，所以必须开启。
>
> rsyslog:日志相关软件，这是操作系统提供的一种机制，系统的守护程序通常会使用rsyslog程序将各种信息写到各个系统日志文件中，在centos6以前此服务的名字为syslog。
>
> network：系统启动时，若想激活/关闭各个网络接口，则应考虑开启此服务。
>
> crond:该服务用于周期性的执行系统及用户配置的任务计划。有要周期性执行的任务时，就要开启，此服务几乎是生产场景必须要用的一个软件。
>
> sysstat；systat是一个软件包，包含检测系统性能及效率的一组工具，这些工具对于我们收集系统性能数据很有帮助，比如cpu使用率、硬盘和网络吞吐率。
>
> ~~~
> Sysstat 软件包集成如下工具：
>     * iostat 工具提供CPU使用率及硬盘吞吐效率的数据；
>     * mpstat 工具提供单个处理器或多个处理器相关数据；
>     * sar 工具负责收集、报告并存储系统活跃的信息；
>     * sa1 工具负责收集并存储每天系统动态信息到一个二进制的文件中。它是通过计划任务工具cron来运行，
>         是为sadc所设计的程序前端程序；
>     * sa2 工具负责把每天的系统活跃性息写入总结性的报告中。它是为sar所设计的前端 ，要通过cron来调用
>     * sadc 是系统动态数据收集工具，收集的数据被写一个二进制的文件中，它被用作sar工具的后端；
>     * sadf 显示被sar通过多种格式收集的数据；
> ~~~

#### 关闭防火墙

>  CentOS中防火墙程序主要是firewall和iptables，CentOS7中firewall服务已经默认安装好了，而iptables服务需要自己用yum  install  iptabes-services来安装。
>
> ** 说明：以下演示均在CentOS7中进行，其他版本也大同小异** 

> **firewall相关的操作** 
>
> 查看防火墙状态
>
> > [root@localhost ~]# firewall-cmd    --state
> > not running
> > [root@localhost ~]# 
>
> 关闭防火墙
>
> > systemctl sop firewall.service
>
> 开启防火墙
>
> > systemctl start firewall.service
>
> 禁止开机启动启动防火墙
>
> > systemctl disable firewall.service

> **iptables相关的操作**
>
>  iptables服务需要自己安装，命令是：
>
> > yum install iptables-services
>
> 开启iptables防火墙的命令是
>
> > systemctl start iptables.service
>
> 关闭iptables防火墙的命令是
>
> > systemctl stop iptables.service
>
> 重启 
>
> > systemctl restart iptables.service
>
> 查看状态
>
> > systemctl  status  iptables.service

#### linux系统安全最小原则说明

> 安装linux系统最小化，即选包最小化，yum安装软件包也要最小化，无用的包不装。
>
> 开机自启动服务最小化，即无用的服务不开启。
>
> 操作命令最小化。例如，能用rm -f test.txt 就不用rm -fr test.txt
>
> 登录linux用户最小化。平时没有特殊需求不登录root,用普通用户登录即可。
>
> 普通用户授权权限最小化，即只给用户必需的管理系统的命令。
>
> Linux系统文件及目录的权限设置最小化，禁止随意创建、更改、删除文件。

#### 更改SSH服务器端远程登录的配置

> 为什么要更改ssh服务远程登录配置？因为黑客都知道Linux远程连接默认端口为22，管理员用户默认为root，采取默认配置会增大我们系统被黑客入侵成功的概率。 
> ssh服务端的配置文件是 **/ect/ssh/** 路径下的 **sshd_config** 文件。
>
> ~~~
> 1、在这里使用vi编辑器编辑这 sshd_config 文件来进行配置。 
> Port 端口号（默认是22）,我们可以随意改但尽量不要使用0到1024之间的端口号（port的取值范围是 0 - 65535(即2的16次方)），这里我改为了10680。 
> 2、PermitRootLogin 是否允许使用ssh服务root登录（默认yes），改为no。
> 3、UseDNS 是否使用DNS（默认yes），改为no。
> 4、PermitEmptyPasswords 是否允许空密码（默认no），不用再改了。 
> 这些改完之后，使用命令 /etc/init.d/sshd reload 使配置生效
> 或者/etc/init.d/sshd restart
> ~~~
>
> **说明，reload为平滑重启，不影响正在SSH连接的其他用户，因此要好于restart。** 

#### 利用sudo控制用户对系统命令的使用权限

> 为了安全及管理的方便，可将需要root权限的普通用户加入sudo管理，这样用户就可以通过自己的普通账户登录，利用root的权限来管理系统，当然也就不需要有root账号及密码了。
>
> sudo有以下特点
>
> ~~~
> 1. sudo能够限制指定用户在指定主机上运行某些命令。
> 2. sudo可以提供日志，忠实地记录每个用户使用sudo做了些什么，并且能将日志传到中心主机或者日志服务器。
> 3. sudo为系统管理员提供配置文件，允许系统管理员集中地管理用户的使用权限和使用的主机。它默认的存放位置是/etc/sudoers。
> 4.sudo使用时间戳文件来完成类似“检票”的系统。当用户执行sudo并且输入密码后，用户获得了一张默认存活期为5分钟的“入场券”（默认值可以在编译的时候改变）。超时以后，用户必须重新输入密码。
> ~~~
>
> **配置sudo**
>
> 配置sudo（super user do！）必须通过编辑/etc/sudoers文件，而且只有超级用户才可以修改它，还必须使用visudo编辑。之所以使用visudo有两个原因，一是它能够防止
>
> 两个用户同时修改它；二是它也能进行有限的语法检查。所以，即使只有你一个超级用户，你也最好用visudo来检查一下语法。
>
> visudo默认的是在vi里打开配置文件，用vi来修改文件。我们可以在编译时修改这个默认项。visudo不会擅自保存带有语法错误的配置文件，它会提示你出现的问题，并询问该如何处理。
>
> 操作
>
>  Syntax:
>
> 语法  user    MACHINE=COMMANDS   用户 登录的主机名=（可以变换的身份） 可以执行的命令
>
> ~~~
> 使用visudo编辑，添加sbtest ALL=(ALL) ALL
> 用sbtest使用 sudo touch a.txt提示权限的时候会提示：
> sudo touch a.txt
> [sudo] password for sbtest:
> 修改成sbtest ALL=(ALL) NOPASSWD:ALL,在提示权限的时候就不需要输入密码了。
> [sbtest@VM_250_91_centos conf]$ touch a.txt
> touch: cannot touch ‘a.txt’: Permission denied
> [sbtest@VM_250_91_centos conf]$ sudo touch a.txt
> ~~~
>
> > 详细了解可以访问 [sudo配置文件/etc/sudoers详解及实战用法](http://blog.csdn.net/Field_Yang/article/details/51547804)
> >
> > [linux /etc/sudoers 文件说明](http://blog.csdn.net/u011641885/article/details/47722699)

#### 历史数据数及登录超时环境变量的设置

> export TMOUT=10 #临时生效
>
> export HISSIZE=5 #临时生效
>
> echo `export TMOUT=10` >>/etc/profile #永久生效

#### Linux服务器内核参数优化

> 略。

#### 锁定关键系统文件，防止被提升篡改

> **chattr命令**用来改变文件属性。这项指令可改变存放在ext2文件系统上的文件或目录属性，这些属性共有以下8种模式：
>
> ~~~
> a：让文件或目录仅供附加用途；
> b：不更新文件或目录的最后存取时间；
> c：将文件或目录压缩后存放；
> d：将文件或目录排除在倾倒操作之外；
> i：不得任意更动文件或目录；
> s：保密性删除文件或目录；
> S：即时更新文件或目录；
> u：预防意外删除。
> -R：递归处理，将指令目录下的所有文件及子目录一并处理；
> -v<版本编号>：设置文件或目录版本；
> -V：显示指令执行过程；
> +<属性>：开启文件或目录的该项属性；
> -<属性>：关闭文件或目录的该项属性；
> =<属性>：指定文件或目录的该项属性。
> ~~~
>
> **实例**
>
> 用chattr命令防止系统中某个关键文件被修改：
>
> ```
> chattr +i /etc/fstab
> ```
>
> 然后试一下[rm](http://man.linuxde.net/rm)、[mv](http://man.linuxde.net/mv)、[rename](http://man.linuxde.net/rename)等命令操作于该文件，都是得到Operation not permitted的结果。
>
> 让某个文件只能往里面追加内容，不能删除，一些日志文件适用于这种操作：
>
> ```
> chattr +a /data1/user_act.log
> ```
>
> 如果想更加安全，可以把chattr改名转移，防止黑客利用。命令如下
>
> ~~~
> mv /usr/bin/chattr /usr/bin/hk1
> ~~~
>
> hk1 +i /etc/passwd 

#### 为grub菜单加密码

> [参考链接](http://blog.51cto.com/13055758/2053986)

#### 禁止linux系统不被ping

> [参考链接](Linux禁止ping的方法)
>
> **说明，是否有必要禁ping**
>
> ~~~
> 禁用ping和tracert我想应该是从网络安全的角度来考虑的。但我站在另外的角度来说说这个问题。我认为企业的网络安全规划应该综合考虑企业信息安全标准和自身网络实际情况，以及自身运维团队的实际情况。仅就安全的角度来说，当然是管控越严，就越能减少安全事件发生的几率。但是管控太严又极大的降低了整体网络的易用性，也极大增加了运维管理难度。所以网络安全规划应该是权衡安全性、易用性和运维管理粒度后的产物。题主所问ping和tracert是网络运维的基本工具，为了安全当然可以限制，但是为运维操作带来太多的障碍，不建议禁止。当然如果运维管理团队人员充足，工具充足，有更精细的运维管理能力，充分考虑运维便捷性，有针对性禁止ping和tracert确实能提升网络安全性。
>
> 作者：黄亮
> 链接：https://www.zhihu.com/question/37668237/answer/104990333
> 来源：知乎
> 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
> ~~~

#### 升级具有典型漏洞的软件版本

> openssl,openssh bash 存在很多软件漏洞，在企业场景需要进行修复，操作步骤如下：
>
> rpm -qa openssl openssh bash 
>
> [root@GCZX_ZHUANFAJI_00 ~]# rpm -qa openssl openssh bash 
> openssl-1.0.2k-8.el7.x86_64
> openssh-7.4p1-13.el7_4.x86_64
> bash-4.2.46-29.el7_4.x86_64
>
> yum install openssl openssh bash
>
> Package 1:openssl-1.0.2k-8.el7.x86_64 already installed and latest version
> Package openssh-7.4p1-13.el7_4.x86_64 already installed and latest version
> Package bash-4.2.46-29.el7_4.x86_64 already installed and latest version
> Nothing to do

### 总结

> linux系统如何优化/
>
> [Linux系统基础优化14条总结centos6.5](http://blog.csdn.net/codeTZ/article/details/52277980)

