#include "Game.h"
#include "MainMenu.h"
#include "GameOver.h"
#include <iostream>
#include <string>

USING_NS_CC;

Scene* GameOver::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOver::create();
    scene->addChild(layer);

    return scene;
}

bool GameOver::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto label = Label::createWithTTF("Game ended", "fonts/Marker Felt.ttf", 34);

    auto menu_item1 = MenuItemFont::create("Play again", CC_CALLBACK_1(GameOver::PlayAgain, this));
    auto menu_item2 = MenuItemFont::create("Back to menu", CC_CALLBACK_1(GameOver::BackToMenu, this));
    

    menu_item1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 3));
    menu_item2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 2));

    auto* menu = Menu::create(menu_item1, menu_item2, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    // position the label on the center of the screen
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);

   
    return true;
}

void GameOver::PlayAgain(cocos2d::Ref* pSender) {
    auto scene = Game::createScene();
    Director::getInstance()->replaceScene(scene);
    //Director::getInstance()->pushScene(scene);
}
void GameOver::BackToMenu(cocos2d::Ref* pSender) {
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(scene);
    //Director::getInstance()->pushScene(scene);
}





