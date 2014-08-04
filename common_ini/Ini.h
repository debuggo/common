/**
 @file	Ini.h
 @brief Ini���ͷ�ļ�.
 */

#ifndef COMMON_INI_H
#define COMMON_INI_H
#include <string>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ini_parser.hpp"
#include "../common/common.h"
namespace common
{
	/**
	 @class	ini
	 @brief	ini��.
	 @author	Debug Go
	 @date	8/1/2014
	 */
	class ini
	{
	public:

		/**
		 @fn	ini::ini();
		 @brief	Ĭ�Ϲ��캯��.
		 @author	Debug Go
		 @date	8/1/2014
		 */
		ini();

		/**
		 @fn	ini::ini(const std::string &path);
		 @brief	����ͬʱ����path_��ֵ.
		 @author	Debug Go
		 @date	8/1/2014
		 @param	path	ini�ļ���·��.
		 @see path_
		 @see setpath() getiniroot()
		 */
		ini(const std::string &path){ setpath(path); }

		/**
		 @fn	virtual ini::~ini();
		 @brief	Ĭ�ϵ���������.
		 @author	Debug Go
		 @date	8/1/2014
		 */
		virtual ~ini();

		/**
		 @fn	void ini::setpath(const std::string &path)
		 @brief	����path_��ֵ.���path��ֵ��Ч���ȡini��boot�ڵ�.
		 @author	Debug Go
		 @date	8/1/2014
		 @param	path	ini�ļ�·��.
		 @see getiniroot()
		 */
		void setpath(const std::string &path){ path_ = path; getiniroot(); }

		/**
		 @fn	std::string ini::getpath()
		 @brief	��ȡini�ļ�·��.
		 @author	Debug Go
		 @date	8/1/2014
		 @return	A std::string.
		 */
		std::string getpath(){ return path_; }

		template <class T>
		/**
		 @fn	bool ini::get(const std::string section, const std::string &key, T &value);
		 @brief	��ȡָ����(section)��ָ����(key)��ֵ.
		 @author	Debug Go
		 @date	8/1/2014
		 @param	section			 	��.
		 @param	key				 	��.
		 @param [in,out]	value	ֵ.
		 @return	true if it succeeds, false if it fails.
		 @attention ���ini�Ľڵ�Ϊ��,�����»�ȡ,�����ȡʧ���򷵻�false.
		 */
		bool get(const std::string &section, const std::string &key, T &value);
	private:
		/**
		 @brief	ini�ļ�·��.
		 */
		std::string path_;

		/**
		 @brief	ini�ļ��ĸ��ڵ�.
		 */
		boost::property_tree::ptree ini_boot_;

		/**
		 @fn	void ini::getiniroot();
		 @brief	��ȡini�ļ��ĸ��ڵ�.
		 @return ���ؽṹ,�ɹ�Ϊtrue,���򷵻�false;
		 @author	Debug Go
		 @date	8/1/2014
		 @attention ����ȷ��path_�Ѿ�����ȷ��ֵ.
		 */
		bool getiniroot();
	};

	

}

#endif // !COMMON_INI_H