//
// OpenGL1.cpp
// TestSpine
//
// Created by ly on 4/6/15.
//
//

#include "OpenGL1.h"
OpenGL1::OpenGL1()
{
    
}

OpenGL1::~OpenGL1()
{
    
}

Scene* OpenGL1::createScene()
{
    auto scene = Scene::create();
    auto layer = OpenGL1::create();
    scene->addChild(layer);
    return scene;
}

bool OpenGL1::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    initData();
    return true;
}

#pragma mark - initData
void OpenGL1::initData()
{
   this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
    
}
void OpenGL1::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags){
    
    Layer::visit(renderer,parentTransform,false);
    
    _command.init(_globalZOrder);
    _command.func = CC_CALLBACK_0(OpenGL1::onDraw, this);
    
    Director::getInstance()->getRenderer()->addCommand(&_command);
}

void OpenGL1::onDraw(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // add your codes here...
    /*!
     *  @author wuxingogo, 15-04-06 00:04:09
     *
     *  @brief  获得当前的着色器程序
     *
     *  @return nil
     */
    auto glProgram = getGLProgram();
    
    glProgram->use();
    /*!
     *  @author wuxingogo, 15-04-06 00:04:17
     *
     *  @brief  set cocos2dx default shader
     */
    glProgram->setUniformsForBuiltins();
    
    auto size = Director::getInstance()->getWinSize();
    /*!
     *  @author wuxingogo, 15-04-06 00:04:48
     *
     *  @brief  triangle vertex
     */
    float vertex[] = {
        0,0,
        size.width , size.height/2,
        size.width / 2, size.height,
        size.width , size.height,
        size.width , size.height/2
    };
    /*!
     *  @author wuxingogo, 15-04-06 00:04:27
     *
     *  @brief  color vertex
     */
    float color[] = {
        0,1,0,1,
        1,0,0,1,
        0,0,1,1,
        1,0,0,1,
        0,0,1,1
    };
    /*!
     *  @author wuxingogo, 15-04-06 00:04:40
     *
     *  @brief  set addtive GL Enable, the color and vertex.
     */
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
    
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertex);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, color);

    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 3);
    
    CHECK_GL_ERROR_DEBUG();
    
    
}
