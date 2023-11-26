# EL表达式

## EL表达式是干什么的？

- Expression Language（表达式语言）

- EL表达式可以代替JSP中的java代码，让JSP文件中的程序看起来更加整洁，美观。
- JSP中夹杂着各种java代码，例如<% java代码 %>、<%=%>等，导致JSP文件很混乱，不好看，不好维护。所以才有了后期的EL表达式。
- **EL表达式可以算是JSP语法的一部分。EL表达式归属于JSP。**

## EL表达式出现在JSP中主要是

- 从某个作用域中取数据，然后将其转换成字符串，然后将其输出到浏览器。这就是EL表达式的功效。三大功效：
    1. 第一功效：从某个域中取数据。
        - 四个域：
            - pageContext
            - request
            - session
            - application
                -
    2. 第二功效：将取出的数据转成字符串。
        - 如果是一个java对象，也会自动调用java对象的toString方法将其转换成字符串。
    3. 第三功效：将字符串输出到浏览器。
        - 和这个一样：<%= %>，将其输出到浏览器。

## 使用

语法格式：${表达式}

```jsp
<%
	// 创建User对象
	User user = new User();
	user.setUsername("jackson");
	user.setPassword("1234");
	user.setAge(50);

	// 将User对象存储到某个域当中。一定要存，因为EL表达式只能从某个范围中取数据。
	// 数据是必须存储到四大范围之一的。
	request.setAttribute("userObj", user);
%>

<%--使用EL表达式取--%>
${这个位置写什么？？？？这里写的一定是存储到域对象当中时的name}
要这样写：
${userObj}
等同于java代码：<%=request.getAttribute("userObj")%>
你不要这样写：${"userObj"}

面试题：
	${abc} 和 ${"abc"}的区别是什么？
		${abc}表示从某个域中取出数据，并且被取的这个数据的name是"abc"，之前一定有这样的代码: 域.setAttribute("abc", 对象);
		${"abc"} 表示直接将"abc"当做普通字符串输出到浏览器。不会从某个域中取数据了。

${userObj} 底层是怎么做的？从域中取数据，取出user对象，然后调用user对象的toString方法，转换成字符串，输出到浏览器。

<%--如果想输出对象的属性值，怎么办？--%>
${userObj.username} 使用这个语法的前提是：User对象有getUsername()方法。
${userObj.password} 使用这个语法的前提是：User对象有getPassword()方法。
${userObj.age} 使用这个语法的前提是：User对象有getAge()方法。
${userObj.email} 使用这个语法的前提是：User对象有getEmail()方法。
EL表达式中的. 这个语法，实际上调用了底层的getXxx()方法。
注意：如果没有对应的get方法，则出现异常。报500错误。

${userObj.addr222.zipcode}
以上EL表达式对应的java代码：
user.getAddr222().getZipcode()
```

综上所述EL表达式是从四级作用域中获取他们的属性

- pageContext > request > session > application
- 通过`getAttribute`获取

- 如果存入作用域中的属性是一个Javabean的话，可以直接通过`.`来输出类中的属性
    - User.xxx   这个xxx是User类中的getXxx方法

- `${User.address.email}`
- `<%= ((User)request.getAttribute("User")).getAddress().getEmail()`

## pageContext

**需要注意！**

在EL表达式中，只有pageContext对象

- EL表达式中有四个隐含的隐式的范围：

    - pageScope 对应的是 pageContext范围。

    - requestScope 对应的是 request范围。

    - sessionScope 对应的是 session范围。

    - applicationScope 对应的是 application范围。

- EL表达式对null进行了预处理。如果是null，则向浏览器输出一个空字符串。

- EL表达式取数据的时候有两种形式：

    - 第一种：.  （大部分使用这种方式）

    - 第二种：[ ] （如果存储到域的时候，这个name中含有特殊字符，可以使用 [ ]）

        - ```java
            request.setAttribute("abc.def", "zhangsan");
            ${requestScope.abc.def} 这样是无法取值的。
            应该这样：${requestScope["abc.def"]}
            ```

- EL表达式输出数组、JavaBean数组、LIst集合、Set集合的方式
    - 其中Set集合没有索引。无法通过`[索引]`的方式获取内容

```jsp
        <h3>数组的输出方式</h3><br>
        n1[0]：${names1[0]}<br>

        <h3>JavaBean的数组的输出方式</h3><br>
        u[0]：${users[0].name}<br>

        <h3>List集合的输出方式</h3><br>
        n2[0]：${names2[0]}<br>

        <h3>Set集合的输出方式</h3><br>
        names3：${names3}<br>
```


- page指令当中，有一个属性，可以忽略EL表达式

```java
        <%@page contentType="text/html;charset=UTF-8" isELIgnored="true" %>
        isELIgnored="true" 表示忽略EL表达式
        isELIgnored="false" 表示不忽略EL表达式。（这是默认值）

        isELIgnored="true" 这个是全局的控制。

        可以使用反斜杠进行局部控制：\${username} 这样也可以忽略EL表达式。
```

- 通过EL表达式获取应用的根：

    - `${pageContext.request.contextPath}`

## EL表达式中其他的隐式对象：

- pageContext

- param

- paramValues

- initParam

```jsp
    如果URL为http://localhost:8080/JSP/5.jsp?name="张三"<br>
    jsp:<%=request.getParameter("name")%><br>
    EL :${param.name}<br>

    <hr>
    如果URL为http://localhost:8080/JSP/5.jsp?aihao="骑马"&aihao="剑术"<br>
    jsp:<%=request.getParameterValues("aihao")%><br>
    EL: ${paramValues.aihao}<br>
    EL: ${paramValues.aihao[0]}<br>
    EL: ${paramValues.aihao[1]}<br>

    <hr>
    获取web.xml的内容<br>
    jsp:<%=application.getInitParameter("pageSize")%><br>
    jsp:<%=application.getInitParameter("pageNum")%><br>
    EL: ${initParam.pageSize}<br>
    EL: ${initParam.pageNum}<br>

```

## EL表达式的运算符

- 算术运算符
    - +、-、*、/、%
- 关系运算符
    - [ ] == eq != > >= < <=
- 逻辑运算符
    - [ ] !  && ||  not and or
- 条件运算符
    - [ ] ? :
- 取值运算符
    - [ ]和.
- empty运算符
    - [ ] empty运算符的结果是boolean类型
    - [ ] ${empty param.username}
    - [ ] ${not empty param.username}
    - [ ] ${!empty param.password}

