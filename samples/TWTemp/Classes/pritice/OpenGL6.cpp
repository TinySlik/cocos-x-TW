//
// OpenGL6.cpp
// TestSpine
//
// Created by ly on 4/6/15.
//
//

#include "OpenGL6.h"
OpenGL6::OpenGL6()
{
    lookAt = Vec3(0, 0,0);
}

OpenGL6::~OpenGL6()
{
    
}

Scene* OpenGL6::createScene()
{
    auto scene = Scene::create();
    auto layer = OpenGL6::create();
    scene->addChild(layer);
    return scene;
}

bool OpenGL6::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    initData();
    initUI();
    return true;
}

void OpenGL6::initUI(){
    _slider = new Slider*[3];
    // add your codes here...
    for (int i = 0; i < 3; i++) {
        _slider[i] = Slider::create();
        _slider[i]->loadBarTexture("sliderTrack.png");
        _slider[i]->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
        _slider[i]->loadProgressBarTexture("sliderProgress.png");
        _slider[i]->setPosition(Vec2(_slider[i]->getContentSize() / 2 )+ Vec2(50,i *50+50));
        _slider[i]->setTag(i);
        _slider[i]->addEventListener(CC_CALLBACK_2(OpenGL6::sliderEvent, this));
        this->addChild(_slider[i]);
    }
}
void OpenGL6::sliderEvent(cocos2d::Ref *pSender, ui::Slider::EventType type){
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
void OpenGL6::initData()
{
    /*!
     *  @author wuxingogo, 15-04-06 21:04:13
     *
     *  @brief  读取纹理
     */
    Image *image = new Image;
    std::string imagePath = FileUtils::getInstance()->fullPathForFilename("HelloWorld.png");
    image->initWithImageFile(imagePath);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // add your codes here...
    typedef struct {
        float Position[3];
        float Color[4];
        float TexCoord[2];
    } Vertex;
    
//    Vertex data[] =
//    {
//        {{-1,-1},{0,1,0,1},{0,1}},
//        {{1,-1},{0,1,0,1},{1,1}},
//        { {-1,1},{0,1,0,1},{0,0}},
//        {{1,1},{0,1,0,1},{1,0}}
//    };
    
#define TEX_COORD_MAX   1
    Vertex Vertices[] = {
        // Front
        {{1, -1, 0}, {1, 0, 0, 1}, {TEX_COORD_MAX, 0}},
        {{1, 1, 0}, {0, 1, 0, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}},
        {{-1, 1, 0}, {0, 0, 1, 1}, {0, TEX_COORD_MAX}},
        {{-1, -1, 0}, {0, 0, 0, 1}, {0, 0}},
        // Back
        {{1, 1, -2}, {1, 0, 0, 1}, {TEX_COORD_MAX, 0}},
        {{-1, -1, -2}, {0, 1, 0, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}},
        {{1, -1, -2}, {0, 0, 1, 1}, {0, TEX_COORD_MAX}},
        {{-1, 1, -2}, {0, 0, 0, 1}, {0, 0}},
        // Left
        {{-1, -1, 0}, {1, 0, 0, 1}, {TEX_COORD_MAX, 0}},
        {{-1, 1, 0}, {0, 1, 0, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}},
        {{-1, 1, -2}, {0, 0, 1, 1}, {0, TEX_COORD_MAX}},
        {{-1, -1, -2}, {0, 0, 0, 1}, {0, 0}},
        // Right
        {{1, -1, -2}, {1, 0, 0, 1}, {TEX_COORD_MAX, 0}},
        {{1, 1, -2}, {0, 1, 0, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}},
        {{1, 1, 0}, {0, 0, 1, 1}, {0, TEX_COORD_MAX}},
        {{1, -1, 0}, {0, 0, 0, 1}, {0, 0}},
        // Top
        {{1, 1, 0}, {1, 0, 0, 1}, {TEX_COORD_MAX, 0}},
        {{1, 1, -2}, {0, 1, 0, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}},
        {{-1, 1, -2}, {0, 0, 1, 1}, {0, TEX_COORD_MAX}},
        {{-1, 1, 0}, {0, 0, 0, 1}, {0, 0}},
        // Bottom
        {{1, -1, -2}, {1, 0, 0, 1}, {TEX_COORD_MAX, 0}},
        {{1, -1, 0}, {0, 1, 0, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}},
        {{-1, -1, 0}, {0, 0, 1, 1}, {0, TEX_COORD_MAX}},
        {{-1, -1, -2}, {0, 0, 0, 1}, {0, 0}}
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    
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
    
   
    
    
    
    GLuint textureLocation = glGetAttribLocation(program->getProgram(), "a_coord");
    glEnableVertexAttribArray(textureLocation);
    glVertexAttribPointer(textureLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoord));
    
    GLuint indexVBO;
    glGenBuffers(1, &indexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) , indices, GL_STATIC_DRAW);
    
    glGenTextures(1, &textureId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    
    unsigned char *imageData = image->getData();
    int width = image->getWidth();
    int height = image->getHeight();
    //调用此方法把imageData的图像数据传递给GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE,//must be GL_UNSIGNED_BYTE
                 imageData);
    //别忘了释放image内存
    CC_SAFE_DELETE(image);
    
    program->autorelease();
    
  
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGL6::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags){
    Layer::visit(renderer,parentTransform,false);
    
    _command.init(-1);
    _command.func = CC_CALLBACK_0(OpenGL6::onDraw, this);
    
    Director::getInstance()->getRenderer()->addCommand(&_command);
}
void OpenGL6::onDraw(){
    //question1: why the triangle goes to the up side
    //如果使用对等矩阵，则三角形绘制会在最前面
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    
    Mat4 modelViewMatrix;
//    Mat4::createLookAt(Vec3(0,0,1), Vec3(0,0,0), Vec3(0,1,0), &modelViewMatrix);
    //camera的位置位于（0，0，1）,然后看着(0,0,0)点，并且头朝上（0,1,0）
        Mat4::createLookAt(Vec3(0,0,1), lookAt, Vec3(0,1,0), &modelViewMatrix);
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
    GLuint textureLocation = glGetUniformLocation(glProgram->getProgram(),"CC_Texture0");
    glUniform1i(textureLocation, 0);
    
    
    
    auto size = Director::getInstance()->getWinSize();
    
    //use vao
    glBindVertexArray(vao);
    
    
    
    GLuint uColorLocation = glGetUniformLocation(glProgram->getProgram(), "u_color");
    
    float uColor[] = {1.0, 1.0, 1.0, 1.0};
    glUniform4fv(uColorLocation,1, uColor);
    
    GL::bindTexture2D(textureId);
    
//    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE,(GLvoid*)0);
    
    glBindVertexArray(0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 36);
    CHECK_GL_ERROR_DEBUG();
    
    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

}