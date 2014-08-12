#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Terrain.h"
#include "Box2D.h"
#include "Hero.h"
using namespace cocos2d;

#define PTM_RATIO 32.0

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
    
    
    ccColor4F randomBrightColor();
    void genBackground();
    void onEnter();
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
    CCSprite * spriteWithColor(ccColor4F c1, ccColor4F c2, float textureWidth, float textureHeight, int nStripes);
    void update(float dt);
    
    void setupWorld();
    void createBodyAtPostition(CCPoint position);
private:
    CCSprite *_background;
    Terrain *_terrain;
    b2World *_world;
    Hero *_hero;
    bool _tapDown;
};

#endif // __HELLOWORLD_SCENE_H__
