#ifndef __extract_param_type_hpp__
#define __extract_param_type_hpp__

#include <stdint.h>

namespace dd
{

	// template<typename... Args>
	// struct VaribleParamTypeSize;
	// 
	// template<>
	// struct VaribleParamTypeSize<>
	// {
	// 	const uint32_t vaue = 0;
	// };
	// 
	// template<typename head, typename... left>
	// struct VaribleParamTypeSize<head, left...>
	// {
	// 	const uint32_t vaue = VaribleParamTypeSize<left...>::vaue + 1;
	// };
	

	// struct NullType;

	template<uint32_t N, typename... Args> struct VaribleParamTypeIndex;

	template<uint32_t N>
	struct VaribleParamTypeIndex<N>
	{
		// cancel typedef, to create a compile error
		// typedef NullType type;
	};

	template<typename head, typename... left>
	struct VaribleParamTypeIndex<0, head, left...>
	{
		typedef head type;
	};

	template<uint32_t N, typename head, typename... left>
	struct VaribleParamTypeIndex<N, head, left...>
	{
		typedef typename VaribleParamTypeIndex<N - 1, left...>::type type;
	};





	template<typename FuncT, uint32_t N = 0>
	struct get_func_param_type_index;


	template<typename C, typename R, typename ... Arg, uint32_t N>
	struct get_func_param_type_index<R(C::*)(Arg...) const, N>
	{
		typedef typename VaribleParamTypeIndex<N, Arg...>::type type;
	};

	template<typename C, typename R, typename ... Arg, uint32_t N>
	struct get_func_param_type_index<R(C::*)(Arg...), N>
	{
		typedef typename VaribleParamTypeIndex<N, Arg...>::type type;
	};

	template<typename R, typename ... Arg, uint32_t N>
	struct get_func_param_type_index<R(*)(Arg...), N>
	{
		typedef typename VaribleParamTypeIndex<N, Arg...>::type type;
	};

}


#endif

