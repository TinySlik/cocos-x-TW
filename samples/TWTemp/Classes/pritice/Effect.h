//
//  Effect.h
//  TestSpine
//
//  Created by ly on 4/5/15.
//
//

#ifndef __TestSpine__Effect__
#define __TestSpine__Effect__

#include "cocos2d.h"
#include "EffectSprite.h"
USING_NS_CC;
class EffectSprite;
class Effect : public Ref{
public:
    Effect();
    ~Effect();
    virtual void setTarget(EffectSprite *sprite){}
    bool initGLProgramState(const std::string &vertexFilename,const std::string &fragmentFilename);
    
//    EventListenerCustom* _backgroundListener;
    
    CC_SYNTHESIZE(GLProgramState*, _glprogramstate, GLProgramState);
};

// Blur
class EffectBlur : public Effect
{
public:
    CREATE_FUNC(EffectBlur);
    virtual void setTarget(EffectSprite *sprite) override;
    void setBlurRadius(float radius);
    void setBlurSampleNum(float num);
    
protected:
    bool init(float blurRadius = 10.0f, float sampleNum = 5.0f);
    
    float _blurRadius;
    float _blurSampleNum;
};



#endif /* defined(__TestSpine__Effect__) */
