#include "TiledMapScene.h"


Scene* TiledMapScene::createScene(){
	Scene* s = Scene::create();
	TiledMapScene* l = TiledMapScene::create();
	s->addChild(l);
	return s;
}


bool TiledMapScene::init(){
	if (!Layer::init())
		return false;

	TMXTiledMap* tMap = TMXTiledMap::create("tiledmap.tmx");
	addChild(tMap, 0);

	m_metaLayer = tMap->getLayer("meta");
	m_metaLayer->setVisible(false);

	TMXObjectGroup* objects = tMap->getObjectGroup("objects");
	CCASSERT(objects != nullptr, "object group not found");

	ValueMap vmap = objects->getObject("SpawnPoint");
	float x = vmap["x"].asFloat();
	float y = vmap["y"].asFloat();
	log("x = %f, y = %f", x, y);

	m_Player = Sprite::create("Player.png");
	m_Player->setPosition(Vec2(x, y));
	addChild(m_Player);

	for (int i = 0; i < objects->getObjects().size(); i++)
	{
		ValueMap vm = objects->getObjects().at(i).asValueMap();
		if (vm["Enemy"].asInt() == 1)
		{
			Sprite* e = Sprite::create("enemy1.png");
			e->setPosition(Vec2(vm["x"].asFloat(), vm["y"].asFloat()));
			addChild(e);

			MoveBy* mb = MoveBy::create(0.3f, (m_Player->getPosition() - e->getPosition()).getNormalized()*10);
			e->runAction(RepeatForever::create(mb));
		}
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [tMap, this](Touch* t, Event* e){
		Vec2 p = t->getLocation();
		
		//int py = p.y / tMap->getTileSize().height;
		//m_Player->setPosition(Vec2((px+0.5)*tMap->getTileSize().width, (py+0.5)*tMap->getTileSize().height));
		
		TMXLayer* layer = tMap->getLayer("background");
		if (layer)
		{
			int px = p.x / tMap->getTileSize().width;
			int py = tMap->getMapSize().height - p.y / tMap->getTileSize().height;
			Sprite* s = layer->getTileAt(Vec2(px, py));

			int gid = m_metaLayer->getTileGIDAt(Vec2(px, py));
			Value v = tMap->getPropertiesForGID(gid);
			if (!v.isNull())
			{
				ValueMap vm = v.asValueMap();
				if(vm["Collidable"].asBool())
					return false;
				if (vm["Collectable"].asBool())
				{
					TMXLayer* foreLayer = tMap->getLayer("foreground");



					foreLayer->removeTileAt(Vec2(px, py));
					foreLayer->setTileGID(gid, Vec2(0, 0));
					
					//foreLayer->removeChild(foreLayer->tileAt(Vec2(px, py)), true);
					m_metaLayer->removeTileAt(Vec2(px, py));

				}
			}
			Vec2 pp = s->getPosition();
			m_Player->setPosition(Vec2(pp.x + tMap->getTileSize().width/2, pp.y + tMap->getTileSize().height/2));
		}
		
		
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}