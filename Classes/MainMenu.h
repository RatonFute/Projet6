#ifndef __MainMenu_SCENE_H__
#define __MainMenu_SCENE_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuCloseCallback(cocos2d::Ref* pSender);
    void onMouseUp(cocos2d::Event* event);
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

    void Play(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);


};

#endif // __MainMenu_SCENE_H__
