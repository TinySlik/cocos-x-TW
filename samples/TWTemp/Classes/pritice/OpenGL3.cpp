//
// OpenGL3.cpp
// TestSpine
//
// Created by ly on 4/6/15.
//
//

#include "OpenGL3.h"
OpenGL3::OpenGL3()
{
    
}

OpenGL3::~OpenGL3()
{
    
}

Scene* OpenGL3::createScene()
{
    auto scene = Scene::create();
    auto layer = OpenGL3::create();
    scene->addChild(layer);
    return scene;
}

bool OpenGL3::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    initData();
    return true;
}

#pragma mark - initData
void OpenGL3::initData()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // add your codes here...
    //create my own program
    auto program = new GLProgram;
    program->initWithFilenames("myVertextShader.vert", "myFragmentShader.frag");
    program->link();
    //set uniform locations
    program->updateUniforms();
    
    
//    this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
    this->setGLProgram(program);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    float vertercies[] = { -1,-1,   //第一个点的坐标
        1, -1,   //第二个点的坐标
        0, 1};  //第三个点的坐标
    
    float color[] = {
        0, 1,0, 1,
        1,0,0, 1,
        0, 0, 1, 1
    };
    
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertercies), vertercies, GL_STATIC_DRAW);
    GLuint positionLocation = glGetAttribLocation(program->getProgram(), "a_position");
    CCLOG("position = %d", positionLocation);
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    
    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    GLuint colorLocation = glGetAttribLocation(program->getProgram(), "a_color");
    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    
    program->autorelease();
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void OpenGL3::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags){
    Layer::visit(renderer,parentTransform,false);
    
    _command.init(_globalZOrder);
    _command.func = CC_CALLBACK_0(OpenGL3::onDraw, this);
    
    Director::getInstance()->getRenderer()->addCommand(&_command);
}
void OpenGL3::onDraw(){
    //question1: why the triangle goes to the up side
    //如果使用对等矩阵，则三角形绘制会在最前面
    
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    auto glProgram = getGLProgram();
    
    glProgram->use();
    
    //set uniform values, the order of the line is very important
    glProgram->setUniformsForBuiltins();
    
    
    auto size = Director::getInstance()->getWinSize();
    
    //use vao
    glBindVertexArray(vao);
    
    GLuint uColorLocation = glGetUniformLocation(glProgram->getProgram(), "a_color");
    float uColor[] = {1.0, 0.0, 0.0, 1.0};
    glUniform4fv(uColorLocation,1, uColor);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glBindVertexArray(0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 3);
    CHECK_GL_ERROR_DEBUG();
    
    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}