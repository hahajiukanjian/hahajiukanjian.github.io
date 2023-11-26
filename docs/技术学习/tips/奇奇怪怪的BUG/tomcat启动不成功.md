 ## 背景介绍：

 电脑中既有tomcat9又有tomcat10。使用以下方法灵活的使用tomcat

 ```shell
 # 配置tomcat9和10的环境变量
 export TOMCAT_9_HOME=/Users/hahajiukanjian/.config/apache-tomcat-9.0.80
 export TOMCAT_10_HOME=/Users/hahajiukanjian/.config/apache-tomcat-10.1.13
 export TOMCAT_HOME=$TOMCAT_10_HOME
 ```

 只需要更改$TOMCAT_HOME的值就好。

## tomcat9无法运行jdk17编译的内容

 当我使用tomcat9运行jdk17编译出的Servlet内容时，浏览器出现了500的错误。

 `java.lang.UnsupportedClassVersionError: com/hahajiukanjian/HelloServlet has been compiled by a more recent version of the Java Runtime (class file version 61.0), this version of the Java Runtime only recognizes class file versions up to 52.0 (无法载入的类 [com.hahajiukanjian.HelloServlet])`

 这个错误表明Servlet类`com.hahajiukanjian.HelloServlet`是使用Java Runtime的版本61.0进行编译的，但你的服务器上的Java Runtime只能识别版本52.0及以下的类文件。这意味着你需要将你的Servlet类编译为与服务器上的Java Runtime版本兼容的版本。

 也就是说，我需要更换到tomcat10版本。（具体的解决办法还不知道，只知道更换新版本）

 ## tomcat10启动后，浏览器无法访问。

 在我更换后，启动tomcat时，没有出现错误。但是浏览器访问`localhost:8080`失败。

 关闭tomcat时却出现了

 ```shell
 $ sudo ./catalina.sh stop
 Using CATALINA_BASE:   /Users/hahajiukanjian/.config/apache-tomcat-10.1.13
 Using CATALINA_HOME:   /Users/hahajiukanjian/.config/apache-tomcat-10.1.13
 Using CATALINA_TMPDIR: /Users/hahajiukanjian/.config/apache-tomcat-10.1.13/temp
 Using JRE_HOME:        /Library/Internet Plug-Ins/JavaAppletPlugin.plugin/Contents/Home
 Using CLASSPATH:       /Users/hahajiukanjian/.config/apache-tomcat-10.1.13/bin/bootstrap.jar:/Users/hahajiukanjian/.config/apache-tomcat-10.1.13/bin/tomcat-juli.jar
 Using CATALINA_OPTS:   
 Unrecognized option: --add-opens=java.base/java.lang=ALL-UNNAMED
 Error: Could not create the Java Virtual Machine.
 Error: A fatal exception has occurred. Program will exit.
 ```

 仔细查看发现JRE_HOME路径不正确，在zshrc中配置JRE_HOME后，关闭tomcat出现的还是原本的错误路径。

需要在`catalina.sh`中添加以下内容：`export JRE_HOME=/path/to/your/jre`

