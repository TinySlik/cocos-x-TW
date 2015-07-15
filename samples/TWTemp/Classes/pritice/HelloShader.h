//
//  HelloShader.h
//  TestSpine
//
//  Created by ly on 4/5/15.
//
//

#ifndef __TestSpine__HelloShader__
#define __TestSpine__HelloShader__

#include "cocos2d.h"
USING_NS_CC;

class HelloShader  : public Layer{
    
public:
    HelloShader();
    CREATE_FUNC(HelloShader);
    static Scene * createScene();
    
};

#endif /* defined(__TestSpine__HelloShader__) */
