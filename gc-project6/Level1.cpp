
#include "Level1.h"
#include <iostream>
#include <string>

USING_NS_CC;

Scene* Level1::createScene()
{
    Scene* scene = Scene::create();
    Level1* layer = Level1::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool Level1::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    //auto map = TMXTiledMap::create("Map.tmx");
    //this->addChild(map);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(Level1::menuCloseCallback, this));


    float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
    float y = origin.y + closeItem->getContentSize().height / 2;
    closeItem->setPosition(Vec2(x, y));


    //// create menu, it's an autorelease object
    auto MainMenu = Menu::create(closeItem, NULL);
    MainMenu->setPosition(Vec2::ZERO);
    this->addChild(MainMenu, 1);

    ///////////////////////////////
    //// 3. add your codes below...

    //// add a label shows "Hello World"
    //// create and initialize a label




    // add "Level1" splash screen"
    //auto sprite = Sprite::create("Level1.png");
    //if (sprite == nullptr)
    //{
    //    problemLoading("'Level1.png'");
    //}
    //else
    //{
        // position the sprite on the center of the screen
      //  sprite->setPosition(Vec2(0 , visibleSize.height/2 + origin.y));
     /*   auto moveBy = MoveBy::create(2, Vec2(visibleSize.width , 0));
        sprite->runAction(moveBy);
        if(sprite->getPositionX() == visibleSize.width)
        {
            auto moveBy = MoveBy::create(2, Vec2(visibleSize.width, 500));
            sprite->runAction(moveBy);

        }*/

        // add the sprite as a child to this layer
          // this->addChild(sprite, 0);
       //}
    return true;
}


void Level1::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
