# 基于C语言的markdown解析器
<hr/>

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

```c
    const char *file_name = "test.md"
    do_parser(file_name);
```
**在当前目录下会生成对应的html文件**
