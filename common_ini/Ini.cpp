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
			WRITE_LOG(LOG_LEVEL_FATAL, L"ini�ṹ�쳣,%s", err.what());
			return ret;
		}
		catch (file_parser_error err)
		{
			WRITE_LOG(LOG_LEVEL_FATAL, L"ini�ļ��쳣,%s", err.what());
			return ret;
		}
		return ret;
	}

	template <class T>
	bool common::ini::get(const std::string &section, const std::string &key, T &value)
	{
		bool ret = false;
		if (ini_boot_.empty())	//���ini�ĸ��ڵ�Ϊ��,��û�л�ȡ��ָ����ֵ.
		{
			//ȡһ��ini�Ľڵ�
			if (!setpath(path_))
				return ret;	//�������������ȡ���ش���
		}
		
		try
		{
			value = ini_boot_.get(section + "." + key);
			ret = true;
		}
		catch (ini_parser_error err)
		{
			WRITE_LOG(LOG_LEVEL_FATAL, L"ini�ṹ�쳣,%s", err.what());
		}

		return ret;
		
	}
}