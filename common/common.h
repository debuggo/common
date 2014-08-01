/**
 @file	common.h

 @brief	common�����ռ��ļ�ͷ
 �����˳��÷���
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
	
	 @brief	��ȡ������ģ����.
	
	 @author	Debug Go
	 @date	8/1/2014
	
	 @return	�����̵�ģ����.
	 */
	HMODULE GetSelfModuleHandle();

	/**
	 @fn	std::wstring MToWChar(std::string str);
	
	 @brief	ansiתunicode.
	
	 @author	Debug Go
	 @date	8/1/2014
	
	 @param	str	��ת����ansi�ַ���.
	
	 @return	str ת����ɵ�unicode�ַ���.
	 */
	std::wstring MToWChar(std::string str);

	/**
	 @fn	std::string WToMChar(std::wstring str) } #endif
	
	 @brief	unicodeתansi.
	
	 @author	Debug Go
	 @date	8/1/2014
	
	 @param	str	��ת����unicode�ַ���.
	
	 @return	str ת�����ansi�ַ���.
	 */
	std::string WToMChar(std::wstring str);
}


#endif	//COMMON_H
