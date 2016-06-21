#include "EncryptLayer.h"
#include "xxtea/xxtea.h"
#include <io.h>

using namespace std;

#define KEY "arsenal"

EncryptLayer::EncryptLayer()
{
	m_vecResNames.clear();
	m_bLoading = false;
	m_bEncrypting = false;
	m_doneCount = 0;
}
EncryptLayer::~EncryptLayer()
{
	m_vecResNames.clear();
}


bool EncryptLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(228, 219, 213, 255)))
	{
		return false;
	}

	auto screenSize = Director::getInstance()->getWinSize();
	
	auto tips = Label::createWithTTF("Please copy the resources you want to encrypt into Resources/Encrypt of this project\nadd before this you should clear this folder", 
		"fonts/arial.ttf", 
		18,
		Size(screenSize.width, screenSize.height),
		TextHAlignment::CENTER,
		TextVAlignment::TOP);
	tips->setColor(Color3B(0, 0, 0));
	tips->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
	addChild(tips);

	
	Menu* pMenu = Menu::create();
	pMenu->setPosition(Vec2(0,0));
	addChild(pMenu);

	auto pLoadFont = Label::createWithTTF("Load", "fonts/Marker Felt.ttf", 25);
	pLoadFont->setColor(Color3B(0, 0, 0));
	
	MenuItemLabel* pLoadItem = MenuItemLabel::create(pLoadFont, CC_CALLBACK_1(EncryptLayer::LoadBtnCallback, this));
	pLoadItem->setPosition(Vec2(100, 50));
	pMenu->addChild(pLoadItem);

	auto pEncryptFont = Label::createWithTTF("Encrypt", "fonts/Marker Felt.ttf", 25);
	pEncryptFont->setColor(Color3B(0, 0, 0));

	MenuItemLabel* pEncryptItem = MenuItemLabel::create(pEncryptFont, CC_CALLBACK_1(EncryptLayer::EncryptBtnCallback, this));
	pEncryptItem->setPosition(Vec2(380, 50));
	pMenu->addChild(pEncryptItem);


	m_pStatusLabel = Label::createWithTTF("Welcome", "fonts/Marker Felt.ttf", 25);
	m_pStatusLabel->setPosition(Vec2(screenSize.width/2, screenSize.height/2));
	m_pStatusLabel->setColor(Color3B(0, 0, 0));
	addChild(m_pStatusLabel);

	return true;
}

Scene* EncryptLayer::createScene()
{
	Scene* s = Scene::create();
	EncryptLayer* el = EncryptLayer::create();
	s->addChild(el);
	return s;
}

void EncryptLayer::LoadBtnCallback(Ref* obj)
{
	log("EncryptLayer::LoadBtnCallback");

	if (m_bLoading)
	{
		return;
	}
	m_bLoading = true;

	m_vecResNames.clear();

	std::string fullPath = FileUtils::getInstance()->fullPathForFilename("HelloWorld.png");
	log("full path = %s", fullPath.c_str());
	int npos = fullPath.rfind("EncryptResources");
	log("npos = %d", npos);
	fullPath = fullPath.substr(0, npos + strlen("EncryptResources"));
	
	m_projectPath = fullPath;
	m_desPath = m_projectPath + "\\Resources\\Done";

	fullPath += "\\Resources\\Encrypt";

	if (TraverseDirectory(fullPath))
	{
		m_bLoading = false;
		m_pStatusLabel->setString("Load End");

		for (int i = 0; i < m_vecResNames.size(); i++)
		{
			log("name = %s", m_vecResNames[i].c_str());
		}
	}
	
}

void EncryptLayer::EncryptBtnCallback(Ref* obj)
{
	log("EncryptLayer::EncryptBtnCallback");

	if ( m_bEncrypting || m_bLoading || m_vecResNames.empty())
	{
		return;
	}
	m_doneCount = 0;
	m_bEncrypting = true;

	for (int i = 0; i < m_vecResNames.size(); i++ )
	{
		if (EncryptOneResource(m_vecResNames[i]))
		{
			m_doneCount++;
			int rate = m_doneCount * 100 / m_vecResNames.size();
			char s[8];
			snprintf(s, sizeof(s), "%d", rate);
			m_pStatusLabel->setString(s);
		}	
	}
	m_bEncrypting = false;
	m_pStatusLabel->setString("Done Encrypt");
}



bool EncryptLayer::TraverseDirectory(std::string path)
{
	_finddata_t FileInfo;
	string strFind = path + "\\*";
	long Handle = _findfirst(strFind.c_str(), &FileInfo);

	if (Handle == -1L)
	{
		m_pStatusLabel->setString("Error");
		return false;
	}

	m_pStatusLabel->setString("Loading...");

	do
	{
		//判断是否有子目录
		if (FileInfo.attrib & _A_SUBDIR)
		{
			//下面的判断条件很重要，过滤 . 和 ..
			if ((strcmp(FileInfo.name, ".") != 0) && (strcmp(FileInfo.name, "..") != 0))
			{
				string newPath = path + "\\" + FileInfo.name;
				TraverseDirectory(newPath);
			}
		}
		else
		{
			string newPath = path + "\\" + FileInfo.name;
			m_vecResNames.push_back(newPath);
		}
	} while (_findnext(Handle, &FileInfo) == 0);

	_findclose(Handle);
	return true;
}

bool EncryptLayer::EncryptOneResource(std::string path)
{
	if (path.empty())
		return false;
	
	ssize_t len = 0;
	//这里我用这个过期的方法才能成功，用getDataFromFile不行，不知道为啥
	unsigned char * fileData = FileUtils::getInstance()->getFileData(path, "rb", &len);

	//Data data = FileUtils::getInstance()->getDataFromFile( fullpath );
	// 	if (data.isNull())
	// 		return;

	unsigned char key[20] = KEY;
	xxtea_long ret_len = 0;
	unsigned char* newBuf = xxtea_encrypt(fileData, (xxtea_long)len, key, (xxtea_long)strlen(KEY), &ret_len);

	int npos = path.find("Encrypt\\");
	std::string savepath = m_desPath + path.substr(npos + 7, path.length());
	log("save path = %s", savepath.c_str());
	

// 	FILE *fp = fopen(savepath.c_str(), "wb+");
// 	fwrite(newBuf, ret_len, 1, fp);
// 	fflush(fp);
// 	fclose(fp);
// 	CC_SAFE_DELETE(newBuf);

	Data d;
	d.fastSet(newBuf, ret_len);
	FileUtils::getInstance()->writeDataToFile(d, savepath);
	return true;
}
