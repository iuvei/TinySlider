//
//  BackgroundLayer.cpp
//  TinySlider
//
//  Created by HalloWorld on 14-8-15.
//
//

#include "BackgroundLayer.h"

using namespace cocos2d;

BackgroundLayer::~BackgroundLayer()
{
    backgroundSprite->release();
}

bool BackgroundLayer::init()
{
    if (CCLayer::init()) {
        backgroundSprite = CCSprite::create("background.png");
        backgroundSprite->retain();
        CCSize ws = CCDirector::sharedDirector()->getWinSize();
        backgroundSprite->setPosition(ccp(ws.width /2, ws.height /2));
        addChild(backgroundSprite);
        return true;
    }
    return false;
}

void BackgroundLayer::onEnter()
{
    CCLayer::onEnter();
}