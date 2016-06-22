#ifndef _H_CODECONVERSION_H_
#define _H_CODECONVERSION_H_

#include "cocos2d.h"
#include "win32-specific/icon/include/iconv.h"
USING_NS_CC;

namespace CodeConversion
{
	int code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen);
	// UTF8转为GB2312
	std::string utfToGb(const char *inbuf);
	// GB2312转为UTF8
	std::string gbToUtf(const char *inbuf);

	//获取字符串的首字符
	char getFirstChar(const char* inbuf);
	char convert(wchar_t wchr);
	bool In(wchar_t start, wchar_t end, wchar_t code);
};

#endif 