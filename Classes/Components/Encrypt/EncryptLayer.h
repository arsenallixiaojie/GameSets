#ifndef _ENCRYPTLAYER_H_
#define _ENCRYPTLAYER_H_

#include "cocos2d.h"
USING_NS_CC;

class EncryptLayer : public LayerColor
{
public:
	EncryptLayer();
	~EncryptLayer();

	static Scene* createScene();
	CREATE_FUNC(EncryptLayer);
private:
	bool init();

	void LoadBtnCallback(Ref* obj);
	void EncryptBtnCallback(Ref* obj);

	bool TraverseDirectory(std::string path);

	bool EncryptOneResource(std::string path);
private:
	std::vector<std::string> m_vecResNames;

	std::string m_desPath;	//Ä¿±êÂ·¾¶
	std::string m_projectPath;

	Label*	m_pStatusLabel;

	bool	m_bLoading;

	bool	m_bEncrypting;

	int		m_doneCount;
};

#endif