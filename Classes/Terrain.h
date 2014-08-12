//
//  Terrain.h
//  TinySlider
//
//  Created by HalloWorld on 14-8-12.
//
//

#ifndef __TinySlider__Terrain__
#define __TinySlider__Terrain__

#include "cocos2d.h"
#include "Box2D.h"
#include "GLES-Render.h"

#define kMaxHillKeyPoints 1000
#define kHillSegmentWidth 5

#define kMaxHillVertices 4000
#define kMaxBorderVertices 800

class Terrain : public cocos2d::CCNode
{
public:
    Terrain(void);
    virtual ~Terrain(void);
    
    CREATE_FUNC(Terrain);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCSprite*, _stripes, Stripes);
    
    void generateHills();
    virtual bool init();
    virtual void draw();
    void setOffsetX(float newOffsetX);
    void resetHillVertices();
    
    static Terrain *createWithWorld(b2World *world);
    void resetBox2DBody();
    bool initWithWorld(b2World *world);
    void setupDebugDraw();
    
    CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _batchNode, BatchNode);
    
private:
    int _offsetX;
    cocos2d::CCPoint _hillKeyPoints[kMaxHillKeyPoints];
    
    int _fromKeyPointI;
    int _toKeyPointI;
    
    int _nHillVertices;
    cocos2d::CCPoint _hillVertices[kMaxHillVertices];
    cocos2d::CCPoint _hillTexCoords[kMaxHillVertices];
    int _nBorderVertices;
    cocos2d::CCPoint _borderVertices[kMaxBorderVertices];
    
    b2World *_world;
    b2Body *_body;
    GLESDebugDraw *_debugDraw;
};

#endif /* defined(__TinySlider__Terrain__) */
