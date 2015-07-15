//
//  MyControlButton.cpp
//  rz_Zom
//
//  Created by ly on 14-12-13.
//
//

#include "MyControlButton.h"


bool MyControlButton::init(bool isSwallowTouch){
    if (Layer::init())
    {
        // Initialise instance variables
        _state=Control::State::NORMAL;
        setEnabled(true);
        setSelected(false);
        setHighlighted(false);
        
        auto dispatcher = Director::getInstance()->getEventDispatcher();
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(isSwallowTouch);
        touchListener->onTouchBegan = CC_CALLBACK_2(Control::onTouchBegan, this);
        touchListener->onTouchMoved = CC_CALLBACK_2(Control::onTouchMoved, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(Control::onTouchEnded, this);
        touchListener->onTouchCancelled = CC_CALLBACK_2(Control::onTouchCancelled, this);
        
        dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        return true;
    }
    else
    {
        return false;
    }
}

MyControlButton* MyControlButton::create(Node* label, cocos2d::ui::Scale9Sprite* backgroundSprite,bool isSwallowTouch)
{
    if (label == NULL) {
        label = Label::create();
    }
    MyControlButton *pRet = new (std::nothrow) MyControlButton();
    pRet->initWithLabelAndBackgroundSprite(label, backgroundSprite,isSwallowTouch);
    pRet->autorelease();
    return pRet;
}

bool MyControlButton::initWithLabelAndBackgroundSprite(Node* node, ui::Scale9Sprite* backgroundSprite,bool isSallowTouch)
{
    if (init(isSallowTouch))
    {
        CCASSERT(node != nullptr, "node must not be nil.");
        LabelProtocol* label = dynamic_cast<LabelProtocol*>(node);
        CCASSERT(backgroundSprite != nullptr, "Background sprite must not be nil.");
        CCASSERT(label != nullptr, "label must not be nil.");
        
        _parentInited = true;
        
        _isPushed = false;
        
        // Adjust the background image by default
        setAdjustBackgroundImage(true);
        setPreferredSize(Size::ZERO);
        // Zooming button by default
        _zoomOnTouchDown = true;
        _scaleRatio = 1.1f;
        
        // Set the default anchor point
        ignoreAnchorPointForPosition(false);
        setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        
        // Set the nodes
        setTitleLabel(node);
        setBackgroundSprite(backgroundSprite);
        
        // Set the default color and opacity
        setColor(Color3B::WHITE);
        setOpacity(255.0f);
        setOpacityModifyRGB(true);
        
        // Initialize the dispatch table
        
        setTitleForState(label->getString(), Control::State::NORMAL);
        setTitleColorForState(node->getColor(), Control::State::NORMAL);
        setTitleLabelForState(node, Control::State::NORMAL);
        setBackgroundSpriteForState(backgroundSprite, Control::State::NORMAL);
        
        setLabelAnchorPoint(Vec2::ANCHOR_MIDDLE);
        
        // Layout update
        needsLayout();
        
        return true;
    }
    //couldn't init the Control
    else
    {
        return false;
    }
}


void MyControlButton::setTileString(std::string tileString,Control::State state){
    this->setTitleForState(tileString, state);
}
void MyControlButton::setBtnTouchRect(cocos2d::Rect touchRect){
    this->rect = touchRect;
    
//    LayerColor *layer = CCLayerColor::create();
//    layer->setColor(Color3B(255, 0, 0));
//    layer->setOpacity(50);
//    addChild(layer);
//    layer->setPosition(Vec2(touchRect.origin.x, touchRect.origin.y));
//    layer->setContentSize(touchRect.size);
//    layer->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    
//    this->setAnchorPoint(Vec2(0.5,0.5));
//    this->setContentSize(touchRect.size);
}
//
//bool MyControlButton::onTouchBegan(Touch *pTouch, Event *event)
//{
//    
//    
//    Vec2 touchLocation = pTouch->getLocation(); // Get the touch position
////    touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
//    touchLocation = Director::getInstance()->convertToUI(touchLocation);
//    if(rect.size.width&&rect.size.height){
//        if(rect.containsPoint(touchLocation)) {
////            CCLOG("wid is %f, hei is %f",rect.size.width,rect.size.height);
////            CCLOG("button out of visible rect, ignore touch event...");
//            return false;
//        }
//    }
//    
//    if (!isTouchInside(pTouch) || !isEnabled() || !isVisible() || !hasVisibleParents() )
//    {
////        CCLOG("is touch inside");
//        return false;
//    }
//    
//    for (Node *c = this->_parent; c != NULL; c = c->getParent())
//    {
//        if (c->isVisible() == false)
//        {
//            return false;
//        }
//    }
//    
//    _isPushed = true;
//    this->setHighlighted(true);
//    sendActionsForControlEvents(EventType::TOUCH_DOWN);
//    
//    return true;
//}
//
//
//void MyControlButton::onTouchEnded(Touch *pTouch, Event *pEvent)
//{
//    _isPushed = false;
//    setHighlighted(false);
//    if (isTouchInside(pTouch))
//    {
//        sendActionsForControlEvents(Control::EventType::TOUCH_UP_INSIDE);
//    }
//    else
//    {
//        sendActionsForControlEvents(Control::EventType::TOUCH_UP_OUTSIDE);
//    }
//}


void MyControlButton::setBlendFunc(){
    //sorry author ,it cant't work well.
//    BlendFunc blend = {GL_SRC_ALPHA , GL_ONE};
//    
//    _bgSprite = ui::Scale9Sprite::createWithSpriteFrame(getBackgroundSprite()->getSprite()->getSpriteFrame());
//    for (Node *  child : _bgSprite->_protectedChildren) {
//        ((Sprite*)child)->setBlendFunc(blend);
//    }
//    setBackgroundSpriteForState(_bgSprite, Control::State::HIGH_LIGHTED);
}

