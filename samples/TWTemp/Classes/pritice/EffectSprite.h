//
//  EffectSprite.h
//  TestSpine
//
//  Created by ly on 4/5/15.
//
//

#ifndef __TestSpine__EffectSprite__
#define __TestSpine__EffectSprite__
#include "Effect.h"
#include "cocos2d.h"
USING_NS_CC;
class Effect;
class EffectSprite : public Sprite {
    
public:
    EffectSprite();
    
    static EffectSprite * create(const std::string & filename);
    
    void setEffect(Effect * effect);
    
    Effect* _defaultEffect;
    
     std::vector<std::tuple<ssize_t,Effect*,QuadCommand>> _effects;
    
    void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
};

#endif /* defined(__TestSpine__EffectSprite__) */
