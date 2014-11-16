#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
protected:
    Size visibleSize;
    Vec2 origin;
    TMXTiledMap *tileMap;
    TMXLayer *domainLayer;
    TMXLayer *wallLayer;
    Layer *tileMapLayer;
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
};

#endif // __HELLOWORLD_SCENE_H__
