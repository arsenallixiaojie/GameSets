#ifndef TOOL_HEAD_FILE
#define TOOL_HEAD_FILE

#include <string>
#include <vector>
#include "CCStdC.h"
#include "cocos2d.h"
USING_NS_CC;

#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32)
#define PLATFORM_WIN32
#endif

//getWritePath�����ǻ�ȡ��д��·����������Ҫ�ڱ��ش����ļ�д�����ݵ�ʱ����Ҫ��ȡ·��
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define getWritePath(path) path = "/sdcard" + FileUtils::getInstance()->getWritablePath();\
							SharedTools::ensureDirectoryExists(path.c_str()); \
							if (!FileUtils::getInstance()->isFileExist(path))\
								path = FileUtils::getInstance()->getWritablePath();

#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define getWritePath(path) path = path = FileUtils::getInstance()->getWritablePath();

#else
#define getWritePath(path) path = "SDCard/";\
	SharedTools::ensureDirectoryExists(path.c_str());

#endif

namespace SharedTools
{
#ifdef PLATFORM_WIN32

	//��const char ����ת��Ϊ wchar_t ����
	wchar_t* ansiToWideChar(const char* str);

#endif

	//ɾ���ļ�
	void deleteFile(const char *part_file_name);

	//����·��
	void ensureDirectoryExists(const char* pszDir);

	void sleepMilliSeconds(unsigned int dwMilliSeconds);

	//��ȡ�ļ���׺
	std::string getFileSuffix(std::string fileName);

	void findFileByPartNameAndDelete(const char * dirp, const char* partName);

	//ʾ��:findFilesByPartName("D:/DZPhone/client/cocos2d-x-2.1.3/PokerClient/Classes","GameLogin");
	//	   findFilesByPartName("/root/cocos2dx/cocos2d-x-2.2/DZPoker/Classes","GameLogin");
	std::vector<std::string> findFilesByPartName(const char * dirp, const char* partName);
}

#endif 
