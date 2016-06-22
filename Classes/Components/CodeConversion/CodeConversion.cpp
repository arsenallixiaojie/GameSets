#include "CodeConversion.h"

int CodeConversion::code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	iconv_t cd;
	cd = iconv_open(to_charset,from_charset);
	if(cd==0) return -1;

	const char *temp = inbuf;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	char ** pin = const_cast<char**>(&temp);
#else
	const char **pin = &temp;
#endif
	char **pout = &outbuf;
	memset(outbuf,0,outlen);
	if(iconv(cd,pin,&inlen,pout,&outlen)==-1)
	{
		iconv_close(cd);
		return -1;
	}
	iconv_close(cd);
	return 0;
}

/*UTF8转为GBK*/
std::string CodeConversion::utfToGb(const char *inbuf)
{
	size_t inlen = strlen(inbuf);
	char * outbuf = new char[inlen * 2 + 2];
	std::string strRet;
	if(code_convert("utf-8", "gbk//IGNORE", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
	{
		strRet = outbuf;
	}
	delete [] outbuf;
	return strRet;
}

/*GBK转为UTF8*/
std::string CodeConversion::gbToUtf(const char *inbuf)
{
	size_t inlen = strlen(inbuf);
	char * outbuf = new char[inlen * 2 + 2];
	std::string strRet;
	if(code_convert("gbk", "utf-8//IGNORE", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
	{
		strRet = outbuf;
	}
	delete [] outbuf;
	return strRet;
}

char CodeConversion::getFirstChar(const char* inbuf){
	wchar_t wchr = 0;
	char szchinese[3] = {0};
	char res;

	if (inbuf[0]>=0 && inbuf[0] <= 127)
		res = inbuf[0];
	else
	{
		szchinese[0] = inbuf[0];
		szchinese[1] = inbuf[1];

		wchr = 0;
		wchr = (szchinese[0] & 0xff) << 8;
		wchr |= (szchinese[1] & 0xff);

		res = convert(wchr);
	}

	return res;
}

		

char CodeConversion::convert(wchar_t wchr){
	if (In(0xb0a1, 0xb0c4, wchr))
		return 'a';
	if (In(0xb0c5, 0xb2c0, wchr))
		return 'b';
	if (In(0xb2c1, 0xb4ed, wchr))
		return 'c';
	if (In(0xb4ee, 0xb6e9, wchr))
		return 'd';
	if (In(0xb6ea, 0xb7a1, wchr))
		return 'e';
	if (In(0xb7a2, 0xb8c0, wchr))
		return 'f';
	if (In(0xb8c1, 0xb9fd, wchr))
		return 'g';
	if (In(0xb9fe, 0xbbf6, wchr))
		return 'h';
	if (In(0xbbf7, 0xbfa5, wchr))
		return 'j';
	if (In(0xbfa6, 0xc0ab, wchr))
		return 'k';
	if (In(0xc0ac, 0xc2e7, wchr))
		return 'l';
	if (In(0xc2e8, 0xc4c2, wchr))
		return 'm';
	if (In(0xc4c3, 0xc5b5, wchr))
		return 'n';
	if (In(0xc5b6, 0xc5bd, wchr))
		return 'o';
	if (In(0xc5be, 0xc6d9, wchr))
		return 'p';
	if (In(0xc6da, 0xc8ba, wchr))
		return 'q';
	if (In(0xc8bb, 0xc8f5, wchr))
		return 'r';
	if (In(0xc8f6, 0xcbf0, wchr))
		return 's';
	if (In(0xcbfa, 0xcdd9, wchr))
		return 't';
	if (In(0xcdda, 0xcef3, wchr))
		return 'w';
	if (In(0xcef4, 0xd118, wchr))
		return 'x';
	if (In(0xd1b9, 0xd4d0, wchr))
		return 'y';
	if (In(0xd4d1, 0xd7f9, wchr))
		return 'z';
	return '#';
}

bool CodeConversion::In(wchar_t start, wchar_t end, wchar_t code){
	if (code >= start && code <= end)
		return true;
	return false;
}