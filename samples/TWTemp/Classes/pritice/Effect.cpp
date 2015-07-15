//
//  Effect.cpp
//  TestSpine
//
//  Created by ly on 4/5/15.
//
//

#include "Effect.h"

Effect::Effect()
: _glprogramstate(nullptr)
{
    
}
Effect::~Effect(){
    CC_SAFE_RELEASE_NULL(_glprogramstate);
}



bool Effect::initGLProgramState(const std::string &vertexFilename,const std::string &fragmentFilename){
    auto fileUtiles = FileUtils::getInstance();
    auto vertexFullPath = fileUtiles->fullPathForFilename(vertexFilename);
    auto fragmentFullPath = fileUtiles->fullPathForFilename(fragmentFilename);
    auto vertSource = fileUtiles->getStringFromFile(vertexFullPath);
    auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
    
    
    /** Initializes the GLProgram with a vertex and fragment with bytes array
     * @js initWithString
     * @lua initWithString
     */
//    auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
    auto glprogram = GLProgram::createWithByteArrays(vertSource.c_str(), fragSource.c_str());
    
    _glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
    _glprogramstate->retain();
    
    return _glprogramstate != nullptr;
}


void EffectBlur::setTarget(EffectSprite *sprite)
{
    Size winSize = Director::getInstance()->getVisibleSize();
    Size size = ((Sprite*)sprite)->getTexture()->getContentSizeInPixels();
    
    Vec3 color(1.0f, 0.2f, 0.3f);
    GLfloat radius = 0.01f;
    GLfloat threshold = 1.75;
    
    Sprite * normal =Sprite::create("CloseNormal.png");
//    _glprogramstate->setUniformVec4("a_position", Vec4(0, 0, 0, 0));
//    _glprogramstate->setUniformFloat("u_threshold", threshold);
//    _glprogramstate->setUniformFloat("u_radius", radius);
//    _glprogramstate->setUniformVec2("resolution", winSize);
//    _glprogramstate->setUniformVec2("center", winSize / 2);
//    _glprogramstate->setUniformFloat("u_interpolate", 0.5);
//    _glprogramstate->setUniformFloat("blurRadius", _blurRadius);
//    _glprogramstate->setUniformFloat("sampleNum", _blurSampleNum);
}

bool EffectBlur::init(float blurRadius, float sampleNum)
{
    initGLProgramState("Shaders/helloworld.vert","Shaders/example_normal.fsh");
    _blurRadius = blurRadius;
    _blurSampleNum = sampleNum;
    
    return true;
}

void EffectBlur::setBlurRadius(float radius)
{
    _blurRadius = radius;
}

void EffectBlur::setBlurSampleNum(float num)
{
    _blurSampleNum = num;
}