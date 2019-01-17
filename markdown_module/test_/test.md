# 基于libevent的HttpServer
![](https://image.winudf.com/v2/image/anAudWJpLmNvbW1vbi5odHRwLnNlcnZlcl9pY29uXzl5bWllbml5/icon.png?w=170&fakeurl=1&type=.png)
放在自己vps上的效果,^[项目预览][www.localhost:9999.com]
## 简介
Libevent是一个用于处理和调度事件的网络库，以及执行非阻塞I/O，正是因为Libevent是一个基于单线程的库，如果你有多个CPU或具有多线程的CPU，会导致CPU资源闲置。对于这一问题，解决方案是为每个活动连接创建一个Libevent事件队列(AKAevent_base），每个队列都有自己的事件未决线程。这个项目正是基于这一点，为您提供编写高性能，多线程，基于Libevent的套接字HTTP服务器所需的一切。
## 功能
1.提供对简单的负载均衡和反向代理的支持,**加重**~~~意大利~~*斜体**3**4
2.提供了可供选择的线程池功能以及灵活的Json配置文件
3.完成JavaWeb请求的转发以及反向代理
4.对于服务器内部错误和请求异常提供了5种不同的日志记录等级以及内置错误页面
5.内置markdown解析模块，可以直接在页面中显示markdown效果。
## 编译以及使用
### 编译流程
```shell
mkdirbuild
mvCMakeLists.txtbuild/
cmake.
make
sudomakeinstall
```
### 样例配置文件
在安装完成后在`properties.json`中修改自己需要的配置
```JSON
{
"server":{
"port":9999,
"dynamic_file":[
"/examples/servlets/"
],
"tips1":"redirect_path仅针对Java项目进行进行转发，load_server是针对PHP文件的负载均衡,如下",
"redirect_path":["/xyd/anon","/api/carousel"],
"tip2":"被转发Java请求的网站",
"redirect_site":["https://doublehh.cn","http://doublehh.cn:82"],
"map_path":"/Users/fss/CLionProjects/httpServ/",
"index":"hello.html",
"log_path":"/Users/fss/servlog.log",
"alternate_port":9998,
"static_page":"./www/http/pages/static/%s",
"load_balancing":1,
"load_servers":[
8080,
8081,
8082
]
}
}
```
### 启动服务器
终端使用命令`nohuphttpServer&`启动服务器
## 致谢
感谢我的好朋友^[胡昊](https://github.com/1120023921)为这个项目的开发出谋划策，提供各种各样的帮助。
