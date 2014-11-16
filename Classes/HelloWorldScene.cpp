#include "HelloWorldScene.h"
#include <array>
#include <algorithm>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    tileMapLayer = Layer::create();
    tileMap = TMXTiledMap::create("map_02.tmx");
    domainLayer = tileMap->getLayer("Domain");
    wallLayer = tileMap->getLayer("Wall");
    
    Size domainSize = domainLayer->getLayerSize();
    int worldGrid[static_cast<int>(domainSize.width)][static_cast<int>(domainSize.height)];

//    typedef std::array<std::array<int,12>,12> WorldGrid;
//    WorldGrid worldGrid;
//    std::array<int, 12> worldGridX;
//    std::fill(std::begin(worldGridX), std::end(worldGridX), 0);
//    std::fill(std::begin(worldGrid), std::end(worldGrid), worldGridX);

    for (int x = 0; x < sizeof(worldGrid) / sizeof(worldGrid[0]); ++x) {
            for (int y = 0; y < sizeof(worldGrid[x]) / sizeof(worldGrid[x][0]); ++y) {
                worldGrid[x][y] = (0 != wallLayer->getTileGIDAt(Vec2(x,y)));
            }
    }
    for (int x = 0; x < sizeof(worldGrid) / sizeof(worldGrid[0]); ++x) {
        for (int y = 0; y < sizeof(worldGrid[x]) / sizeof(worldGrid[x][0]); ++y) {
            CCLOG("(x,y) = (%i,%i) => %i", x,y,worldGrid[x][y]);
        }
    }

    tileMapLayer->addChild(tileMap);
    tileMapLayer->setContentSize(domainLayer->getContentSize());
    
    auto lister = EventListenerTouchOneByOne::create();
    lister->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    lister->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    lister->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    lister->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    domainLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lister, domainLayer);
    
    this->addChild(tileMapLayer);
    
    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    Size tileSize = tileMap->getTileSize();
    Point domainLocation = domainLayer->convertToNodeSpace(touch->getLocation());
    Size domainSize = domainLayer->getContentSize();
    float slopeFormula = tileSize.height / tileSize.width;
    float tileX = floor((slopeFormula * domainLocation.x + domainSize.height * 0.5 - domainLocation.y) / tileSize.height);
    float tileY = floor((-slopeFormula * domainLocation.x + domainSize.height * 1.5 - domainLocation.y) / tileSize.height);
    Point departurePoint = domainLayer->getPositionAt(Vec2(tileX, tileY)) + tileSize * 0.5;
    
    SpriteBatchNode* spritebatch = SpriteBatchNode::create("CloseNormal.png");
    auto spriteArcher = Sprite::create("CloseNormal.png");
    spritebatch->addChild(spriteArcher);
    spritebatch->setPosition(departurePoint);
    tileMapLayer->addChild(spritebatch);
    
    Point destinationPoint = domainLayer->getPositionAt(Vec2(5,5)) + tileSize * 0.5;
    spritebatch->runAction(MoveTo::create(0.5f, destinationPoint));
    
    return true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    CCLOG("2. moved");
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    CCLOG("3. ended");
}

void HelloWorld::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    CCLOG("4. cancelled");
}