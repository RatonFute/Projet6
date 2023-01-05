#ifndef __MainMenu_SCENE_H__
#define __MainMenu_SCENE_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void Play(cocos2d::Ref* pSender);
    void Quit(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);

//protected:
//    Label play;
//    Label* options;
//    Label* quit;
};

#endif // __MainMenu_SCENE_H__
