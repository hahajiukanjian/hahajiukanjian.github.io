# Vue的引入

Vue (读音 /vjuː/，类似于 **view**) 是一套用于构建用户界面的**渐进式框架**。

## Vue2的安装

在学习前期阶段，我们使用Vue2。

[Vue2下载链接](https://v2.cn.vuejs.org/v2/guide/installation.html)

![image-20231124102711024](./Vue.assets/image-20231124102711024.png)

## 引入Vue2

```html
<script src="../js/vue.js"></script>
// ../js/vue.js为vue所在的路径
```

## 最简单的Vue程序

```html
<div id="app"></div>
<script>
    // 第一步
	const myVue = new Vue({
		template : '<h1>Hello Vue!!!</h1>'
	})
    // 第二步
	myVue.$mount('#app')
</script>
```

### 第一步 创建Vue实例

1. 为什么不直接调用Vue()函数？
    - 不行，因为直接调用Vue()函数，不创建实例的话，会出现以下错误：
    - `Vue is a constructor and should be called with the new keyword`
2. Vue(options)构造函数中，options参数是什么
    - option翻译为选项  options翻译为多个选项
    - Vue框架要求这个options参数必须是一个纯粹的JS对象：{}
    - 在{}对象中可以编写大量的key:value对。
    - 一个key:value对就是一个配置项。
    - 主要是通过options这个参数来给Vue实例指定多个配置项。
3. 关于template配置项
    - template翻译为：模板。
    - template配置项用来指定什么？用来指定模板语句，模板语句是一个字符串形式的。
    - 什么是模板语句？
        - Vue框架自己制定了一些具有特殊含义的特殊符号。
        - Vue的模板语句是Vue框架自己搞的一套语法规则。
        - 我们写Vue模板语句的时候，不能乱写，要遵守Vue框架的模板语法规则。
        - 模板语句可以是一个纯粹的HTML代码，也可以是Vue中的特殊规则。也可以是HTML代码 + Vue的特殊规则。
        - template后面的模板语句会被Vue框架的编译器进行编译，转换成浏览器能够识别的HTML代码。

### 第二步 将Vue实例挂载到id='app'的元素位置。

1. Vue实例都有一个$mount()方法，这个方法的作用是什么？
    - 将Vue实例挂载到指定位置。
2. #app 显然是ID选择器。这个语法借鉴了CSS。

## 模板语句template的数据来源

### 谁可以给模板语句提供数据支持呢

data选项。

data配置项的专业叫法：Vue 实例的数据对象.（data实际上是给整个Vue实例提供数据来源的。）

#### 项的类型是什么？

Object | Function （对象或者函数）

a是对象的话，对象必须是纯粹的对象 (含有零个或多个的 key/value 对)

#### data数据如何插入到模板语句当中？

{{}} 这是Vue框架自己搞的一套语法，别的框架看不懂的，浏览器也是不能够识别的。
Vue框架自己是能够看懂的。这种语法在Vue框架中被称为：模板语法中的插值语法。（有的人把他叫做胡子语法。）

```vue
{{data的key}}
```


## 模板语句的配置项

1. template后面指定的是模板语句，但是模板语句中只能有一个根节点。

2. 只要data中的数据发生变化，模板语句一定会重新编译。（只要data变，template就会重新编译，重新渲染）

3. 如果使用template配置项的话，指定挂载位置的元素会被替换。

    - ```html
        原本的<div id="app"></div>会被替代
        ```

4. 好消息：目前我们可以不使用template来编写模板语句。这些模板语句可以直接写到html标签中。Vue框架能够找到并编译，然后渲染。如果直接将模板语句编写到HTML标签中，指定的挂载位置就不会被替换了。

5. 关于$mount('#app')

    1. 也可以不使用$mount('#app')的方式进行挂载
    2. 在Vue中有一个配置项：el
    3. el配置项和$mount()可以达到同样的效果。

6. el配置项的作用？

    1. 告诉Vue实例去接管哪个容器。
    2. el : '#app'，表示让Vue实例去接管id='app'的容器。
    3. el其实是element的缩写。被翻译为元素。



## 解决浏览器控制台的错误信息

1. 我们使用开发版本的vue.js时，控制台会出现白色字体的警告。可以用以下方法关掉警告

- 在每次写代码时，在script标签内写入`Vue.config.productionTip=false`，但是这样有些时候会不起作用
    - 可能是vue的版本问题，也可能是浏览器的内核问题
- 更换生产版本的vue
- 更改开发版本vue的源码：找到`productionTip`这个全局变量，将它的值设置为`false`

2. 安装vue.jsp devtools，关闭另一个白色字体的警告
3. 在vscode中，使用LiveServer运行html文件时，会将html放到一个服务器上运行。有些时候服务器会找不到一些原本的资源文件。我们只需要找到对应的资源文件，将其放到相应的位置即可。（这是废话）

## Vue实例与容器的关系

实例就是new出来的一个Vue对象

容器就是Vue对象接管的html标签

**一个Vue实例只能接管一个容器**

**一个容器也只能被一个Vue实例接管**

# Vue核心语法

## 模版语法-插值

`{{}}`

### 主要研究：{{这里可以写什么}}

1. 在data中声明的变量、函数等都可以。
2. 常量都可以。    
3. 只要是合法的javascript表达式，都可以。
4. 模板表达式都被放在沙盒中，只能访问全局变量的一个白名单，如 Math 和 Date 等。
    'Infinity,undefined,NaN,isFinite,isNaN,' 'parseFloat,parseInt,decodeURI,decodeURIComponent,encodeURI,encodeURIComponent,' 
    'Math,Number,Date,Array,Object,Boolean,String,RegExp,Map,Set,JSON,Intl,' 
    'require'

```html
    <div id="app">
        <!-- 在data中声明的 -->
        <!-- 这里就可以看做在使用msg变量。 -->
        <h1>{{msg}}</h1>
        <h1>{{sayHello()}}</h1>
        <!-- <h1>{{i}}</h1> -->
        <!-- <h1>{{sum()}}</h1> -->

        <!-- 常量 -->
        <h1>{{100}}</h1>
        <h1>{{'hello vue!'}}</h1>
        <h1>{{3.14}}</h1>

        <!-- javascript表达式 -->
        <h1>{{1 + 1}}</h1>
        <h1>{{'hello' + 'vue'}}</h1>
        <h1>{{msg + 1}}</h1>
        <h1>{{'msg' + 1}}</h1>
        <h1>{{gender ? '男' : '女'}}</h1>
        <h1>{{number + 1}}</h1>
        <h1>{{'number' + 1}}</h1>
        <h1>{{msg.split('').reverse().join('')}}</h1>

        <!-- 错误的：不是表达式，这是语句。 -->
        <!-- <h1>{{var i = 100}}</h1> -->

        <!-- 在白名单里面的 -->
        <h1>{{Date}}</h1>
        <h1>{{Date.now()}}</h1>
        <h1>{{Math}}</h1>
        <h1>{{Math.ceil(3.14)}}</h1>

    </div>

    <!-- vue程序 -->
    <script>

        // 用户自定义的一个全局变量
        var i = 100
        // 用户自定义的一个全局函数
        function sum(){
            console.log('sum.....');
        }

        new Vue({
            el : '#app',
            data : {
                number : 1,
                gender : true,
                msg : 'abcdef',  // 为了方便沟通，以后我们把msg叫做变量。（这行代码就可以看做是变量的声明。）
                sayHello : function(){
                    console.log('hello vue!');
                }
            }
        })
    </script>
```

## 模版语法-指令

