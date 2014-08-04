/**
* @file Textlog.h
* @brief 日志类
* 
* 文件中包含了g_logger全局对象g_logger
* 会LOG_DIR下生成以"程序名_YYYYMMDD.log"日志文件.
* @see LOG_DIR
* @author DebugGo
* @version 1.0.0.0
* @date 2014-7-31
*/
#ifndef TEXTLOG_H
#define TEXTLOG_H

#include <stdio.h>
#include <windows.h>
#include <tchar.h>
/**
* 常用类库命名空间
*/
namespace common
{

	/**
	* @brief 日志信息的等级
	*/
	enum ENUM_LOG_LINE_LEVEL
	{
		/**
		 @brief	调试级别, 仅在调试时输出.
		 */
		LOG_LEVEL_DEBUG = 1,       

		/**
		 @brief	一般信息输出.
		 */
		LOG_LEVEL_INFO = 2,

		/**
		 @brief	警告.
		 */
		LOG_LEVEL_WARN = 3,

		/**
		 @brief	一般错误.
		 */
		LOG_LEVEL_ERROR = 4,

		/**
		 @brief	严重错误,  这个级别的错误表示程序一般无法正常进行.
		 */
		LOG_LEVEL_FATAL = 5,
	};

	//#define FAST_RELEASE

#ifdef FAST_RELEASE 
#define WRITE_LOG(...) 
#define WRITE_LOGLINE(...) 
#else

	/**
	* 窄字符前加上"L".
	* @see __WFUNCTION__
	*/
#define WIDEN2(x) L ## x
	/**
	* 输出unicode编码
	* @see WINDEN2
	*/
#define WIDEN(x) WIDEN2(x)
	/**
	* 输出当前源文件名
	* @see WINDEN
	*/
#define __WFILE__ WIDEN(__FILE__)
#ifdef _UNICODE
	/**
	* 输出unicode编码的源文件名
	*/
#define __TFILE__ __WFILE__
#else
	/**
	* 输出ansi编码的源文件名
	*/
#define __TFILE__ __FILE__
#endif
	//如果编辑器版本小于1200,无法获取方法名
#if (_MSC_VER && _MSC_VER<=1200) || (__BORLANDC__) 
#define __FUNCTION__ NULL
#define __WFUNCTION__ NULL
#else //_MSC_VER>1200 __GNUC__ __INTEL_COMPILER
	/**
	* 获得unicode编码的方法名
	*/
#define __WFUNCTION__ WIDEN(__FUNCTION__)
#endif

#ifdef _UNICODE
#ifdef __GNUC__
#define __TFUNCTION__ NULL
#else
	/**
	* 输出unicode编码的方法名
	*/
#define __TFUNCTION__ __WFUNCTION__
#endif
#else
	/**
	* 输出ansi编码的方法名
	*/
#define __TFUNCTION__ __FUNCTION__
#endif

/**
* @brief 写入一行日志,并自动追加换行符.
*/
#define WRITE_LOG(level,format,...) g_logger.AddTLog(true,level, __TFILE__, __TFUNCTION__, __LINE__, format,__VA_ARGS__)
/**
* @brief 写入一行日志,但不追加换行符.
*/
#define WRITE_LOGLINE(level,format,...) g_logger.AddTLog(false,level, __TFILE__, __TFUNCTION__, __LINE__, format,__VA_ARGS__)
#endif

/**
*每条日志最大长度.
*/
#define LINE_BUFFER_SIZE (1024)
	/**
	* 操作日志类.
	*/
	class CTextLog
	{
	public:
		/**
		* @enum ENUM_LOG_MODE
		* @brief 日志输出模式
		* @note 用作构造函数参数.
		*/
		enum ENUM_LOG_MODE
		{
			/**
			 @brief	直接输出日志.
			 */
			LOG_MODE_DIRECT = 0,

			/**
			 @brief	延迟输出日志.
			 */
			LOG_MODE_DELAY  = 1
		};

		/**
		 * @enum	ENUM_LOG_LEVEL
		 * @brief	日志输出级别
		 * @note	用作构造函数参数
		*/
		enum ENUM_LOG_LEVEL
		{
			/**
			 @brief	关闭日志.
			 */
			LOG_WRITE_NONE = 0,

			/**
			 @brief	输出警告级别以上的日志 (日志量极小).
			 */
			LOG_WRITE_ERROR = 1,

			/**
			 @brief	输出信息级别以上的日志 (不包括调试日志,一般是这个级别).
			 */
			LOG_WRITE_INFO = 2,

			/**
			 @brief	输出调试级别以上的日志 (所有日志,包括调试日志).
			 */
			LOG_WRITE_ALL = 3,
		};

	public: //构造析构

		/**
		 * @fn	CTextLog::CTextLog(ENUM_LOG_LEVEL level = LOG_WRITE_ALL, ENUM_LOG_MODE writemode = LOG_MODE_DIRECT, LPCTSTR lpLogName = NULL);
		 * CTextLog的默认构造函数,理论上来说无需手动调用.将在方法内创建当日的日志文件.
		 * @brief	默认构造函数.
		 * @note	无需调用,会在初始化的时候由全局变量g_logger来创建.
		 * @date	7/31/2014
		 * @param	level	 	日志等级.
		 * @param	writemode	写入模式.
		 * @param	lpLogName	日志文件名称,将在构造函数内部自动创建.
		 * @see ENUM_LOG_MODE ENUM_LOG_LEVEL LOG_DIR
		*/
		CTextLog(ENUM_LOG_LEVEL level = LOG_WRITE_ALL, ENUM_LOG_MODE writemode = LOG_MODE_DIRECT, LPCTSTR lpLogName = NULL);

		/**
		 @fn	virtual CTextLog::~CTextLog();
		
		 @brief	析构函数,会在内部调用close().
		 @author	Debug Go
		 @date	8/1/2014
		 @see Close()
		 */
		virtual ~CTextLog();

	public: //外部调用接口

		/**
		 * @fn	void CTextLog::SetMode(ENUM_LOG_LEVEL level, ENUM_LOG_MODE writemode)
		 *
		 * @brief 设置日志记录模式,
		 *
		 * @author	Debug Go
		 * @date	7/31/2014
		 *
		 * @param	level	 	输出等级.
		 * @param	writemode	写入模式.
		*/
		void SetMode(ENUM_LOG_LEVEL level, ENUM_LOG_MODE writemode)
		{
			m_level = level;
			m_mode = writemode;
		}


		/**
		 @brief	增加一条日志.
		 增加一条unicode编码的日志,在调用WRITE_LOG及WRITE_LOGLINE时会调用该方法.
		 @param	bAddLine	true 在末尾加入换行符.
		 @param	level   	日志信息等级.
		 @param	szSrc   	输出日志的源文件名.
		 @param	szFunc  	输出日志的方法名.
		 @param	uLine   	输出日志所在的行号.
		 @param	format  	日志的内容.
		 @see WRITE_LOG WRITE_LOGLINE
		 @see ENUM_LOG_LINE_LEVEL __WFILE__  __TFUNCTION__ __LINE__
		 */
		void AddTLog(bool bAddLine, ENUM_LOG_LINE_LEVEL level, LPCTSTR szSrc, LPCTSTR szFunc, ULONG uLine, const WCHAR* format, ...);

		/**
		* 增加一条ansi编码的日志,在调用WRITE_LOG及WRITE_LOGLINE时会调用该方法.
		* @see AddTLog(bool bAddLine, ENUM_LOG_LINE_LEVEL level, LPCTSTR szSrc, LPCTSTR szFunc, ULONG uLine, const WCHAR* format, ...);
		*/
		void AddTLog(bool bAddLine, ENUM_LOG_LINE_LEVEL level, LPCTSTR szSrc, LPCTSTR szFunc, ULONG uLine, const CHAR* format, ...);

	private:  //私有函数

		/**
		 @fn	void CTextLog::Close();
		
		 @brief	关闭文件句柄
		
		 @author	Debug Go
		 @date	8/1/2014
		 @see m_file
		 */
		void Close();

		/**
		 @fn	void CTextLog::CreateNewLogFile();
		 按日期创建新的日志文件按"processname+yyyymmdd.log"格式创建.
		 @brief	创建一个新的日志文件.
		 @author	Debug Go
		 @date	8/1/2014
		 @exception 如果创建失败会抛出异常,有可能是文件无法正常创建导致的.
		 */
		void CreateNewLogFile();
	private:  //私有变量

		/**
		 @brief	日志文件完整路径.
		 */
		TCHAR m_strFileName[MAX_PATH];

		/**
		 @brief	日志文件存放路径.
		 */
		TCHAR m_szCurPath[MAX_PATH];

		/**
		 @brief	日志文件名.
		 */
		TCHAR m_szFileName[MAX_PATH];

		/**
		 @brief	日志文件句柄.
		 */
		HANDLE m_file;

		/**
		 @brief	日志创建时间.
		 */
		SYSTEMTIME m_createtime;

		/**
		 @brief	日志输出级别, 默认为3,  输出所有日志.
		 */
		ENUM_LOG_LEVEL m_level;

		/**
		 @brief	日志输出模式: 直接,延迟, 默认为直接,  延迟模式为每大于9*LINE_BUFFER_SIZE输出一次.
		 */
		ENUM_LOG_MODE m_mode;

		/**
		 @brief	日志缓存.
		 */
		CHAR m_buffer[10 * LINE_BUFFER_SIZE];

		/**
		 @brief	全局互斥体用于同步.
		 */
		CRITICAL_SECTION m_cs;
	};

	/**
	 @brief	全局日志类.
	 */
	extern CTextLog g_logger;
}
#endif // !TEXTLOG_H
