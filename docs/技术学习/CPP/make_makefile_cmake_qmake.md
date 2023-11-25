## gcc make makefile
- `gcc`是`GNU Compiler Collection`（就是GNU编译器套件），也可以简单认为是编译器，它可以编译很多种编程语言（括`C、C++、Objective-C、Fortran、Java`等等）。
> 当我们的程序只有一个源文件时，直接可以用`gcc`编译它。但是当你的程序包含很多个源文件时，用`gcc`命令逐个去编译时，你就很容易混乱而且工作量大。所以出现了`make`工具
- `make`工具可以看成是一个智能的批处理工具，它本身并没有编译和链接的功能，而是用类似于批处理的方式—通过调用`makefile`文件中用户指定的命令来进行编译和链接的。
- `makefile`是什么？简单的说就像一首歌的乐谱，`make`工具就像指挥家，指挥家根据乐谱指挥整个乐团怎么样演奏，`make`工具就根据`makefile`中的命令进行编译和链接的。`makefile`命令中就包含了调用`gcc`（也可以是别的编译器）去编译某个源文件的命令。`makefile`在一些简单的工程完全可以人工手下，但是当工程非常大的时候，手写`makefile`也是非常麻烦的，如果换了个平台`makefile`又要重新修改。
## cmake
- 这时候就出现了`Cmake`这个工具，`cmake`就可以更加简单的生成`makefile`文件给上面那个`make`用。当然`cmake`还有其他功能，就是可以跨平台生成对应平台能用的`makefile`，你不用再自己去修改了。可是`cmake`根据什么生成`makefile`呢？它又要根据一个叫`CMakeLists.txt`文件（学名：组态档）去生成`makefile`。当然如果你用IDE，类似VS这些一般它都能帮你弄好了，你只需要按一下那个三角形。
## qmake
- `qmake`是什么，先说一下Qt这个东西。Qt是跨平台C++图形用户界面应用程序开发框架。它既可以开发GUI程序，也可用于开发非GUI程序，比如控制台工具和服务器。简单的说就是C++的第三方库，使用这个库你可以很容易生成windows，Linux，MAC os等等平台的图形界面。现在的Qt还包含了开发各种软件一般需要用到的功能模块（网络，数据库，XML，多线程啊等等），比你直接用C++（只带标准内裤那种）要方便和简单。
- 你可以用Qt简简单单就实现非常复杂的功能，是因为Qt对C++进行了扩展，你写一行代码，Qt在背后帮你写了几百上千行，而这些多出来的代码就是靠Qt专有的moc编译器（The Meta-Object Compiler）和uic编译器（User Interface Complier）来重新翻译你那一行代码。问题来了，你在进行程序编译前就必须先调用moc和uic对Qt源文件进行预处理，然后再调用编译器进行编译。上面说的那种普通makefile文件是不适用的，它没办法对qt源文件进行预处理。所以qmake就产生了。
- qmake工具就是Qt公司制造出来，用来生成Qt 专用makefile文件，这种makefile文件就能自动智能调用moc和uic对源程序进行预处理和编译。qmake当然必须也是跨平台的，跟cmake一样能对应各种平台生成对应makefile文件。
- qmake是根据Qt 工程文件（.pro）来生成对应的makefile的。工程文件（.pro）相对来说比较简单，一般工程你都可以自己手写，但是一般都是由Qt的开发环境 Qt Creator自动生成的。
- 还没有完，由于qmake很简单很好用又支持跨平台，而且是可以独立于它的IDE，所以你也可以用在非Qt工程上面，照样可以生成普通的makefile，只要在pro文件中加入CONFIG -= qt 就可以了
### qmake cmake 区别
cmake也是同样支持Qt程序的，cmake也能生成针对qt 程序的那种特殊makefile，

​ 只是cmake的CMakeLists.txt 写起来相对与qmake的pro文件复杂点。

​ qmake 是为 Qt 量身打造的，使用起来非常方便，但是cmake功能比qmake强大。

​ 一般的Qt工程你就直接使用qmake就可以了，cmake的强大功能一般人是用不到的。

​ 当你的工程非常大的时候，又有qt部分的子工程，又有其他语言的部分子工程，据说用cmake会 方便。