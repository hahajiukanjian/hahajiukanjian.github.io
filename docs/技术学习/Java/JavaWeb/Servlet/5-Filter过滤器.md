# Filter过滤器

## 为什么要使用Filter

> ### 当前的OA项目存在什么缺陷？
>
> 假设我们当前的系统有多个功能。需要使用DeptServlet、EmpServlet、OrderServlet等Servlet来实现该功能。
>
> 而以上的Servlet都**需要提前判断用户是否登录**，并且每个Servlet都**需要处理请求、响应的乱码问题。**
>
> 这些都是重复的代码，会造成代码的冗余。显然没有达到代码复用的要求。

这时候我们需要引入Servlet规范中的Filter过滤器来解决以上问题。

## Filter的作用？

- Filter可以在Servlet这个目标程序执行之前添加代码。也可以在目标Servlet执行之后添加代码。之前之后都可以添加过滤规则。
- 一般情况下，都是在过滤器当中编写公共代码。

## 使用步骤？

1. 创建一个Java类，实现jakarta.servlet.Filter接口，并实现这个接口的所有方法

    - ```java
        public interface Filter {
            default void init(FilterConfig filterConfig) throws ServletException {
            }
        
            void doFilter(ServletRequest var1, ServletResponse var2, FilterChain var3) throws IOException, ServletException;
        
            default void destroy() {
            }
        }
        ```

2. 在web.xml文件中对Filter进行配置。这个配置和Servlet很像。

    - ```xml
        <filter>
            <filter-name>filter2</filter-name>
            <filter-class>com.bjpowernode.javaweb.servlet.Filter2</filter-class>
        </filter>
        <filter-mapping>
            <filter-name>filter2</filter-name>
            <url-pattern>*.do</url-pattern>
        </filter-mapping>
        ```

    - 或者使用注解：@WebFilter({"*.do"})

### 注意

- Filter对象默认情况下，在服务器启动的时候会新建对象。而Servlet如果没有特殊配置，是在调用它时才会创建对象

- Servlet是单例的。Filter也是单例的。（单实例。）

- **目标Servlet是否执行，取决于两个条件：**

    1. Filter接口的实现类中的`doFilter`方法编写了`chain.doFilter(request, response);`语句

    2. 用户发送的请求路径与Servlet处理的请求路径一致

- `chain.doFilter(request, response);`这行代码的作用：

    - 执行下一个过滤器，如果没有下一个过滤器，就执行对应的Servlet，最终执行到Servlet结束。与递归的过程相似，遵循栈的数据结构。

- Filter天生的就比Servlet优先级高。

    - /a.do 对应一个Filter，也对应一个Servlet。那么一定是先执行Filter，然后再执行Servlet。

- 关于Filter的配置路径：

    - /a.do、/b.do、/dept/save。这些配置方式都是精确匹配。
    - /* 匹配所有路径。
    - *.do 后缀匹配。不要以 / 开始
    - /dept/*  前缀匹配。

#### 在web.xml文件中进行配置的时候，Filter的执行顺序是什么？

依靠filter-mapping标签的配置位置，越靠上优先级越高。

#### 使用@WebFilter的时候，Filter的执行顺序是怎样的呢？

执行顺序是：比较Filter这个类名。

- 比如：FilterA和FilterB，则先执行FilterA。
- 比如：Filter1和Filter2，则先执行Filter1.

#### Filter的生命周期？

- 和Servlet对象生命周期一致。
- 唯一的区别：Filter默认情况下，在服务器启动阶段就实例化。Servlet不会。

#### Filter过滤器这里有一个设计模式：

- - 责任链设计模式。
            - 过滤器最大的优点：
                - 在程序编译阶段不会确定调用顺序。因为Filter的调用顺序是配置到web.xml文件中的，只要修改web.xml配置文件中filter-mapping的顺序就可以调整Filter的执行顺序。显然Filter的执行顺序是在程序运行阶段动态组合的。那么这种设计模式被称为责任链设计模式。
            - 责任链设计模式最大的核心思想：
                - 在程序运行阶段，动态的组合程序的调用顺序。

## 使用Filter改造OA项目

我们希望将

- 通过获取Session判断用户是否登录的代码整合到Filter实现类中。
- Filter处理的路径设置为整个项目下的所有路径
    - 这会带来一个问题：当我们第一次登录的时候、勾选了10天免登录之后下一次登录的时候、用户第二次登录的时候……这些请求也都会被Filter处理。
    - 显然上面的请求一般情况下是不会携带我们希望的Session信息的。
    - 因此我们需要对上述情况做特殊处理：
        - 获取请求路径，如果请求路径是：`/welcome `,`/index.jsp `,`/login/in`, `/login/out`
        - 这些路径的话，我们不对其进行过滤
- 处理判断Session中是否存了我们想要的属性值、路径的匹配……
    - 如果为true，调用chain.doFilter()方法
    - 如果为false，跳转到登录页面

