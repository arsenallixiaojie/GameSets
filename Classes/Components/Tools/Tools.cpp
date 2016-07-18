#include "Tools.h"

#include <algorithm>
#ifdef PLATFORM_WIN32
#include <io.h>
#else
#include <dirent.h>
#endif

using namespace std;

namespace SharedTools
{
#ifdef PLATFORM_WIN32
	
	wchar_t* ansiToWideChar(const char* str)
	{
		static wchar_t unicodeString[1024];
		memset(unicodeString,0,(512)*sizeof(wchar_t));  
		int stringLength = ::MultiByteToWideChar(CP_ACP, NULL, str, strlen(str), LPWSTR(unicodeString), 512);
		return unicodeString;
	}
#endif

	void deleteFile(const char *part_file_name)
	{
#ifdef PLATFORM_WIN32
	#ifdef UNICODE
		DeleteFile(ansiToWideChar(part_file_name));
	#else
		DeleteFile(part_file_name);
	#endif // UNICODE
#else
	remove(part_file_name);
#endif
	}

	void ensureDirectoryExists(const char* pszDir)
	{
#ifdef PLATFORM_WIN32
		std::string dir = pszDir;
		if ( dir[0] == '/' )
		{
			dir = dir.substr(1);
		}

		std::string::size_type beginPos = dir.find_first_of('/', 0);
		while(beginPos != std::string::npos)
		{
			std::string subDir = dir.substr(0, beginPos);
			if(beginPos != std::string::npos)
			{
				beginPos++;
			}

			#ifdef UNICODE
				CreateDirectory(ansiToWideChar(subDir.c_str()), NULL);
			#else
				CreateDirectory(subDir.c_str(), NULL);
			#endif

			beginPos = dir.find_first_of('/', beginPos);
		}
#else
		std::string dir = pszDir;
		std::string::size_type beginPos = dir.find_first_of('/', 0);
		if ( beginPos == 1)
		{
			beginPos = dir.find_first_of('/', beginPos);
		}
		while(beginPos != std::string::npos)
		{
			std::string subDir = dir.substr(0, beginPos);
			if(beginPos != std::string::npos)
			{
				beginPos++;
			}
			mkdir( subDir.c_str(), S_IRWXU );
			beginPos = dir.find_first_of('/', beginPos);
		}
#endif
	}

	void sleepMilliSeconds(unsigned int dwMilliSeconds)
	{
#ifndef PLATFORM_WIN32
		usleep(dwMilliSeconds*1000);
#else
		Sleep(dwMilliSeconds);
#endif
	}

	std::string getFileSuffix(std::string fileName)
	{
		std::string::size_type pos;

		pos=fileName.rfind('.');

		std::string suffix;
		if (pos != std::string::npos)
		{
			suffix = fileName.substr(pos);
			transform(suffix.begin(),suffix.end(),suffix.begin(),towupper);
		}

		return suffix;
	}

	std::vector<std::string> findFilesByPartName(const char * dirp, const char* partName)
	{
		std::vector<std::string> res;
#ifdef PLATFORM_WIN32
		_finddata_t ffile;
		long lf;
		string strPath = dirp;
		strPath += "/*";
		strPath += partName;
		strPath += "*";
		if ((lf = _findfirst(strPath.c_str(),&ffile))!= -1l)
		{
			string name;
			name = ffile.name;
			if (name.find(partName) != string::npos)
			{	
				res.push_back(name);
			}
			while(_findnext(lf,&ffile) == 0)
			{
				name = ffile.name;
				if (name.find(partName) != string::npos)
				{
					res.push_back(name);
					break;
				}
			}
			_findclose(lf);
		}
#else
		struct dirent **namelist;
		string name;
		int n = scandir(dirp, &namelist,0,alphasort);
		if (n >= 0)
		{
			while (n--)
			{
				name = namelist[n]->d_name;
				if (name.find(partName) != string::npos)
					res.push_back(name);
				free(namelist[n]);
			}
			free(namelist);
		}
#endif
		return res;
	}

	void findFileByPartNameAndDelete(const char * dirp, const char* partName)
	{
#if(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
		std::vector<std::string> res;

		struct dirent **namelist;
		string name;
		string pushName; 
		int n = scandir(dirp, &namelist,0,alphasort);
		if (n >= 0)
		{
			while (n--)
			{
				name = namelist[n]->d_name;
				if (name.find(partName) != string::npos)
				{
					pushName = dirp;
					pushName += name;
					res.push_back(pushName);
				}
					
				free(namelist[n]);
			}
			free(namelist);
		}

		for (std::vector<std::string>::iterator iter = res.begin(); iter != res.end(); ++iter)
		{
			remove((*iter).c_str());
		}
#endif
	}


}