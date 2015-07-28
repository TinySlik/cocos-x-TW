//
// OpenGL2.cpp
// TestSpine
//
// Created by ly on 4/6/15.
//
//

#include "OpenGL2.h"
OpenGL2::OpenGL2()
{
    
}

OpenGL2::~OpenGL2()
{
    
}

Scene* OpenGL2::createScene()
{
    auto scene = Scene::create();
    auto layer = OpenGL2::create();
    scene->addChild(layer);
    return scene;
}

bool OpenGL2::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    initData();
    return true;
}

void OpenGL2::initData()
{
   
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //创建和绑定vao
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
    
    typedef struct {
        float Position[2];
        float Color[4];
    } Vertex;
    
        auto size = Director::getInstance()->getVisibleSize();
    Vertex data[] =
    {
        {{-1,-1},{0,1,0,1}},
        
        {{1,-1},{0,1,0,1}},
        
        { {-1,1},{0,1,0,1}},
        
        {{1,1},{0,1,0,1}}
    };
    
    float vertercies[] = { 0,0,   //第一个点的坐标
        size.width, 0,   //第二个点的坐标
        size.width / 2, size.height};  //第三个点的坐标
    
    float color[] = { 0, 1,0, 1,  1,0,0, 1, 0, 0, 1, 1};
    
    GLubyte indices[] = { 0,1,2,  //第一个三角形索引
        2,3,1}; //第二个三角形索引
    
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertercies), vertercies, GL_STATIC_DRAW);
    
//    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    GLuint positionLocation = glGetAttribLocation(program->getProgram(), "a_position");
        CCLOG("position =%d", positionLocation);
    glEnableVertexAttribArray(positionLocation);
//    glVertexAttribPointer(positionLocation,
//                          2,
//                          GL_FLOAT,
//                          GL_FALSE,
//                          sizeof(Vertex),
//                         (GLvoid*)offsetof(Vertex,Position));
    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    
    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    
    GLuint colorLocation = glGetAttribLocation(program->getProgram(), "a_color");
    CCLOG("position =%d", colorLocation);
//    float uColor[] = {1.0, 0.0, 0.0, 1.0};
//    glUniform4fv(colorLocation,1, uColor);
    glEnableVertexAttribArray(colorLocation);
//    glVertexAttribPointer(colorLocation,
//                          4,
//                          GL_FLOAT,
//                          GL_FALSE,
//                          sizeof(Vertex),
//                          (GLvoid*)offsetof(Vertex,Color));
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    
    GLuint indexVBO;
    glGenBuffers(1, &indexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) , indices, GL_STATIC_DRAW);
    
    program->autorelease();
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void OpenGL2::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags){
    
    Layer::visit(renderer,parentTransform,false);
    
    _command.init(_globalZOrder);
    _command.func = CC_CALLBACK_0(OpenGL2::onDraw, this);
    
    Director::getInstance()->getRenderer()->addCommand(&_command);
}

void OpenGL2::onDraw(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // add your codes here...
//    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
//    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    
    auto glProgram = getGLProgram();
    
    glProgram->use();
    
    //set uniform values, the order of the line is very important
    glProgram->setUniformsForBuiltins();
    
    
    
    auto size = Director::getInstance()->getWinSize();
    //use vao
    glBindVertexArray(vao);
    
    GLuint uColorLocation = glGetUniformLocation(glProgram->getProgram(), "u_color");
    
    float uColor[] = {1.0, 1.0, 1.0, 1.0};
    glUniform4fv(uColorLocation,1, uColor);
    
//        glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE,(GLvoid*)0);
    
    glBindVertexArray(0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 6);
    CHECK_GL_ERROR_DEBUG();
    
//    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
//    
//    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
