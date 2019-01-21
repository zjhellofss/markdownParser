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
* 自动生成目录

<table >
    <tr>
        <td>加粗</td>
        <td>斜体</td>
        <td>下划线</td>
        <td>图片</td>
        <td>表格</td>
        <td>链接</td>
        <td>删除</td>
        <td>代码段</td>
       <td>语法高亮</td>
       <td>脚注</td>
        <td>目录生成</td>
        </tr>
    <tr>
            <td>√</td>
            <td>√</td>
            <td>√</td>
            <td>√</td>
            <td>√</td>
            <td>√</td>
            <td>√</td>
            <td>√</td>
     <td>√</td>
            <td>√</td>
        <td>√</td>
    </tr>
</table>

## 解析效果展示
[请点击查看解析生成的文件](http://118.25.89.81/index1.html)

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
  $ md_parser test.md
  $ ls -l test.html
```
**在markdown所在的文件目录下会生成对应的html文件**

以模块的方式在C项目中使用
```c
    const char *file_name = "test.md"
    do_parser(file_name);
```



