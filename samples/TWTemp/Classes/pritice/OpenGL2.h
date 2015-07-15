//
// OpenGL2.h
// TestSpine
//
// Created by ly on 4/6/15.
//
//

#ifndef __TestSpine__OpenGL2__
#define __TestSpine__OpenGL2__

/**
 *　　　　　　　　┏┓              ┏┓+ +
 *　　　　　　　┏┛┻━━━┛┻┓ + +
 *　　　　　　　┃　　　　　　　┃
 *　　　　　　　┃　　　━　　　┃ ++ + + +
 *　　　　　　 ████━████ ┃+
 *　　　　　　　┃　　　　　　　┃ +
 *　　　　　　　┃　　　┻　　　┃
 *　　　　　　　┃　　　　　　　┃ + +
 *　　　　　　　┗━┓　　　┏━┛
 *　　　　　　　　　┃　　　┃
 *　　　　　　　　　┃　　　┃ + + + +
 *　　　　　　　　　┃　　　┃　　　　Code is far away from bug with the animal protecting
 *　　　　　　　　　┃　　　┃ + 　　　　神兽保佑,代码无bug
 *　　　　　　　　　┃　　　┃
 *　　　　　　　　　┃　　　┃　　+
 *　　　　　　　　　┃　 　　┗━━━┓ + +
 *　　　　　　　　　┃ 　　　　　　　┣┓
 *　　　　　　　　　┃ 　　　　　　　┏┛
 *　　　　　　　　　┗┓┓┏━┳┓┏┛ + + + +
 *　　　　　　　　　　┃┫┫　┃┫┫
 *　　　　　　　　　　┗┻┛　┗┻┛+ + + +
 */

#include "cocos2d.h"
USING_NS_CC;

class OpenGL2 : public Layer
{
public:
    OpenGL2();
    ~OpenGL2();
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(OpenGL2);
    
private:
    void initData();
    
    virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags);
    void onDraw();
    CustomCommand _command;
    
    GLuint vao;
    GLuint vertexVBO;
    GLuint colorVBO;
};

#endif /* defined(__TestSpine__OpenGL2__) */