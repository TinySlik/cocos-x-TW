//
// OpenGL4.h
// TestSpine
//
// Created by ly on 4/6/15.
//
//

#ifndef __TestSpine__OpenGL4__
#define __TestSpine__OpenGL4__

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

/*!
 *  @author wuxingogo, 15-04-06 19:04:43
 *
 *  @brief  使用VBO索引
 */
class OpenGL4 : public Layer
{
public:
    OpenGL4();
    ~OpenGL4();
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(OpenGL4);
    
private:
    void initData();
    
    virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags);
    void onDraw();
    CustomCommand _command;
    
    GLuint vao;
    GLuint vertexVBO;
    GLuint colorVBO;
};

#endif /* defined(__TestSpine__OpenGL4__) */