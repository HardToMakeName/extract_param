#include "extract_param_type.hpp"

#include <type_traits>



class A
{
public:
	uint8_t fun(uint16_t, uint32_t, uint64_t) const
	{
		return 0;
	}


	void overload_func(uint8_t) const
	{
		(void)"do something";
	}

	void overload_func(uint8_t)
	{
		(void)"do something";
	}
};



uint8_t Func(A *a, uint16_t, uint32_t, uint64_t)
{
	return 0;
}

void test();

int main(int argc, char* argv[])
{
	// compile error
	// typedef typename dd::get_func_param_type_index<int, 0>::type A_fun; 


	// compile error. 
	// 	typedef std::remove_reference<dd::get_func_param_type_index<decltype(&A::overload_func), 0>::type>::type  A_OverLoadFuncError;
	// 	static_assert(std::is_same<A_OverLoadFuncError, uint8_t>::value, "param type error");


	typedef void (A::*OverLoadFuncConst)(uint8_t) const;
	typedef std::remove_reference<dd::get_func_param_type_index<OverLoadFuncConst, 0>::type>::type  A_OverLoadFuncConst;
	static_assert(std::is_same<A_OverLoadFuncConst, uint8_t>::value, "param type error");

	typedef void (A::*OverLoadFunc)(uint8_t);
	typedef std::remove_reference<dd::get_func_param_type_index<OverLoadFunc, 0>::type>::type  A_OverLoadFunc;
	static_assert(std::is_same<A_OverLoadFunc, uint8_t>::value, "param type error");

	/*成员函数*/
	typedef std::remove_reference<dd::get_func_param_type_index<decltype(&A::fun), 0>::type>::type  A_FUN;
	static_assert(std::is_same<A_FUN, uint16_t>::value, "param type error");

	typedef dd::get_func_param_type_index<decltype(&A::fun), 0>::type A_param0;
	static_assert(std::is_same<A_param0, uint16_t>::value, "param type error");

	typedef dd::get_func_param_type_index<decltype(&A::fun), 1>::type A_param1;
	static_assert(std::is_same<A_param1, uint32_t>::value, "param type error");


	typedef dd::get_func_param_type_index<decltype(&A::fun), 2>::type A_param2;
	static_assert(std::is_same<A_param2, uint64_t>::value, "param type error");

	// compile error
	// typedef dd::get_func_param_type_index<decltype(&A::fun), 3>::type A_param3;
	// static_assert(false,  "param index out of range");


	/*公共函数*/
	typedef dd::get_func_param_type_index<decltype(&Func), 0>::type Func_param0;
	static_assert(std::is_same<Func_param0, A*>::value, "param type error");

	typedef dd::get_func_param_type_index<decltype(&Func), 1>::type Func_param1;
	static_assert(std::is_same<Func_param1, uint16_t>::value, "param type error");


	typedef dd::get_func_param_type_index<decltype(&Func), 2>::type Func_param2;
	static_assert(std::is_same<Func_param2, uint32_t>::value, "param type error");


	typedef dd::get_func_param_type_index<decltype(&Func), 3>::type Func_param3;
	static_assert(std::is_same<Func_param3, uint64_t>::value, "param type error");


	// compile error
	// typedef dd::get_func_param_type_index<decltype(&Func), 4>::type Func_param4;
	// static_assert(false,  "param index out of range");

	test();


	return 0;
}


class B
{

};


class C
{

};


class MyTestKit
{
public:
	void getA(A&) const {}
	void getB(B&) const {}
	void getC(C&) const {}


	void setA(A&) const {}
	void setB(B&) const {}
	void setC(C&) const {}

private:
	void *_data;
};

class MyTest
{
public:
	void getA(A&) const {}
	void getB(B&) const {}
	void getC(C&) const {}


	void setA(A&) const {}
	void setB(B&) const {}
	void setC(C&) const {}


private:

	void *_data;
};




void MyTestKit2MyTest(const MyTestKit &from, MyTest &to)
{
#define single_operator(get, set) \
	std::remove_reference<dd::get_func_param_type_index<decltype(&MyTestKit::get), 0>::type>::type get##Src; \
	from.get(get##Src); \
	to.set(get##Src);


	single_operator(getA, setA);
	single_operator(getB, setB);
	single_operator(getC, setC);
}


void test()
{
	MyTestKit from;
	MyTest to;
	MyTestKit2MyTest(from, to);
}