# 基于C语言的markdown解析器

## 当前支持的语法

* 标题
* 列表
* 引用
* 高亮的代码块
* 各种行内文字加粗，斜体，删除等效果
* 链接，图片
* 脚标
* 表格

## 编译流程

```Bash
  mkdir build 
  cd build 
  cmake ..
  make ..
  sudo make install

```
## 解析器的使用

在shell中使用
```bash
  $ ./parser test.md
  $ ls -l test.html
```
**在markdown所在的文件目录下会生成对应的html文件**

以模块的方式在C项目中使用
```c
    const char *file_name = "test.md"
    do_parser(file_name);
```


## 解析效果展示
[请点击查看测试生成的文件](http://118.25.89.81/index1.html)
