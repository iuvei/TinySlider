//
//  Hero.h
//  TinySlider
//
//  Created by HalloWorld on 14-8-12.
//
//

#ifndef __TinySlider__Hero__
#define __TinySlider__Hero__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#define NUM_PREV_VELS 5

class Hero : public cocos2d::CCSprite
{
public:
    Hero(void);
    ~Hero(void);
    
    static Hero *createWithWorld(b2World *world);
    bool initWithWorld(b2World *world);
    
    void update(float dt);
    void createBody();
    
    CC_SYNTHESIZE_READONLY(bool, _awake, Awake);
    
    void wake();
    void dive();
    void limitVelocity();
    void applyTorque(cocos2d::CCAcceleration *pAccelerationValue);
    
private:
    b2World *_world;
    b2Body *_body;
    
    b2Vec2 _prevVels[NUM_PREV_VELS];
    int _nextVel;
};

#endif /* defined(__TinySlider__Hero__) */
