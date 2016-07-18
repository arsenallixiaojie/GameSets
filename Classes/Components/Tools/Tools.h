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

//getWritePath函数是获取可写入路径，当你需要在本地创建文件写入数据的时候需要获取路径
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

	//把const char 数组转化为 wchar_t 数组
	wchar_t* ansiToWideChar(const char* str);

#endif

	//删除文件
	void deleteFile(const char *part_file_name);

	//生成路径
	void ensureDirectoryExists(const char* pszDir);

	void sleepMilliSeconds(unsigned int dwMilliSeconds);

	//获取文件后缀
	std::string getFileSuffix(std::string fileName);

	void findFileByPartNameAndDelete(const char * dirp, const char* partName);

	//示例:findFilesByPartName("D:/DZPhone/client/cocos2d-x-2.1.3/PokerClient/Classes","GameLogin");
	//	   findFilesByPartName("/root/cocos2dx/cocos2d-x-2.2/DZPoker/Classes","GameLogin");
	std::vector<std::string> findFilesByPartName(const char * dirp, const char* partName);
}

#endif 
