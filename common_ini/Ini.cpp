/**
 @file	Ini.cpp

 @brief	ini的实现文件.
 */

#include "Ini.h"
#include "../common_log/TextLog.h"
#include "boost/property_tree/ini_parser.hpp"
namespace common
{

	ini::ini()
	{
	}


	ini::~ini()
	{
	}

	bool ini::getiniroot()
	{
		bool ret = false;
		if (path_.empty())
		{
			return ret;
		}
		using namespace boost::property_tree;
		try
		{
			/**
			* 利用boost::property_tree::iniparser的read_ini方法读取ini文件
			* 如果出入的path无效,抛出file_parser_error(文件分析错误)
			* ini的内容存在异常,抛出ini_parser_error(ini分析错误)
			*/
			read_ini(path_, ini_boot_);
			ret = true;
		}
		catch (ini_parser_error err)
		{
			WRITE_LOG(LOG_LEVEL_FATAL, L"ini结构异常,%s", err.what());
			return ret;
		}
		catch (file_parser_error err)
		{
			WRITE_LOG(LOG_LEVEL_FATAL, L"ini文件异常,%s", err.what());
			return ret;
		}
		return ret;
	}

	template <class T>
	bool common::ini::get(const std::string &section, const std::string &key, T &value)
	{
		bool ret = false;
		if (ini_boot_.empty())	//如果ini的跟节点为空,则没有获取到指定的值.
		{
			//取一次ini的节点
			if (!setpath(path_))
				return ret;	//如果不能正常获取返回错误
		}
		
		try
		{
			value = ini_boot_.get(section + "." + key);
			ret = true;
		}
		catch (ini_parser_error err)
		{
			WRITE_LOG(LOG_LEVEL_FATAL, L"ini结构异常,%s", err.what());
		}

		return ret;
		
	}
}