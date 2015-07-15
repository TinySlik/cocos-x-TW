//
// OpenGL5.h
// TestSpine
//
// Created by ly on 4/6/15.
//
//

#ifndef __TestSpine__OpenGL5__
#define __TestSpine__OpenGL5__

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
class OpenGL5 : public Layer
{
public:
    OpenGL5();
    ~OpenGL5();
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(OpenGL5);
    
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
};

#endif /* defined(__TestSpine__OpenGL5__) */