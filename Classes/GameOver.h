#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class GameOver : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void PlayAgain(cocos2d::Ref* pSender);
    void BackToMenu(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(GameOver);

    //protected:
    //    Label play;
    //    Label* options;
    //    Label* quit;
};

#endif // __GameOver_SCENE_H__
