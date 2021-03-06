//
//  EffectSprite.cpp
//  TestSpine
//
//  Created by ly on 4/5/15.
//
//

#include "EffectSprite.h"

EffectSprite* EffectSprite::create(const std::string &filename){
    auto ret = new (std::nothrow) EffectSprite;
    if(ret && ret->initWithFile(filename)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_RELEASE(ret);
    return nullptr;
}

void EffectSprite::setEffect(Effect *effect){
    if (_defaultEffect != effect) {
        effect->setTarget(this);
        
        CC_SAFE_RELEASE(_defaultEffect);
        _defaultEffect = effect;
        CC_SAFE_RETAIN(_defaultEffect);
        
        setGLProgramState(_defaultEffect->getGLProgramState());
    }
}

EffectSprite::EffectSprite()
: _defaultEffect(nullptr)
{
    _effects.reserve(2);
    
}

void EffectSprite::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags){
#if CC_USE_CULLING
    // Don't do calculate the culling if the transform was not updated
    _insideBounds = (flags & FLAGS_TRANSFORM_DIRTY) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;
    
    if(_insideBounds)
#endif
    {
        // negative effects: order < 0
        int idx=0;
        for(auto &effect : _effects) {
            
            if(std::get<0>(effect) >=0)
                break;
            QuadCommand &q = std::get<2>(effect);
            q.init(_globalZOrder, _texture->getName(), std::get<1>(effect)->getGLProgramState(), _blendFunc, &_quad, 1, transform);
            renderer->addCommand(&q);
            idx++;
            
        }
        
        // normal effect: order == 0
        _quadCommand.init(_globalZOrder, _texture->getName(), getGLProgramState(), _blendFunc, &_quad, 1, transform);
        renderer->addCommand(&_quadCommand);
        
        // postive effects: oder >= 0
        for(auto it = std::begin(_effects)+idx; it != std::end(_effects); ++it) {
            QuadCommand &q = std::get<2>(*it);
            q.init(_globalZOrder, _texture->getName(), std::get<1>(*it)->getGLProgramState(), _blendFunc, &_quad, 1, transform);
            renderer->addCommand(&q);
            idx++;
        }
    }

}