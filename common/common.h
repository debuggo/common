/**
 @file	common.h

 @brief	common命名空间文件头
 包含了常用方法
 */
#ifndef COMMON_H
#define COMMON_H
#include <windows.h>
#include <tchar.h>
#include <string>

namespace common
{
	/**
	 @fn	HMODULE GetSelfModuleHandle() } #endif
	
	 @brief	获取本进程模块句柄.
	
	 @author	Debug Go
	 @date	8/1/2014
	
	 @return	本进程的模块句柄.
	 */
	HMODULE GetSelfModuleHandle();

	/**
	 @fn	std::wstring MToWChar(std::string str);
	
	 @brief	ansi转unicode.
	
	 @author	Debug Go
	 @date	8/1/2014
	
	 @param	str	待转换的ansi字符串.
	
	 @return	str 转换完成的unicode字符串.
	 */
	std::wstring MToWChar(std::string str);

	/**
	 @fn	std::string WToMChar(std::wstring str) } #endif
	
	 @brief	unicode转ansi.
	
	 @author	Debug Go
	 @date	8/1/2014
	
	 @param	str	待转换的unicode字符串.
	
	 @return	str 转换后的ansi字符串.
	 */
	std::string WToMChar(std::wstring str);
}


#endif	//COMMON_H
