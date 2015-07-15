//
// OpenGL6.h
// TestSpine
//
// Created by ly on 4/6/15.
//
//

#ifndef __TestSpine__OpenGL6__
#define __TestSpine__OpenGL6__

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

#include "UISlider.h"
using namespace cocos2d::ui;

/*!
 *  @author wuxingogo, 15-04-06 19:04:51
 *
 *  @brief  绘制立方体
 */
class OpenGL6 : public Layer
{
public:
    OpenGL6();
    ~OpenGL6();
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(OpenGL6);
    
private:
    void initData();
    
    void initUI();
    
    virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags);
    void onDraw();
    CustomCommand _command;
    
    GLuint vao;
    GLuint vertexVBO;
    GLuint colorVBO;
    
    void sliderEvent(Ref *pSender, ui::Slider::EventType type);
    Slider** _slider;
    
    Vec3 lookAt;
    
    GLuint textureId;
};

#endif /* defined(__TestSpine__OpenGL6__) */