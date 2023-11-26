memset 某个结构（或其它的数据类型）在C语言中是很常见的代码，其目的是对结构（或其它的数据类型）进行初始化，通常都是将变量置为NULL或者0。在C++ 中，针对类对象除了用构造函数初始化对象外，也可以使用memset来进行初始化操作（确实有这种情况，不得已而为之，请大家不要把鸡蛋砸过来！）。但是 一定要注意以下所说的这种情况：如果类包含虚拟函数，则不能用 memset 来初始化类对象。下面是一个例子：

``` C++
class GraphicsObject
{
protected:
    char *m_pcName;
    int    m_iId;
    //etc
public:
    virtual void Draw() {}
    virtual int Area() {}
    char* Name() { return m_pcName;}
};

class Circle: public GraphicsObject
{
    void Draw() { /*draw something*/ }
    int Area() { /*calculate Area*/ }
};

void main()
{
    GraphicsObject *obj = new Circle; // 创建对象
    memset((void *)obj,NULL,sizeof(Circle)); // memset to 0
    obj->Name(); // 非虚函数调用没问题
    obj->Draw(); // 在这里死得很难看
}
```

结果我就不说了。因为每个包含虚函数的类对象都有一个指针指向虚函数表（vtbl）。这个指针被用于解决运行时以及动态类型强制转换时虚函数的调用问题。该 指针是被隐藏的，对程序员来说，这个指针也是不可存取的。当进行memset操作时，这个指针的值也要被overwrite，这样一来，只要一调用虚函 数，程序便崩溃。这在很多由C转向C++的程序员来说，很容易犯这个错误，而且这个错误很难查。
为了避免这种情况，记住对于有虚拟函数的类对象，决不能使用 memset 来进行初始化操作。而是要用缺省的构造函数或其它的 init 例程来初始化成员变量。


