#include "MainMenu.h"
#include "Game.h" 
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
    // position the label on the center of the screen
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - label->getContentSize().height / 2));
    // add the label as a child to this layer
    this->addChild(label, 1);

    auto menu_item_1 = MenuItemFont::create("Play", CC_CALLBACK_1(MainMenu::Play, this));
    auto menu_item_2 = MenuItemFont::create("Options", CC_CALLBACK_1(MainMenu::Options, this));
    auto menu_item_3 = MenuItemFont::create("Quit", CC_CALLBACK_1(MainMenu::Quit, this));
    
    auto* menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, NULL);
    menu->alignItemsVertically();
    this->addChild(menu);

    return true;
}

void MainMenu::Play(cocos2d::Ref* pSender){
    auto scene = Game::createScene();
    Director::getInstance()->replaceScene(scene);
    //Director::getInstance()->pushScene(scene);
}

void MainMenu::Options(cocos2d::Ref* pSender) {
    auto scene = Game::createScene();
}


void MainMenu::Quit(cocos2d::Ref* pSender) {
    Director::getInstance()->end();
}
