# markdown模块效果测试
--- 
> 引用测试本页面的效果均有httpServer中的markdown模块转换得到
## 图片测试
![图片插入](https://s2.ax1x.com/2019/01/20/kC59BQ.jpg)
## 引用测试
^[这是一段引用][http://www.baidu.com] 这段话来自《markdown装逼指南》[1]
## 文本测试
这是一条文本
## 列表功能测试
1. 列表1
2. 列表2
* 列表3
* 列表4
* 列表5
### 表格功能测试
\table(name,price,sum)[piano,$5000,4][violin,35000,2]
### 单行测试
**加粗** *斜体* _下划线_~~删除~~@高亮@普通文本:__*notitaly***black**@red@
## 高亮效果测试
### 编译流程
```bash
 mkdir build
 cd build 
 make ../
 sudo make .. install
```
#### JSON高亮
```JSON
{"server":{
"port":9999,
"dynamic_file":[
"/examples/servlets/"
],
"tips1": "redirect_path仅针对Java项目进行进行转发，load_server是针对PHP文件的负载均衡,如下",
"redirect_path":["/xyd/anon","/api/carousel"],
"tip2":"被转发Java请求的网站",
"redirect_site":["https://doublehh.cn","http://doublehh.cn:82"],
"map_path":"/Users/fss/CLionProjects/httpServ/",
"index":"hello.html",
"log_path":"/Users/fss/servlog.log",
"alternate_port":9998,
"static_page":"./www/http/pages/static/%s",
"load_balancing":1,
"load_servers":[8080,8081,8082]
}}
```
#### C代码高亮测试
```C
bool issymbol (char c) {
 switch (c) {
 case '-' :
 case '*':
 case '~':
 case '`':
 case '#':
 case '!':
 case '^':
 case '<':
 case '@'://表示高亮
 case '_':
 return true;
 default:
 return false;
 }
}
```
### 短引用测试
终端使用命令`nohuphttpServer&`启动服务器
\foot(脚注测试){[1].markdown是如何炼成的}{[2].markdown装逼指南}{[3].C语言从入门到放弃}