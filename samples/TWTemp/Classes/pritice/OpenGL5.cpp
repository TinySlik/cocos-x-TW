//
// OpenGL5.cpp
// TestSpine
//
// Created by ly on 4/6/15.
//
//

#include "OpenGL5.h"
OpenGL5::OpenGL5()
{
    lookAt = Vec3(0, 0,0);
}

OpenGL5::~OpenGL5()
{
    
}

Scene* OpenGL5::createScene()
{
    auto scene = Scene::create();
    auto layer = OpenGL5::create();
    scene->addChild(layer);
    return scene;
}

bool OpenGL5::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    initData();
    initUI();
    return true;
}

void OpenGL5::initUI(){
    _slider = new Slider*[3];
    // add your codes here...
    for (int i = 0; i < 3; i++) {
        _slider[i] = Slider::create();
        _slider[i]->loadBarTexture("sliderTrack.png");
        _slider[i]->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
        _slider[i]->loadProgressBarTexture("sliderProgress.png");
        _slider[i]->setPosition(Vec2(_slider[i]->getContentSize() / 2 )+ Vec2(50,i *50+50));
        _slider[i]->setTag(i);
        _slider[i]->addEventListener(CC_CALLBACK_2(OpenGL5::sliderEvent, this));
        this->addChild(_slider[i]);
    }
}
void OpenGL5::sliderEvent(cocos2d::Ref *pSender, ui::Slider::EventType type){
    Slider * operation =(Slider*)pSender;
    float value = operation->getPercent() / 20.0f;
    switch (operation->getTag()) {
        case 0:
            lookAt.x = value;
            break;
        case 1:
            lookAt.y = value;
            break;
        case 2:
            lookAt.y = value;
            break;
            
        default:
            break;
    }
}

#pragma mark - initData
void OpenGL5::initData()
{
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // add your codes here...
    typedef struct {
        float Position[3];
        float Color[4];
    } Vertex;
    
    Vertex data[] =
    {
        // Front
        {{1, -1, 0}, {1, 0, 0, 1}},
        {{1, 1, 0}, {0, 1, 0, 1}},
        {{-1, 1, 0}, {0, 0, 1, 1}},
        {{-1, -1, 0}, {0, 0, 0, 1}},
        // Back
        {{1, 1, -2}, {1, 0, 0, 1}},
        {{-1, -1, -2}, {0, 1, 0, 1}},
        {{1, -1, -2}, {0, 0, 1, 1}},
        {{-1, 1, -2}, {0, 0, 0, 1}},
        // Left
        {{-1, -1, 0}, {1, 0, 0, 1}},
        {{-1, 1, 0}, {0, 1, 0, 1}},
        {{-1, 1, -2}, {0, 0, 1, 1}},
        {{-1, -1, -2}, {0, 0, 0, 1}},
        // Right
        {{1, -1, -2}, {1, 0, 0, 1}},
        {{1, 1, -2}, {0, 1, 0, 1}},
        {{1, 1, 0}, {0, 0, 1, 1}},
        {{1, -1, 0}, {0, 0, 0, 1}},
        // Top
        {{1, 1, 0}, {1, 0, 0, 1}},
        {{1, 1, -2}, {0, 1, 0, 1}},
        {{-1, 1, -2}, {0, 0, 1, 1}},
        {{-1, 1, 0}, {0, 0, 0, 1}},
        // Bottom
        {{1, -1, -2}, {1, 0, 0, 1}},
        {{1, -1, 0}, {0, 1, 0, 1}},
        {{-1, -1, 0}, {0, 0, 1, 1}},
        {{-1, -1, -2}, {0, 0, 0, 1}}
    };
    /*!
     *  @author wuxingogo, 15-04-06 20:04:09
     *
     *  @brief  index
     */
    GLubyte indices[] = {
        // Front
        0, 1, 2,
        2, 3, 0,
        // Back
        4, 5, 6,
        4, 5, 7,
        // Left
        8, 9, 10,
        10, 11, 8,
        // Right
        12, 13, 14,
        14, 15, 12,
        // Top
        16, 17, 18,
        18, 19, 16,
        // Bottom
        20, 21, 22,
        22, 23, 20
    };
    
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
    
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    
    GLuint positionLocation = glGetAttribLocation(program->getProgram(), "a_position");
    CCLOG("position = %d", positionLocation);
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(
                          GLProgram::VERTEX_ATTRIB_POSITION,
                          3, GL_FLOAT, GL_FALSE,
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
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGL5::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags){
    Layer::visit(renderer,parentTransform,false);
    
    _command.init(_globalZOrder);
    _command.func = CC_CALLBACK_0(OpenGL5::onDraw, this);
    
    Director::getInstance()->getRenderer()->addCommand(&_command);
}
void OpenGL5::onDraw(){
    //question1: why the triangle goes to the up side
    //如果使用对等矩阵，则三角形绘制会在最前面
    
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    Mat4 modelViewMatrix;
    Mat4::createLookAt(Vec3(0,0,1), Vec3(0,0,0), Vec3(0,1,0), &modelViewMatrix);
    //camera的位置位于（0，0，1）,然后看着(0,0,0)点，并且头朝上（0,1,0）
//    Mat4::createLookAt(Vec3(0,0,1), lookAt, Vec3(0,1,0), &modelViewMatrix);
    modelViewMatrix.translate(0, 0, -5);
    
    static float rotation = 0;
    modelViewMatrix.rotate(Vec3(1,1,1),CC_DEGREES_TO_RADIANS(rotation));
    rotation++;
    if (rotation > 360) {
        rotation = 0;
    }
    
    
    Mat4 projectionMatrix;
    Mat4::createPerspective(60, 480/320, 1.0, 42, &projectionMatrix);
    Director::getInstance()->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, projectionMatrix);
    
    
    Director::getInstance()->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, modelViewMatrix);
    
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
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE,(GLvoid*)0);
    
    glBindVertexArray(0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 36);
    CHECK_GL_ERROR_DEBUG();
    
    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}