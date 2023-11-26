# JSP

> ##  分析使用纯粹Servlet开发web应用的缺陷
>
> 在Servlet当中编写HTML/CSS/JavaScript等前端代码。存在什么问题？
>
> - java程序中编写前端代码，编写难度大。麻烦。
> - java程序中编写前端代码，显然程序的耦合度非常高。
> - java程序中编写前端代码，代码非常不美观。
> - java程序中编写前端代码，维护成本太高。（非常难于维护）
>     - 修改小小的一个前端代码，只要有改动，就需要重新编译java代码，生成新的class文件，打一个新的war包，重新发布。
>
> Servlet（Java程序）能不能不写了，让机器自动生成。我们程序员只需要写这个Servlet程序中的“前端的那段代码”，然后让机器将我们写的“前端代码”自动翻译生成“Servlet这种java程序”。然后机器再自动将“java”程序编译生成"class"文件。然后再使用JVM调用这个class中的方法。

## JSP是什么？

JSP是：JavaServer Pages的缩写。（基于Java语言实现的服务器端的页面。）

Servlet是JavaEE的13个子规范之一，那么JSP也是JavaEE的13个子规范之一。

JSP是一套规范。所有的web容器/web服务器都是遵循这套规范的，都是按照这套规范进行的“翻译”

每一个web容器/web服务器都会内置一个JSP翻译引擎。

对JSP进行错误调试的时候，还是要直接打开JSP文件对应的java文件，检查java代码。

### JSP实际上就是一个Servlet。

- 当我们访问 index.jsp 时，**实际上底层执行的是：index_jsp.class 这个java程序。**

- **这个index.jsp会被tomcat翻译生成index_jsp.java文件，然后tomcat服务器又会将index_jsp.java编译生成index_jsp.class文件**

- index_jsp 类继承 HttpJspBase，而HttpJspBase类继承的是HttpServlet。所以index_jsp类就是一个Servlet类。
- jsp的生命周期和Servlet的生命周期完全相同。完全就是一个东西。没有任何区别。
- jsp和servlet一样，都是单例的。（假单例。）

### 为什么jsp文件第一次访问时比较慢？

- 为什么大部分的运维人员在给客户演示项目的时候，为什么提前先把所有的jsp文件先访问一遍。
    - 要把jsp文件翻译生成java源文件
    - java源文件要编译生成class字节码文件
    - 然后通过class去创建servlet对象
    - 然后调用servlet对象的init方法
    - 最后调用servlet对象的service方法。
- 第二次就比较快了，为什么？
    - 因为第二次直接调用单例servlet对象的service方法即可。

### JSP既然本质上是一个Servlet，那么JSP和Servlet到底有什么区别呢？

职责不同：

- Servlet的职责是什么：收集数据。（Servlet的强项是逻辑处理，业务处理，然后链接数据库，获取/收集数据。）
- JSP的职责是什么：展示数据。（JSP的强项是做数据的展示）

## JSP的基础语法

### 在jsp文件中直接编写文字，都会自动被翻译到哪里？

翻译到servlet类的service方法的out.write("翻译到这里")，直接翻译到双引号里，被java程序当做普通字符串打印输出到浏览器。

### <% java语句; %>

- 在这个符号当中编写的被视为java程序，被翻译到Servlet类的service方法内部。
- 这里你要细心点，你要思考，在<% %>这个符号里面写java代码的时候，你要时时刻刻的记住你正在“方法体”当中写代码，方法体中可以写什么，不可以写什么，你心里是否明白呢？
- 在service方法当中编写的代码是有顺序的，方法体当中的代码要遵循自上而下的顺序依次逐行执行。
- service方法当中不能写静态代码块，不能写方法，不能定义成员变量。。。。。。
- 在同一个JSP当中 <%%> 这个符号可以出现多个。

### <%! %>

- 在这个符号当中编写的java程序会自动翻译到service方法之外。
- 这个语法很少用，为什么？不建议使用，因为在service方法外面写静态变量和实例变量，都会存在线程安全问题，因为JSP就是servlet，servlet是单例的，多线程并发的环境下，这个静态变量和实例变量一旦有修改操作，必然会存在线程安全问题。

### <%= %>

- 怎么向浏览器上输出一个java变量。
- <% String name = “jack”;  out.write("name = " + name); %>
- 注意：以上代码中的out是JSP的九大内置对象之一。可以直接拿来用。当然，必须只能在service方法内部使用。
- 如果向浏览器上输出的内容中没有“java代码”，例如输出的字符串是一个固定的字符串，可以直接在jsp中编写，不需要写到<%%> 这里。
- 如果输出的内容中含有“java代码”，这个时候可以使用以下语法格式：
    - <%= %> 注意：在=的后面编写要输出的内容。
    - <%= %> 这个符号会被翻译到哪里？最终翻译成什么？
        - 翻译成了这个java代码：   out.print();
        - 翻译到service方法当中了。
    - 什么时候使用<%=%> 输出呢？输出的内容中含有java的变量，输出的内容是一个动态的内容，不是一个死的字符串。如果输出的是一个固定的字符串，直接在JSP文件中编写即可。

### <%--  --%>

在JSP中如何编写JSP的专业注释

- <%--JSP的专业注释，不会被翻译到java源代码当中。--%>
- <!--这种注释属于HTML的注释，这个注释信息仍然会被翻译到java源代码当中，不建议。-->

### <%@page %>指令

<%@page  contentType="text/html;charset=UTF-8"%>

- page指令，通过contentType属性用来设置响应的内容类型。

## JSP基础语法---指令讲解

### 指令的作用

指导JSP的翻译引擎如何工作（指导当前的JSP翻译引擎如何翻译JSP文件。）

### 指令都有哪些

- inclue指令：包含指令，在JSP中完成静态包含，很少用（不学）
- taglib指令：引入标签库的指令。在JSTL标签库的时候再学习
- page  指令：重点学习

**<%@指令名  属性名=属性值  属性名=属性值  属性名=属性值....%>**

#### page指令

##### session

```jsp
<%@page session="true|false" %>
true表示启用JSP的内置对象session，表示一定启动session对象。没有session对象会创建。
如果没有设置，默认值就是session="true"
session="false" 表示不启动内置对象session。当前JSP页面中无法使用内置对象session。
```

##### contentType

```jsp
<%@page contentType="text/json" %>
contentType属性用来设置响应的内容类型
但同时也可以设置字符集。
<%@page contentType="text/json;charset=UTF-8" %>
```

##### pageEncoding

```jsp
<%@page pageEncoding="UTF-8" %>
pageEncoding="UTF-8" 表示设置响应时采用的字符集。
```

##### import

```jsp
<%@page import="java.util.List, java.util.Date, java.util.ArrayList" %>
<%@page import="java.util.*" %>
import语句，导包。
```

##### errorPage

```jsp
<%@page errorPage="/error.jsp" %>
当前页面出现异常之后，跳转到error.jsp页面。
errorPage属性用来指定出错之后的跳转位置。
```

##### isErrorPage

```jsp
<%@page isErrorPage="true" %>
表示启用JSP九大内置对象之一：exception
默认值是false。
```

## 九大内置对象

jakarta.servlet.jsp.PageContext pageContext

jakarta.servlet.http.HttpServletRequest request

jakarta.servlet.http.HttpSession session

jakarta.servlet.ServletContext application

jakarta.servlet.jsp.JspWriter out

jakarta.servlet.http.HttpServletResponse response

java.lang.Throwable exception

jakarta.servlet.ServletConfig config

java.lang.Object page

### 四级作用域

```java
jakarta.servlet.jsp.PageContext				pageContext
jakarta.servlet.http.HttpServletRequest		request
jakarta.servlet.http.HttpSession 			session
jakarta.servlet.ServletContext 				application
```

作用域的大小排序为

pageContext `<` request `<` session `<` application

页面域 `<` 请求域 `<` 会话域 `<` 应用域

它们都有`setAttribute` `getAttribute` `removeAttribute`方法

### 其余的内置对象

`out | response`

`exception`

`page ===> this`

`config`









