//
//  ContactListener.h
//  TinySlider
//
//  Created by HalloWorld on 14-8-12.
//
//

#ifndef __TinySlider__ContactListener__
#define __TinySlider__ContactListener__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Hero.h"

class ContactListener : public b2ContactListener {
private:
    //碰撞开始
    void BeginContact(b2Contact* contact);
    //碰撞结束
    void EndContact(b2Contact* contact);
    
    Hero *_hero;
    
public:
    void setHero(Hero *h);
};

#endif /* defined(__TinySlider__ContactListener__) */
