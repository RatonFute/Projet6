#include "MainMenu.h"
#include <iostream>
#include <string>

USING_NS_CC;

Scene* MainMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenu::create();
    scene->addChild(layer);

    return scene;
}

bool MainMenu::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto label = Label::createWithTTF("Lemmings World", "fonts/Marker Felt.ttf", 24);
    auto play = Label::createWithTTF("Play", "fonts/Marker Felt.ttf", 20);
    auto options = Label::createWithTTF("Options", "fonts/Marker Felt.ttf", 20);
    //options->enableOutline(Color4B::RED, 1);

    auto quit = Label::createWithTTF("Quit", "fonts/Marker Felt.ttf", 20);


    // position the label on the center of the screen
    label->setPosition(Vec2(visibleSize.width/2, visibleSize.height - label->getContentSize().height));
    play->setPosition(Vec2(visibleSize.width /2, visibleSize.height - label->getContentSize().height *3));
    options->setPosition(Vec2(visibleSize.width /2, visibleSize.height - label->getContentSize().height *4));
    quit->setPosition(Vec2(visibleSize.width /2, visibleSize.height - label->getContentSize().height *5));

    // add the label as a child to this layer
    this->addChild(label, 1);
    this->addChild(play, 1);
    this->addChild(options, 1);
    this->addChild(quit, 1);


    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseUp = CC_CALLBACK_1(MainMenu::onMouseUp, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    return true;
}

void MainMenu::onMouseUp(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    int b = int (e->getMouseButton());
    Vec2 Mousep = e->getLocationInView();
    //Rect playbox = this->play->getBoundingBox();
    //e->getCursorX() + e->getCursorY();

}

void MainMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}


