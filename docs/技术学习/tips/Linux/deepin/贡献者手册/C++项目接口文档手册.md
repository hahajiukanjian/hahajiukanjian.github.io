## 项目文件结构
在docs中存放项目相关的文档资料，可以为markdown文件和.地区代码.dox扩展名的C++Doxygen注释文档。
```shell
debian/
src/
docs/
CMakeLists.txt
```
## 文档标记方式
### Doxygen文档标记方式
Doxygen称呼用来标记文档不同组成部分的关键字为Doxygen特殊指令，以下简称指令。
Doxygen指令同时支持以@或\作为指令的标识字符。为了统一，我们一律使用@作为文档指令的前缀，例如使用@fn而不是使用\fn。
完整的Doxygen特殊指令列表见[Doxygen 官网的相应页面](https://www.doxygen.nl/manual/commands.html)
|Doxygen指令|含义|
|---|---|
|@~语言ID|声明其后的部分是*语言ID*对应的语言版本，例如`@~chinese`对应中文|
|@file 文件名|声明其后的部分是对`文件名`的文档描述|
|@class 类名 头文件名|声明其后的部分是对`头文件名`中`类名`的文档描述|
|@fn 函数声明|声明其后的部分是对`函数声明`的文档描述|
|@def 宏定义	|声明其后的部分是对 宏定义 的文档描述|
|@enum 枚举定义	|声明其后的部分是对 枚举定义 对应的枚举的文档描述|
|@var 变量定义	|标记其后的部分是对 变量定义 对应的枚举或全局变量的描述|
|@brief 概述	|标记 概述 概述应该是简短而有效的|
|@details 详细描述	|标记 详细的描述|
|@param 参数名 描述	|标记对 参数名 的对应 描述 介绍|
|@deprecated 描述	|标记对应接口的废弃以及相关的 描述 介绍|
|@exception 描述	|标记对异常的 描述 介绍|
|@return 描述|	标记对返回值的 描述 介绍|
|@since 版本号	|标记相关功能或特性是自 版本号 后引入的|
|@sa 函数或类名	|标记与当前函数或类相关的其它 函数或类名（See also）|
|@note 描述	|标记值得备注的 描述 介绍|
|@code{.ext}~@endcode	|标记代码块的起止区域。代码块的格式为.ext。
|@anchor 锚点	|常和@ref一同使用，形成引用到锚点的超链接(锚点是不可见的)
|@ref 引用	|见上文 使用方法是@ref <锚点名> "<显示文字>"|
另外，Doxygen的代码注释(.dox形式文档)中也支持使用markdown进行相应的标记。
### 示例文档
假定我们对如下示例类`test.h`进行文档编写:
```cpp
class Fz_Test
{
public:
    const char *member(char, int) throw(std::out_of_range);
    void undocumented();
};
```
则此文件对应的文档`test.zh_CN.dox`看上去会是这样的:
```cpp
/*
@~chinese
@file test.h

这里是 test.h 的描述

@class Fn_Test test.h
@brief Fn_Test 类

Fn_Test 的详情

@fn const char *Fn_Test::member(char c, int n)
@brief 一个成员函数

函数的详细描述

@param c 一个字符
@param n 一个数字
@exception std::out_of_range 参数超过了范围
@return 一个字符指针
*/
```
## 配置方式
### 配置生成
Doxygen 使用 Doxyfile 维护和管理配置，但为了方便文档相关的自动化流程，我们使用 CMake 来管理相应的配置，并确保必要的配置以缓存变量的形式对外暴露，以便外部调用时控制（参见最下方“检查项”一节）。

示例配置可参考 dtkwidget 项目的 [doc/CMakeLists.txt](https://github.com/linuxdeepin/dtkwidget/blob/26509c34800a5634db16377ded0d3e746bcfbca8/doc/CMakeLists.txt)，根据项目自身情况酌情修改配置即可。

在 CMakeLists.txt 无误的情况下，使用 cmake 时，传递 -DDOXYGEN_GENERATE_HTML="YES" 即可在生成目录下的 docs/html 目录下生成 HTML 文档。其它用法请参见下面的“检查项”一节。
### 检查项
可以在执行 cmake 默认配置后，通过 make doxygen 生成 qch 文档，且可通过 cmake 传入 -DQCH_INSTALL_DESTINATION 来配置 qch 的安装位置
可以在执行 cmake 时传入 -DDOXYGEN_GENERATE_XML="YES" 配置后，通过 make doxygen 在构建目录内的 docs/xml/ 子目录中生成 XML 文档信息
可以在执行 cmake 时传入 -DDOXYGEN_GENERATE_HTML="YES" -DDOXYGEN_HTML_EXTRA_STYLESHEET="/path/to/stylesheet.css" -DDOXYGEN_TAGFILES="qtcore.tags=http://doc.qt.io/qt-5/" 配置后，通过 make doxygen 在构建目录内的 docs/html/ 子目录中生成 HTML 文档
可以通过 DOXYGEN_FILE_PATTERNS 与 DOXYGEN_OUTPUT_LANGUAGE 控制生成文档的语言（默认中文即可）
