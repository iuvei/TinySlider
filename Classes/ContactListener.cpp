//
//  ContactListener.cpp
//  TinySlider
//
//  Created by HalloWorld on 14-8-12.
//
//

#include "ContactListener.h"

using namespace cocos2d;

//碰撞开始
void ContactListener::BeginContact(b2Contact* contact)
{
    CCSprite *sprite = (CCSprite *)contact->GetFixtureA()->GetBody()->GetUserData();
    CCSprite *sprite2 = (CCSprite *)contact->GetFixtureB()->GetBody()->GetUserData();
    if (sprite == _hero || sprite2 == _hero) {
    }
}


//碰撞结束
void ContactListener::EndContact(b2Contact* contact)
{
}


void ContactListener::setHero(Hero *h)
{
    _hero = h;
}

