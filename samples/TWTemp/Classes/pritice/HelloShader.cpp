//
//  HelloShader.cpp
//  TestSpine
//
//  Created by ly on 4/5/15.
//
//

#include "HelloShader.h"
#include "EffectSprite.h"


HelloShader::HelloShader(){
    auto winSize = Director::getInstance()->getVisibleSize();
    
    EffectSprite *_sprite = EffectSprite::create("HelloWorld.png");
    _sprite->setPosition(winSize / 2);
    addChild(_sprite);
    
    _sprite->setEffect(EffectBlur::create());
}

Scene * HelloShader::createScene(){
    Scene * scene = Scene::create();
    auto layer = HelloShader::create();
    scene->addChild(layer);
    return scene;
}