//
//  BackgroundLayer.h
//  TinySlider
//
//  Created by HalloWorld on 14-8-15.
//
//

#ifndef __TinySlider__BackgroundLayer__
#define __TinySlider__BackgroundLayer__

#include "cocos2d.h"

class BackgroundLayer : public cocos2d::CCLayer {
    
    cocos2d::CCSprite *backgroundSprite;
    
public:
    virtual ~BackgroundLayer();
    virtual bool init();
    void onEnter();
    void startAnimate();
    
    CREATE_FUNC(BackgroundLayer);
};


#endif /* defined(__TinySlider__BackgroundLayer__) */
