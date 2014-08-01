/**
 @file	common.cpp

 @brief	common命名空间方法实现类.
 */

#include "common.h"

namespace common
{

	HMODULE GetSelfModuleHandle()
	{
		MEMORY_BASIC_INFORMATION mbi;
		return ((::VirtualQuery(GetSelfModuleHandle, &mbi, sizeof(mbi)) != 0) ? (HMODULE)mbi.AllocationBase : NULL);
	}

	std::wstring MToWChar(std::string str)
	{
		//获取缓冲区的大小，并申请空间，缓冲区大小是按字符计算的
		int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
		WCHAR *buffer = new WCHAR[len + 1];
		//多字节编码转换成宽字节编码
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
		buffer[len] = '\0';//添加字符串结尾
		//删除缓冲区并返回值
		std::wstring return_value;
		return_value.append(buffer);
		delete[]buffer;
		return return_value;
	}

	std::string WToMChar(std::wstring str)
	{
		using namespace std;
		string return_value;
		//获取缓冲区的大小，并申请空间，缓冲区大小是按字节计算的
		int len = WideCharToMultiByte(CP_ACP, 0, str.c_str(), str.size(), NULL, 0, NULL, NULL);
		char *buffer = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, str.c_str(), str.size(), buffer, len, NULL, NULL);
		buffer[len] = '\0';
		//删除缓冲区并返回值
		return_value.append(buffer);
		delete[]buffer;
		return return_value;
	}
}