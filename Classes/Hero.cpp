//
//  Hero.cpp
//  TinySlider
//
//  Created by HalloWorld on 14-8-12.
//
//

#include "Hero.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

Hero::Hero(void)
{
    _world = NULL;
    _body = NULL;
    _awake = false;
    
    memset(_prevVels, 0, NUM_PREV_VELS * sizeof(b2Vec2));
    _nextVel = 0;
}

Hero::~Hero(void)
{
}

Hero * Hero::createWithWorld(b2World *world)
{
    Hero *pRet = new Hero();
    if (pRet && pRet->initWithWorld(world))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool Hero::initWithWorld(b2World *world)
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!CCSprite::initWithSpriteFrameName("seal1.png"));
        
        _world = world;
        this->createBody();
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void Hero::update(float dt)
{
    this->setPosition(ccp(_body->GetPosition().x * PTM_RATIO, _body->GetPosition().y * PTM_RATIO));
    b2Vec2 vel = _body->GetLinearVelocity();
    b2Vec2 weightedVel = vel;
    
    for (int i = 0; i < NUM_PREV_VELS; ++i)
    {
        weightedVel += _prevVels[i];
    }
    weightedVel = b2Vec2(weightedVel.x / NUM_PREV_VELS, weightedVel.y / NUM_PREV_VELS);
    _prevVels[_nextVel++] = vel;
    if (_nextVel >= NUM_PREV_VELS)
    {
        _nextVel = 0;
    }
    
    float angle = ccpToAngle(ccp(weightedVel.x, weightedVel.y));
    if (_awake)
    {
        this->setRotation(-1 * CC_RADIANS_TO_DEGREES(angle));
    }
}

void Hero::createBody()
{
    float radius = 16.0f;
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    int screenH = size.height;
    
    CCPoint startPosition = ccp(0, screenH / 2 + radius);
    
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.linearDamping = 0.1f;
    bd.fixedRotation = true;
    bd.position.Set(startPosition.x / PTM_RATIO, startPosition.y / PTM_RATIO);
    _body = _world->CreateBody(&bd);
    
    b2CircleShape shape;
    shape.m_radius = radius / PTM_RATIO;
    
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = 1.0f / CC_CONTENT_SCALE_FACTOR();
    fd.restitution = 0.0f;
    fd.friction = 0.2f;
    
    _body->CreateFixture(&fd);
    _body->SetUserData(this);
}


void Hero::wake()
{
    _body->ApplyLinearImpulse(b2Vec2(2, 0), _body->GetPosition());
}

void Hero::dive()
{
    _body->ApplyForce(b2Vec2(5, -50), _body->GetPosition());
}

void Hero::limitVelocity()
{
    if (!_awake)
    {
        return;
    }
    
    const float minVelocityX = 5;
    const float minVelocityY = -40;
    b2Vec2 vel = _body->GetLinearVelocity();
    if (vel.x < minVelocityX)
    {
        vel.x = minVelocityX;
    }
    if (vel.y < minVelocityY)
    {
        vel.y = minVelocityY;
    }
    _body->SetLinearVelocity(vel);
}