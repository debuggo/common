/**
* @file Textlog.h
* @brief ��־��
* 
* �ļ��а�����g_loggerȫ�ֶ���g_logger
* ��LOG_DIR��������"������_YYYYMMDD.log"��־�ļ�.
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
* ������������ռ�
*/
namespace common
{

	/**
	* @brief ��־��Ϣ�ĵȼ�
	*/
	enum ENUM_LOG_LINE_LEVEL
	{
		/**
		 @brief	���Լ���, ���ڵ���ʱ���.
		 */
		LOG_LEVEL_DEBUG = 1,       

		/**
		 @brief	һ����Ϣ���.
		 */
		LOG_LEVEL_INFO = 2,

		/**
		 @brief	����.
		 */
		LOG_LEVEL_WARN = 3,

		/**
		 @brief	һ�����.
		 */
		LOG_LEVEL_ERROR = 4,

		/**
		 @brief	���ش���,  �������Ĵ����ʾ����һ���޷���������.
		 */
		LOG_LEVEL_FATAL = 5,
	};

	//#define FAST_RELEASE

#ifdef FAST_RELEASE 
#define WRITE_LOG(...) 
#define WRITE_LOGLINE(...) 
#else

	/**
	* խ�ַ�ǰ����"L".
	* @see __WFUNCTION__
	*/
#define WIDEN2(x) L ## x
	/**
	* ���unicode����
	* @see WINDEN2
	*/
#define WIDEN(x) WIDEN2(x)
	/**
	* �����ǰԴ�ļ���
	* @see WINDEN
	*/
#define __WFILE__ WIDEN(__FILE__)
#ifdef _UNICODE
	/**
	* ���unicode�����Դ�ļ���
	*/
#define __TFILE__ __WFILE__
#else
	/**
	* ���ansi�����Դ�ļ���
	*/
#define __TFILE__ __FILE__
#endif
	//����༭���汾С��1200,�޷���ȡ������
#if (_MSC_VER && _MSC_VER<=1200) || (__BORLANDC__) 
#define __FUNCTION__ NULL
#define __WFUNCTION__ NULL
#else //_MSC_VER>1200 __GNUC__ __INTEL_COMPILER
	/**
	* ���unicode����ķ�����
	*/
#define __WFUNCTION__ WIDEN(__FUNCTION__)
#endif

#ifdef _UNICODE
#ifdef __GNUC__
#define __TFUNCTION__ NULL
#else
	/**
	* ���unicode����ķ�����
	*/
#define __TFUNCTION__ __WFUNCTION__
#endif
#else
	/**
	* ���ansi����ķ�����
	*/
#define __TFUNCTION__ __FUNCTION__
#endif

/**
* @brief д��һ����־,���Զ�׷�ӻ��з�.
*/
#define WRITE_LOG(level,format,...) g_logger.AddTLog(true,level, __TFILE__, __TFUNCTION__, __LINE__, format,__VA_ARGS__)
/**
* @brief д��һ����־,����׷�ӻ��з�.
*/
#define WRITE_LOGLINE(level,format,...) g_logger.AddTLog(false,level, __TFILE__, __TFUNCTION__, __LINE__, format,__VA_ARGS__)
#endif

/**
*ÿ����־��󳤶�.
*/
#define LINE_BUFFER_SIZE (1024)
	/**
	* ������־��.
	*/
	class CTextLog
	{
	public:
		/**
		* @enum ENUM_LOG_MODE
		* @brief ��־���ģʽ
		* @note �������캯������.
		*/
		enum ENUM_LOG_MODE
		{
			/**
			 @brief	ֱ�������־.
			 */
			LOG_MODE_DIRECT = 0,

			/**
			 @brief	�ӳ������־.
			 */
			LOG_MODE_DELAY  = 1
		};

		/**
		 * @enum	ENUM_LOG_LEVEL
		 * @brief	��־�������
		 * @note	�������캯������
		*/
		enum ENUM_LOG_LEVEL
		{
			/**
			 @brief	�ر���־.
			 */
			LOG_WRITE_NONE = 0,

			/**
			 @brief	������漶�����ϵ���־ (��־����С).
			 */
			LOG_WRITE_ERROR = 1,

			/**
			 @brief	�����Ϣ�������ϵ���־ (������������־,һ�����������).
			 */
			LOG_WRITE_INFO = 2,

			/**
			 @brief	������Լ������ϵ���־ (������־,����������־).
			 */
			LOG_WRITE_ALL = 3,
		};

	public: //��������

		/**
		 * @fn	CTextLog::CTextLog(ENUM_LOG_LEVEL level = LOG_WRITE_ALL, ENUM_LOG_MODE writemode = LOG_MODE_DIRECT, LPCTSTR lpLogName = NULL);
		 * CTextLog��Ĭ�Ϲ��캯��,��������˵�����ֶ�����.���ڷ����ڴ������յ���־�ļ�.
		 * @brief	Ĭ�Ϲ��캯��.
		 * @note	�������,���ڳ�ʼ����ʱ����ȫ�ֱ���g_logger������.
		 * @date	7/31/2014
		 * @param	level	 	��־�ȼ�.
		 * @param	writemode	д��ģʽ.
		 * @param	lpLogName	��־�ļ�����,���ڹ��캯���ڲ��Զ�����.
		 * @see ENUM_LOG_MODE ENUM_LOG_LEVEL LOG_DIR
		*/
		CTextLog(ENUM_LOG_LEVEL level = LOG_WRITE_ALL, ENUM_LOG_MODE writemode = LOG_MODE_DIRECT, LPCTSTR lpLogName = NULL);

		/**
		 @fn	virtual CTextLog::~CTextLog();
		
		 @brief	��������,�����ڲ�����close().
		 @author	Debug Go
		 @date	8/1/2014
		 @see Close()
		 */
		virtual ~CTextLog();

	public: //�ⲿ���ýӿ�

		/**
		 * @fn	void CTextLog::SetMode(ENUM_LOG_LEVEL level, ENUM_LOG_MODE writemode)
		 *
		 * @brief ������־��¼ģʽ,
		 *
		 * @author	Debug Go
		 * @date	7/31/2014
		 *
		 * @param	level	 	����ȼ�.
		 * @param	writemode	д��ģʽ.
		*/
		void SetMode(ENUM_LOG_LEVEL level, ENUM_LOG_MODE writemode)
		{
			m_level = level;
			m_mode = writemode;
		}


		/**
		 @brief	����һ����־.
		 ����һ��unicode�������־,�ڵ���WRITE_LOG��WRITE_LOGLINEʱ����ø÷���.
		 @param	bAddLine	true ��ĩβ���뻻�з�.
		 @param	level   	��־��Ϣ�ȼ�.
		 @param	szSrc   	�����־��Դ�ļ���.
		 @param	szFunc  	�����־�ķ�����.
		 @param	uLine   	�����־���ڵ��к�.
		 @param	format  	��־������.
		 @see WRITE_LOG WRITE_LOGLINE
		 @see ENUM_LOG_LINE_LEVEL __WFILE__  __TFUNCTION__ __LINE__
		 */
		void AddTLog(bool bAddLine, ENUM_LOG_LINE_LEVEL level, LPCTSTR szSrc, LPCTSTR szFunc, ULONG uLine, const WCHAR* format, ...);

		/**
		* ����һ��ansi�������־,�ڵ���WRITE_LOG��WRITE_LOGLINEʱ����ø÷���.
		* @see AddTLog(bool bAddLine, ENUM_LOG_LINE_LEVEL level, LPCTSTR szSrc, LPCTSTR szFunc, ULONG uLine, const WCHAR* format, ...);
		*/
		void AddTLog(bool bAddLine, ENUM_LOG_LINE_LEVEL level, LPCTSTR szSrc, LPCTSTR szFunc, ULONG uLine, const CHAR* format, ...);

	private:  //˽�к���

		/**
		 @fn	void CTextLog::Close();
		
		 @brief	�ر��ļ����
		
		 @author	Debug Go
		 @date	8/1/2014
		 @see m_file
		 */
		void Close();

		/**
		 @fn	void CTextLog::CreateNewLogFile();
		 �����ڴ����µ���־�ļ���"processname+yyyymmdd.log"��ʽ����.
		 @brief	����һ���µ���־�ļ�.
		 @author	Debug Go
		 @date	8/1/2014
		 @exception �������ʧ�ܻ��׳��쳣,�п������ļ��޷������������µ�.
		 */
		void CreateNewLogFile();
	private:  //˽�б���

		/**
		 @brief	��־�ļ�����·��.
		 */
		TCHAR m_strFileName[MAX_PATH];

		/**
		 @brief	��־�ļ����·��.
		 */
		TCHAR m_szCurPath[MAX_PATH];

		/**
		 @brief	��־�ļ���.
		 */
		TCHAR m_szFileName[MAX_PATH];

		/**
		 @brief	��־�ļ����.
		 */
		HANDLE m_file;

		/**
		 @brief	��־����ʱ��.
		 */
		SYSTEMTIME m_createtime;

		/**
		 @brief	��־�������, Ĭ��Ϊ3,  ���������־.
		 */
		ENUM_LOG_LEVEL m_level;

		/**
		 @brief	��־���ģʽ: ֱ��,�ӳ�, Ĭ��Ϊֱ��,  �ӳ�ģʽΪÿ����9*LINE_BUFFER_SIZE���һ��.
		 */
		ENUM_LOG_MODE m_mode;

		/**
		 @brief	��־����.
		 */
		CHAR m_buffer[10 * LINE_BUFFER_SIZE];

		/**
		 @brief	ȫ�ֻ���������ͬ��.
		 */
		CRITICAL_SECTION m_cs;
	};

	/**
	 @brief	ȫ����־��.
	 */
	extern CTextLog g_logger;
}
#endif // !TEXTLOG_H
