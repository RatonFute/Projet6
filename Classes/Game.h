#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class Game : public cocos2d::Scene
{
public:
    Game();
    ~Game();

    cocos2d::Sprite* _sprite;
    cocos2d::Sprite* pick;
    cocos2d::Sprite* _JumpSprite;
    cocos2d::PhysicsBody* _spriteBody;
    cocos2d::PhysicsBody* _JumpBox;

    static cocos2d::Scene* createScene();
    virtual bool init();

    void update(float dt);
    void onMouseUp(cocos2d::Event* event);
    void onMouseMove(cocos2d::Event* event);
    void End(cocos2d::Ref* pSender);
    void MapColl();
    void ActionMenu();

    void Kamikaze(cocos2d::Ref* pSender);
    void Builder(cocos2d::Ref* pSender);
    void Jumper(cocos2d::Ref* pSender);

    cocos2d::Sprite* createBlock(char*, float, float, float, float, int);
    int _moveDir, _jump, count;
    float _movement, _time;
    bool _isGrounded, _isJumping, active;
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    // implement the "static create()" method manually
    CREATE_FUNC(Game);
};

#endif // __HELLOWORLD_SCENE_H__
