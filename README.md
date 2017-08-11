# extract_param
使用模板编译期萃取函数形参类型

## 概要
萃取函数的参数类型

```
	template<typename FuncT, uint32_t N = 0>
	struct get_func_param_type_index;
```
FuncT: 函数类型
N: 函数的第N个参数


## 用法声明
`&MyTestKit::get` 这个是个值
`decltype(&MyTestKit::get)`而这个才是类型
下边第一行代码编译失败

```
dd::get_func_param_type_index<&MyTestKit::get, 0>::type;

dd::get_func_param_type_index<decltype(&MyTestKit::get), 0>::type;
```


## 编译
用到的工具
> cmake 2.8+
> vs any version

```
mkdir build
cd build
cmake ..
./extract_param.sln
```

## 其他
将代码中的 `// compile error`部分取消注释，就会编译失败

```
	// compile error
	typedef typename dd::get_func_param_type_index<int, 0>::type A_fun;
```


## 目的
为了实现`MyTestKit2MyTest`这里边的宏操作，所以才搞出的这个提取函数参数的模板。
​:smile:​ ​:happy:​
