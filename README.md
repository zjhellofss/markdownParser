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


## 使用教程

<pre>
# 这是一级标题
## 这是二级标题
### 这是三级标题
#### 这是四级标题
##### 这是五级标题
###### 这是六级标题

**这是加粗的文字**
*这是倾斜的文字*`
***这是斜体加粗的文字***
~~这是加删除线的文字~~
@这是高亮的字体@
_加下划线的字体_

> 这是引用的内容
>> 二级引用

--- 分割线

![图片alt](图片地址 ''图片title'')

^[超链接名][超链接地址 "超链接title"]

- 无序列表内容
* 无序列表内容

1.有序列表内容
2.有序列表内容

`代码内容`

```代码块

```
脚注测试:\foot(参考文献){[1].markdown是如何炼成的}{[2].markdown装逼指南}{[3].C语言从入门>到放弃}

公式:$$Latexx = {-b \pm \sqrt{b^2-4ac} \over 2a}.$$

表格 \table(name,price,sum)[piano,$5000,4][violin,35000,2][suona,5000]

<pre>


