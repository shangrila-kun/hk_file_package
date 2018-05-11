## Nginx Web服务器应用

## Nginx介绍

> ~~~
> Nginx是一款轻量级的Web 服务器/反向代理服务器及电子邮件（IMAP/POP3）代理服务器，并在一个BSD-like 协议下发行。其特点是占有内存少，并发能力强，事实上nginx的并发能力确实在同类型的网页服务器中表现较好，中国大陆使用nginx网站用户有：百度、京东、新浪、网易、腾讯、淘宝等。
>
> ~~~
>
> Nginx软件的主要企业功能应用
>
> > 作为Web服务软件  反向代理或负载均衡服务  前端业务数据缓存服务
>
> 为什么 Nginx 的性能要比 Apache 高很多？
>
> >  这得益于Nginx使用了最新的epoll（Linux 2.6内核）和kqueue（freebsd）网络I/O模型，而Apache则使用的是传统的select模型。
> >
> > 目前Linux下能够承受高并发访问的Squid、Memcached都采用的是epoll网络I/O模型。
> >
> > 处理大量的连接的读写，Apache所采用的select网络I/O模型非常低效。
> >
> > ~~~
> > 下面用一个比喻来解析Apache采用的select模型和Nginx采用的epoll模型进行之间的区别：
> > 假设你在大学读书，住的宿舍楼有很多间房间，你的朋友要来找你。
> > select版宿管大妈就会带着你的朋友挨个房间去找，直到找到你为止。
> > 而epoll版宿管大妈会先记下每位同学的房间号，
> > 你的朋友来时，只需告诉你的朋友你住在哪个房间即可，不用亲自带着你的朋友满大楼找人
> > 如果来了10000个人，都要找自己住这栋楼的同学时，select版和epoll版宿管大妈，谁的效率更高，不言自明。
> > 同理，在高并发服务器中，轮询I/O是最耗时间的操作之一，select和epoll的性能谁的性能更高，同样十分明了。
> > ~~~

## Nginx配置

> Nginx的配置文件是一个纯文本文件，它一般位于Nginx安装目录的conf目录下，整个配置文件是以block的形式组织的。每个block一般以一个大括号“{}”来表示，block可以分为几个层次，整个配置文件中Main指令位于最高层，在Main层下面可以有Events、HTTP等层级，而在HTTP层中又包含有Server层，即server block，server block中又可分为location层，并且一个server block中可以包含多个location block。
> 一个完整的配置文件结构如下图所示。
>
> ![img](http://img.my.csdn.net/uploads/201303/19/1363665285_8463.png)
>
> nginx.conf的配置文件详解如下：
>
> ~~~
> #开启进程数 <=CPU数  
> worker_processes 1;  
>   
> #错误日志保存位置  
> #error_log logs/error.log;  
> #error_log logs/error.log notice;  
> #error_log logs/error.log info;  
>   
> #进程号保存文件  
> #pid logs/nginx.pid;  
>   
> #等待事件  
> events {  
> #每个进程最大连接数（最大连接=连接数x进程数）   
> worker_connections 1024;  
> }  
>   
>   
> http {  
> #文件扩展名与文件类型映射表  
> include mime.types;  
>   
> #默认文件类型  
> default_type application/octet-stream;  
>   
> #日志文件输出格式 这个位置相于全局设置  
> #log_format main '$remote_addr - $remote_user [$time_local] "$request" '  
> # '$status $body_bytes_sent "$http_referer" '  
> # '"$http_user_agent" "$http_x_forwarded_for"';  
>   
> #请求日志保存位置  
> #access_log logs/access.log main;  
>   
> #打开发送文件  
> sendfile on;  
> #tcp_nopush on;  
>   
> #连接超时时间  
> #keepalive_timeout 0;  
> keepalive_timeout 65;  
>   
> #打开gzip压缩  
> #gzip on;  
>   
> #设定请求缓冲  
> client_header_buffer_size 1k;  
> large_client_header_buffers 4 4k;  
>   
> #设定负载均衡的服务器列表  
> upstream myproject {   
> #weigth参数表示权值，权值越高被分配到的几率越大  
> #max_fails 当有#max_fails个请求失败，就表示后端的服务器不可用，默认为1，将其设置为0可以关闭检查  
> #fail_timeout 在以后的#fail_timeout时间内nginx不会再把请求发往已检查出标记为不可用的服务器  
> #这里指定多个源服务器，ip:端口,80端口的话可写可不写   
> server 192.168.1.78:8080 weight=5 max_fails=2 fail_timeout=600s;  
> #server 192.168.1.222:8080 weight=3 max_fails=2 fail_timeout=600s;   
> }  
>   
> #第一个虚拟主机  
> server {  
> #监听IP端口  
> listen 80;  
>   
> #主机名  
> server_name localhost;  
>   
> #设置字符集  
> #charset koi8-r;  
>   
> #本虚拟server的访问日志 相当于局部变量  
> #access_log logs/host.access.log main;   
>   
> #对本server"/"启用负载均衡  
> location / {   
> #root /root; #定义服务器的默认网站根目录位置  
> #index index.php index.html index.htm; #定义首页索引文件的名称  
> proxy_pass http://myproject; #请求转向myproject定义的服务器列表  
>   
> #以下是一些反向代理的配置可删除.  
> # proxy_redirect off;   
> # proxy_set_header Host $host;   
> # proxy_set_header X-Real-IP $remote_addr;   
> # proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;   
> # client_max_body_size 10m; #允许客户端请求的最大单文件字节数   
> # client_body_buffer_size 128k; #缓冲区代理缓冲用户端请求的最大字节数，   
> # proxy_connect_timeout 90; #nginx跟后端服务器连接超时时间(代理连接超时)   
> # proxy_send_timeout 90; #后端服务器数据回传时间(代理发送超时)   
> # proxy_read_timeout 90; #连接成功后，后端服务器响应时间(代理接收超时)   
> # proxy_buffer_size 4k; #设置代理服务器（nginx）保存用户头信息的缓冲区大小   
> # proxy_buffers 4 32k; #proxy_buffers缓冲区，网页平均在32k以下的话，这样设置   
> # proxy_busy_buffers_size 64k; #高负荷下缓冲大小（proxy_buffers*2）   
> # proxy_temp_file_write_size 64k; #设定缓存文件夹大小，大于这个值，将从upstream服务器传  
> }   
> location /upload {   
> alias e:/upload;   
> }  
> #设定查看Nginx状态的地址   
> location /NginxStatus {   
> stub_status on;   
> access_log off;   
> #allow 192.168.0.3;  
> #deny all;  
> #auth_basic "NginxStatus";   
> #auth_basic_user_file conf/htpasswd;   
> }  
>   
> #error_page 404 /404.html;  
>   
> # redirect server error pages to the static page /50x.html  
> # 定义错误提示页面  
> error_page 500 502 503 504 /50x.html;  
> location = /50x.html {  
> root html;  
> }  
>   
>   
> # proxy the PHP scripts to Apache listening on 127.0.0.1:80  
> #  
> #location ~ \.php$ {  
> # proxy_pass http://127.0.0.1;  
> #}  
>   
> # pass the PHP scripts to FastCGI server listening on 127.0.0.1:9000  
> #  
> #location ~ \.php$ {  
> # root html;  
> # fastcgi_pass 127.0.0.1:9000;  
> # fastcgi_index index.php;  
> # fastcgi_param SCRIPT_FILENAME /scripts$fastcgi_script_name;  
> # include fastcgi_params;  
> #}  
>   
> # deny access to .htaccess files, if Apache's document root  
> # concurs with nginx's one  
> #  
> #location ~ /\.ht {  
> # deny all;  
> #}  
> }   
>   
>   
> # another virtual host using mix of IP-, name-, and port-based configuration  
> #  
> #server {  
> #多监听   
> # listen 8000;  
> #主机名  
> # listen somename:8080;  
> # server_name somename alias another.alias;  
>   
> # location / {  
> #WEB文件路径  
> # root html;  
> #默认首页  
> # index index.html index.htm;  
> # }  
> #}  
>   
>   
> # HTTPS server HTTPS SSL加密服务器  
> #  
> #server {  
> # listen 443;  
> # server_name localhost;  
>   
> # ssl on;  
> # ssl_certificate cert.pem;  
> # ssl_certificate_key cert.key;  
>   
> # ssl_session_timeout 5m;  
>   
> # ssl_protocols SSLv2 SSLv3 TLSv1;  
> # ssl_ciphers HIGH:!aNULL:!MD5;  
> # ssl_prefer_server_ciphers on;  
>   
> # location / {  
> # root html;  
> # index index.html index.htm;  
> # }  
> #}   
> }
> ~~~

## Nginx虚拟主机配置实践

### 虚拟主机类型

> 所谓虚拟主机，在web服务里就是一个独立的网站站点，这个站点对应独立的域名（也可能对应的是ip和端口），具有独立的程序及资源目录，可以独立的供用户访问。
>
> 一个web服务里面可以有多个虚拟主机标签对，使用一份server{}标签来标示一个虚拟主机。

> 1、基于域名的虚拟主机
>
> 2、基于端口的虚拟主机
>
> 3、基于ip的虚拟主机

### 基于域名的虚拟主机配置实践

> 单个的
>
> ~~~
> server{
>     listen 80;
>     server_name www.ap.com;
>     location /{
>         root html/www;
>         index index.html index.htm;
>     }
> }
> ~~~
>
> 多个的
>
> ~~~
> server{
>     listen 80;
>     server_name www.blog.com;
>     location /{
>         root html/www/blog;
>         index index.html index.htm;
>     }
> }
> server{
>     listen 80;
>     server_name www.bbs.com;
>     location /{
>         root html/www/bbs;
>         index index.html index.htm;
>     }
> }
> ~~~
>
> 

### 配置基于端口的虚拟主机

> 基于端口的虚拟主机在生产环境中不多见，仅偶尔会用到，一般为公司内部人员提供访问，如OA系统，网站程序的后台，CMS发布后台、mysql的web客户端phpmyadmin等，使用特殊端口多是从安全上考虑的。下面讲下基于端口的虚拟主机相关配置部署。
>
> 如果要配置基于端口的虚拟主机，就需要为每个虚拟主机配置不同的端口。基于端口的虚拟主机就是通过端口来唯一区别不同的虚拟主机的，只要端口不同就是不同的虚拟主机。
>
> 修改配置如下：
>
> ~~~
> server{
> 	listen 80;
> 	server_name www.abc.com;
> 	location /{
>         root html/www;
>         index index.html index.htm;
> 	}
> }
> server{
>     listen 81;
>     server_name www.efg.com
>     location /{
>         root html/efg;
>         index index.html index.htm;
>     }   
> }
> server{
>     listen 82;
>     server_name www.abc.com
>     location /{
>         root html/aa;
>         index index.html index.htm;
>     }   
> }
> ~~~
>
> 访问的路径如下
>
> > http://www.abc.com:80 此处80可以省略。
> >
> > http://www.efg.com:81
> >
> > http://www.abc.com:82

### 基于ip的虚拟主机配置

> 步骤是：1、在服务器网卡上增加多个ip。 2、增加虚拟主机配置。
>
> 配置基于ip的虚拟主机，就需要让每个虚拟主机有不同的ip地址，此处以增加辅助ip的形式临时在eth0网卡上增加2个不同的ip,命令如下：
>
> ip addr add 10.0.0.9/24 dev eth0
>
> ip addr add 10.0.0.10/24 dev eth0
>
> 基于ip的虚拟主机实际配置实例如下。这是一个端口和ip混合的虚拟主机实例，读者可以自行修改，使其仅仅基于ip,即每个虚拟主机的server_name 字段都换成ip地址。
>
> ~~~
> server{
>     listen 10.0.0.8：80；
>     server_name www.abc.org;此处也可以改为ip
>     location /{
>         
>     }
> }
> server{
>     listen 10.0.0.9：81；
>     server_name www.abc.org;此处也可以改为ip
>     location /{
>         
>     }
> }
> server{
>     listen 10.0.0.10：81；
>     server_name www.abc.org;此处也可以改为ip
>     location /{
>         
>     }
> }
> ~~~
>
> 客户端浏览器中访问方法
>
> > http://10.0.0.8:80;
> >
> > http://10.0.0.8:81;
>
> 

