#include "HelloWorldScene.h"
#include "ContactListener.h"
#include "BackgroundLayer.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    BackgroundLayer *bkLayer = BackgroundLayer::create();
    scene->addChild(bkLayer, -1);
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

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
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->setAccelerometerEnabled(true);
    _tapDown = false;
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

#pragma For Tiny

ccColor4F HelloWorld::randomBrightColor()
{
    while (true)
    {
        float requiredBrightness = 192;
        ccColor4B randomColor = ccc4(rand() % 255,
                                     rand() % 255,
                                     rand() % 255,
                                     255);
        if (randomColor.r > requiredBrightness ||
            randomColor.g > requiredBrightness ||
            randomColor.b > requiredBrightness)
        {
            return ccc4FFromccc4B(randomColor);
        }
    }
}

void HelloWorld::genBackground()
{
    /*
    if (_background)
    {
        _background->removeFromParentAndCleanup(true);
    }
    
    ccColor4F bgColor = this->randomBrightColor();
    ccColor4F color2 = this->randomBrightColor();
    //_background = this->spriteWithColor(bgColor, 512, 512);
    int nStripes = ((rand() % 4) + 1) * 2;
    _background = this->spriteWithColor(bgColor, color2, 512, 512, nStripes);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    ccTexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
    _background->getTexture()->setTexParameters(&tp);
    this->addChild(_background);
     */
    
    ccColor4F color3 = this->randomBrightColor();
    ccColor4F color4 = this->randomBrightColor();
    CCSprite *stripes = this->spriteWithColor(color3, color3, 512, 512, 1);
    ccTexParams tp2 = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_CLAMP_TO_EDGE};
    stripes->getTexture()->setTexParameters(&tp2);
    _terrain->setStripes(stripes);
}

void HelloWorld::onEnter()
{
    CCLayer::onEnter();
    this->setScale(1);
    this->setupWorld();
    _terrain = Terrain::createWithWorld(_world);
    this->addChild(_terrain);
    
    _hero = Hero::createWithWorld(_world);
    _terrain->getBatchNode()->addChild(_hero);
    
    this->scheduleUpdate();
    this->genBackground();
    this->setTouchEnabled(true);
}

void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    _tapDown = true;
    
    /*
    CCTouch *anyTouch = static_cast<CCTouch*>(pTouches->anyObject());
    CCPoint touchLocation = _terrain->convertTouchToNodeSpace(anyTouch);
    this->createBodyAtPostition(touchLocation);
     */
}

void HelloWorld::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    _tapDown = false;
}


CCSprite * HelloWorld::spriteWithColor(ccColor4F c1, ccColor4F c2, float textureWidth, float textureHeight, int nStripes)
{
    // 1: Create new CCRenderTexture
    CCRenderTexture *rt = CCRenderTexture::create(textureWidth, textureHeight);
    
    // 2: Call CCRenderTexture:begin
    rt->beginWithClear(c1.r, c1.g, c1.b, c1.a);
    
    // 3: Draw into the texture
    this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
    CC_NODE_DRAW_SETUP();
    
    // Layer 1: Stripes
    CCPoint *vertices = new CCPoint[nStripes * 6];
    ccColor4F *colors = new ccColor4F[nStripes * 6];
    
    int nVertices = 0;
    float x1 = -textureHeight;
    float x2;
    float y1 = textureHeight;
    float y2 = 0;
    float dx = textureWidth / nStripes * 2;
    float stripeWidth = dx / 2;
    for (int i = 0; i < nStripes; ++i)
    {
        x2  = x1 + textureHeight;
        
        vertices[nVertices] = ccp(x1, y1);
        colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);
        
        vertices[nVertices] = ccp(x1 + stripeWidth, y1);
        colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);
        
        vertices[nVertices] = ccp(x2, y2);
        colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);
        
        vertices[nVertices] = vertices[nVertices - 2];
        colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);
        
        vertices[nVertices] = vertices[nVertices - 2];
        colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);
        
        vertices[nVertices] = ccp(x2 + stripeWidth, y2);
        colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);
        x1 += dx;
    }
    
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_TRUE, 0, colors);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)nVertices);
    
    CC_SAFE_DELETE_ARRAY(vertices);
    CC_SAFE_DELETE_ARRAY(colors);
    
    // Layer 4: Noise
    CCSprite *noise = CCSprite::create("Noise.png");
    ccBlendFunc blendFunc = {GL_DST_COLOR, CC_BLEND_DST};
    noise->setBlendFunc(blendFunc);
    noise->setPosition(ccp(textureWidth / 2, textureHeight / 2));
    noise->visit();
    
    // 4: Call CCRenderTexture:end
    rt->end();
    
    // 5: Create a new Sprite from the texture
    return CCSprite::createWithTexture(rt->getSprite()->getTexture());
}


void HelloWorld::update(float dt)
{
    
    if (_tapDown)
    {
        /*
        if (!_hero->getAwake())
        {
            _hero->wake();
            _tapDown = false;
        }
        else
        {
            _hero->dive();
        }
         */
        _hero->wake();
        _tapDown = false;
    }
    _hero->limitVelocity();
    
    static double UPDATE_INTERVAL = 1.0f / 60.0f;
    static double MAX_CYCLES_PER_FRAME = 5;
    static double timeAccumulator = 0;
    
    timeAccumulator += dt;
    if (timeAccumulator > (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL))
    {
        timeAccumulator = UPDATE_INTERVAL;
    }
    
    int32 velocityIterations = 3;
    int32 positionIterations = 2;
    while (timeAccumulator >= UPDATE_INTERVAL)
    {
        timeAccumulator -= UPDATE_INTERVAL;
        _world->Step(UPDATE_INTERVAL, velocityIterations, positionIterations);
        _world->ClearForces();
    }
    
    _hero->update(dt);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float scale = (winSize.height * 3 / 4) / _hero->getPosition().y;
    if (scale > 1)
    {
        scale = 1;
    }
    if (scale < 0.8) {
        scale = 0.8;
    }
    
    _terrain->setScale(scale);
    float offset = _hero->getPosition().x;
    _terrain->setOffsetX(offset);
}


void HelloWorld::setupWorld()
{
    b2Vec2 gravity = b2Vec2(0.0f, -7.f);
    bool doSleep = true;
    _world = new b2World(gravity);
    _world->SetAllowSleeping(doSleep);
    
    ContactListener *listener = new ContactListener();
    _world->SetContactListener(listener);
}

void HelloWorld::createBodyAtPostition(CCPoint position)
{
    b2BodyDef testBodyDef;
    testBodyDef.type = b2_dynamicBody;
    testBodyDef.position.Set(position.x / PTM_RATIO, position.y / PTM_RATIO);
    b2Body *testBody = _world->CreateBody(&testBodyDef);
    
    b2PolygonShape testBodyShape;
    testBodyShape.SetAsBox(25.f/PTM_RATIO, 25.f/PTM_RATIO);
    b2FixtureDef testFixtureDef;
//    testBodyShape.m_radius = 25.0 / PTM_RATIO;
    testFixtureDef.shape = &testBodyShape;
    testFixtureDef.density = 1.0;
    testFixtureDef.friction = 2.0;
    testFixtureDef.restitution = 0.5;
    testBody->CreateFixture(&testFixtureDef);
}


void HelloWorld::didAccelerate(CCAcceleration* pAccelerationValue)
{
    _hero->applyTorque(pAccelerationValue);
}