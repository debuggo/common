/**
 @file	common.cpp

 @brief	common�����ռ䷽��ʵ����.
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
		//��ȡ�������Ĵ�С��������ռ䣬��������С�ǰ��ַ������
		int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
		WCHAR *buffer = new WCHAR[len + 1];
		//���ֽڱ���ת���ɿ��ֽڱ���
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
		buffer[len] = '\0';//����ַ�����β
		//ɾ��������������ֵ
		std::wstring return_value;
		return_value.append(buffer);
		delete[]buffer;
		return return_value;
	}

	std::string WToMChar(std::wstring str)
	{
		using namespace std;
		string return_value;
		//��ȡ�������Ĵ�С��������ռ䣬��������С�ǰ��ֽڼ����
		int len = WideCharToMultiByte(CP_ACP, 0, str.c_str(), str.size(), NULL, 0, NULL, NULL);
		char *buffer = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, str.c_str(), str.size(), buffer, len, NULL, NULL);
		buffer[len] = '\0';
		//ɾ��������������ֵ
		return_value.append(buffer);
		delete[]buffer;
		return return_value;
	}
}