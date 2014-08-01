/**
 @file	Ini.cpp

 @brief	ini��ʵ���ļ�.
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
			* ����boost::property_tree::iniparser��read_ini������ȡini�ļ�
			* ��������path��Ч,�׳�file_parser_error(�ļ���������)
			* ini�����ݴ����쳣,�׳�ini_parser_error(ini��������)
			*/
			read_ini(path_, ini_boot_);
			ret = true;
		}
		catch (ini_parser_error err)
		{
			WRITE_LOG(LOG_LEVEL_FATAL, L"ini�ṹ%s", err.what());
			return ret;
		}
		catch (file_parser_error err)
		{
			WRITE_LOG(LOG_LEVEL_FATAL, L"ini�ļ��쳣,%s", err.what());
			return ret;
		}
		return ret;
	}

}