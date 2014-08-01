/**
 @file	Ini.h
 @brief Ini类的头文件.
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
	 @brief	ini类.
	 @author	Debug Go
	 @date	8/1/2014
	 */
	class ini
	{
	public:

		/**
		 @fn	ini::ini();
		 @brief	默认构造函数.
		 @author	Debug Go
		 @date	8/1/2014
		 */
		ini();

		/**
		 @fn	ini::ini(const std::string &path);
		 @brief	构造同时给对path_赋值.
		 @author	Debug Go
		 @date	8/1/2014
		 @param	path	ini文件的路径.
		 @see path_
		 @see setpath() getiniroot()
		 */
		ini(const std::string &path){ setpath(path); }

		/**
		 @fn	virtual ini::~ini();
		 @brief	默认的析构函数.
		 @author	Debug Go
		 @date	8/1/2014
		 */
		virtual ~ini();

		/**
		 @fn	void ini::setpath(const std::string &path)
		 @brief	设置path_的值.如果path的值有效会获取ini的boot节点.
		 @author	Debug Go
		 @date	8/1/2014
		 @param	path	ini文件路径.
		 @see getiniroot()
		 */
		void setpath(const std::string &path){ path_ = path; getiniroot(); }

		/**
		 @fn	std::string ini::getpath()
		 @brief	获取ini文件路径.
		 @author	Debug Go
		 @date	8/1/2014
		 @return	A std::string.
		 */
		std::string getpath(){ return path_; }

	private:
		/**
		 @brief	ini文件路径.
		 */
		std::string path_;

		/**
		 @brief	ini文件的跟节点.
		 */
		boost::property_tree::ptree ini_boot_;

		/**
		 @fn	void ini::getiniroot();
		 @brief	获取ini文件的跟节点.
		 @return 返回结构,成功为true,否则返回false;
		 @author	Debug Go
		 @date	8/1/2014
		 @attention 必须确保path_已经被正确赋值.
		 */
		bool getiniroot();
	};
}

#endif // !COMMON_INI_H