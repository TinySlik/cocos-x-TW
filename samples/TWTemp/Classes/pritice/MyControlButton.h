//
//  MyControlButton.h
//  rz_Zom
//
//  Created by ly on 14-12-13.
//
//

#ifndef __rz_Zom__MyControlButton__
#define __rz_Zom__MyControlButton__

#include "cocos2d.h"
#include <cocos-ext.h>
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCInputDelegate.h"
//#include "MyScrollView.h"
using namespace cocos2d;
using namespace extension;
/*!
 *  @author wuxingogo, 15-02-25 19:02:51
 *
 *  @brief  this MyControlButton by author ly,override control button touch in 3.x
 *  @brief  quick setting blend function ,you can change sm in the 'setBlendFunc' methof.
 */
class  MyControlButton : public ControlButton,public cocostudio::InputDelegate{
public:
public:
    virtual bool init(bool isSwallowTouch);
    
    virtual bool initWithLabelAndBackgroundSprite(Node* label, cocos2d::ui::Scale9Sprite* backgroundSprite,bool isSwallowTouch);
    
    static MyControlButton* create(Node* label, cocos2d::ui::Scale9Sprite* backgroundSprite,bool isSwallowTouch = true);
    
    void setBtnTouchRect(cocos2d::Rect touchRect);
    cocos2d::Rect rect;
    
//    virtual bool isTouchInside(Touch * touch);
    
//    virtual bool onTouchBegan(Touch *touch, Event *event) override;
//    virtual void onTouchEnded(Touch * touch,Event * event) override;
    virtual void setBlendFunc();
    
    virtual void setTileString(std::string,Control::State = Control::State::NORMAL);

protected:
    ui::Scale9Sprite * _bgSprite;
   
};
#endif /* defined(__rz_Zom__MyControlButton__) */
