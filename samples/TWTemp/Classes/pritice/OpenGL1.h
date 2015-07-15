//
// OpenGL1.h
// TestSpine
//
// Created by ly on 4/6/15.
//
//
 
#ifndef __TestSpine__OpenGL1__
#define __TestSpine__OpenGL1__
 
#include "cocos2d.h"
USING_NS_CC;
 
class OpenGL1 : public Layer
{
public:
    OpenGL1();
    ~OpenGL1();
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(OpenGL1);
     
private:
    void initData();
    virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags);
    void onDraw();
    CustomCommand _command;
};
 
#endif /* defined(__TestSpine__OpenGL1__) */