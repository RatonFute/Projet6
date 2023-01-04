

#ifndef __Level1_SCENE_H__
#define __Level1_SCENE_H__

#include "cocos2d.h"

class Level1 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Level1);
};

#endif // __Level1_SCENE_H__
