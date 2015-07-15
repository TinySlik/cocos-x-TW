//
// OpenGL4.cpp
// TestSpine
//
// Created by ly on 4/6/15.
//
//

#include "OpenGL4.h"
OpenGL4::OpenGL4()
{
    
}

OpenGL4::~OpenGL4()
{
    
}

Scene* OpenGL4::createScene()
{
    auto scene = Scene::create();
    auto layer = OpenGL4::create();
    scene->addChild(layer);
    return scene;
}

bool OpenGL4::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    initData();
    return true;
}

#pragma mark - initData
void OpenGL4::initData()
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
    
    
    
    auto size = Director::getInstance()->getVisibleSize();
    
    float vertercies[] ={
        -1,-1,
        1, -1,
        -1, 1,
        1,1
    };
    
    float color[] = { 0, 1,0, 1,
        0,1,0, 1,
        0, 1, 0, 1,
        0, 1,0, 1,
        0,1,0, 1,
        0,1, 0, 1
    };
    
    GLubyte indices[] = { 0,1,2,  //第一个三角形索引
        2,3,1
    }; //第二个三角形索引
    
    /*!
     *  @author wuxingogo, 15-04-06 19:04:57
     *
     *  @brief  模仿 V3F_C4B_T2F结构体
     */
    typedef struct {
        float Position[2];
        float Color[4];
    } Vertex;
    
    Vertex data[] =
    {
        {{-1,-1},{0,1,0,1}},
        {{1,-1},{0,1,0,1}},
        { {-1,1},{0,1,0,1}},
        {{1,1},{0,1,0,1}}
    };
    
    /*!
     *  @author wuxingogo, 15-04-06 19:04:38
     *
     *  @brief  绑定(装订)顶点缓冲区
     */
    //    glGenBuffers(1, &vertexVBO);
    //    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(vertercies), vertercies, GL_STATIC_DRAW);
    /*!
     *  @author wuxingogo, 15-04-06 19:04:45
     *
     *  @brief  使用VBO索引,只需要一次绑定
     */
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    
    GLuint positionLocation = glGetAttribLocation(program->getProgram(), "a_position");
    CCLOG("position = %d", positionLocation);
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(
                          GLProgram::VERTEX_ATTRIB_POSITION,
                          2, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex),
                          (GLvoid* )offsetof(Vertex,Position));
    
    
    /*!
     *  @author wuxingogo, 15-04-06 19:04:26
     *
     *  @brief  绑定颜色缓冲区
     */
    //    glGenBuffers(1, &colorVBO);
    //    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    
    GLuint colorLocation = glGetAttribLocation(program->getProgram(), "a_color");
    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(
                          GLProgram::VERTEX_ATTRIB_COLOR,
                          4,
                          GL_FLOAT, GL_FALSE,
                          sizeof(Vertex),
                          (GLvoid* )offsetof(Vertex,Color));
    
    program->autorelease();
    
    GLuint indexVBO;
    glGenBuffers(1, &indexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) , indices, GL_STATIC_DRAW);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void OpenGL4::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags){
    Layer::visit(renderer,parentTransform,false);
    
    _command.init(_globalZOrder);
    _command.func = CC_CALLBACK_0(OpenGL4::onDraw, this);
    
    Director::getInstance()->getRenderer()->addCommand(&_command);
}
void OpenGL4::onDraw(){
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
    
    //    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE,(GLvoid*)0);
    
    glBindVertexArray(0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 6);
    CHECK_GL_ERROR_DEBUG();
    
    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}