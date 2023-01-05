#include "Game.h"
#include "MainMenu.h"
#include "GameOver.h"

#define SPEED 1.0
//Collision category
#define PLAYER 1
#define WALL 2
#define FLOOR 3
#define ENDFLAG 4
#define JUMPBOX 5

USING_NS_CC;

Scene* Game::createScene()
{
    return Game::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

Game::Game() {
    
    _JumpSprite = Sprite::create("CloseSelected.png");
    
    _JumpBox = PhysicsBody::createBox(Size(50, 50), PhysicsMaterial(0.0f, 0.0f, 0.0f));
    _moveDir = -1;
    _jump = 450.0;
    _time = 30.0;
    _isJumping = false;
}

Game::~Game() {}



// on "init" you need to initialize your instance
bool Game::init()
{
    if (!Scene::initWithPhysics())
    {

    }
    getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    getPhysicsWorld()->setGravity(Vect(0.0f, -200.0f));
    Director* director = Director::getInstance();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto map = TMXTiledMap::create("Map.tmx");
    this->addChild(map);


    if (_sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        for (int i = 0; i < 3; i++) {
            _sprite = Sprite::create("CloseSelected.png");
            _sprite->setPosition(Vec2(450, 200));
            _spriteBody = PhysicsBody::createBox(Size(20.0f, 20.0f), PhysicsMaterial(0.0f, 1.5f, 0.2f));
            _spriteBody->setDynamic(true);
            _spriteBody->setVelocityLimit(200.0);
            _spriteBody->setRotationEnable(false);
            _spriteBody->setCollisionBitmask(1);
            _spriteBody->setContactTestBitmask(true);
            _sprite->addComponent(_spriteBody);
        }
        //player
        
    }

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    //collision listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Game::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    //mouse position and click release listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(Game::onMouseMove, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(Game::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    char* path = "CloseSelected.png";
    char* path2 = "CloseSelected.png";
    char* poke = "CloseSelected.png";

    //----------------SPRITES----------------
    
    //walls
    Sprite* Lwall = createBlock(path2, origin.x, visibleSize.height / 2 + origin.y, 5.0, 320.0, WALL);
    Sprite* Rwall = createBlock(path2, visibleSize.width + origin.x, visibleSize.height / 2 + origin.y, 5.0, 320.0, WALL);
    Sprite* wallTopR = createBlock(path2, 280, 180, 5.0, 50.0, WALL);
    addChild(Lwall);
    addChild(Rwall);
    addChild(wallTopR);

    //Floor
    Sprite* FloorLvl = createBlock(path, visibleSize.width / 2 + origin.x, origin.y, visibleSize.width, 5.0, FLOOR);
    Sprite* Plat1 = createBlock(path, 120, 100, 260, 15.0, FLOOR);
    Sprite* Plat2 = createBlock(path, 400, 160, 260, 15.0, FLOOR);
    addChild(FloorLvl);
    addChild(Plat1);
    addChild(Plat2);

    //end flag
    Sprite* Flag = createBlock(path, 120, 120, 5, 50.0, ENDFLAG);
    addChild(Flag);

    //jump box
    Sprite* JumpBox = createBlock(path, 300, 170, 20, 20, JUMPBOX);
    addChild(JumpBox);

    addChild(_sprite);



    this->scheduleUpdate();
    return true;
}

//path of the sprite, position X, position Y, Width, Height, Collision category
cocos2d::Sprite* Game::createBlock(char* SpritePath, float posX, float posY, float sizeX, float sizeY, int ColCat)
{
    cocos2d::Sprite* spriteBox = Sprite::create(SpritePath);
    spriteBox->setPosition(Vec2(posX, posY));
    cocos2d::PhysicsBody* Box = PhysicsBody::createBox(Size(sizeX, sizeY), PhysicsMaterial(0.0f, 0.0f, 0.0f));
    Box->setDynamic(false);
    Box->setCollisionBitmask(ColCat);
    Box->setContactTestBitmask(true);
    spriteBox->addComponent(Box);
    return spriteBox;
}



void Game::update(float dt) {

    _movement = SPEED * _moveDir;
    _sprite->setPositionX(_sprite->getPositionX() + _movement);
    _time -= dt;
    if (_time <= 0) {
        _time = 0;
        Director::getInstance()->popScene();
    }

}

//----------------------COLLISION MANAGEMENT-----------------------
bool Game::onContactBegin(cocos2d::PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();




    // check if the Player collide with wall
    if ((PLAYER == a->getCollisionBitmask() && WALL == b->getCollisionBitmask()) || (WALL == a->getCollisionBitmask() && PLAYER == b->getCollisionBitmask()))
    {
        //float posx = _sprite->getPositionX();
        log("COLLISION HAS OCCURED WITH A WALL");
        //stopAllActions();
        //_sprite->setPosition(posx, _sprite->getPositionY());
        _moveDir = _moveDir * -1;
    }
    // check if Player collide with Floor
    if ((PLAYER == a->getCollisionBitmask() && FLOOR == b->getCollisionBitmask()) || (FLOOR == a->getCollisionBitmask() && PLAYER == b->getCollisionBitmask()))
    {
        log("GROUNDED");
        _isGrounded = true;
    }
    // check if Player collide with End flag
    if ((PLAYER == a->getCollisionBitmask() && ENDFLAG == b->getCollisionBitmask()) || (ENDFLAG == a->getCollisionBitmask() && PLAYER == b->getCollisionBitmask()))
    {
        auto scene = GameOver::createScene();
        Director::getInstance()->replaceScene(scene);
        //Director::getInstance()->pushScene(scene);
        return true;
    }
    // check if PLAYER collide with jump box
    if (((PLAYER == a->getCollisionBitmask() && JUMPBOX == b->getCollisionBitmask()) || (JUMPBOX == a->getCollisionBitmask() && PLAYER == b->getCollisionBitmask())) && _isGrounded)
    {
        log("COLLISION HAS OCCURED WITH JUMP BOX");
        _spriteBody->applyImpulse(Vec2(0, _jump));
        b->getOwner()->removeFromParent();
    }
    else if (((PLAYER == a->getCollisionBitmask() && JUMPBOX == b->getCollisionBitmask()) || (JUMPBOX == a->getCollisionBitmask() && PLAYER == b->getCollisionBitmask())) && !_isGrounded)
    {
    }
    
}


void Game::onMouseUp(Event* event)
{
    // to illustrate the event....
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Up detected, Key: ";
    str += std::to_string((int)e->getMouseButton());
    //log(str.c_str());
}

void Game::onMouseMove(Event* event)
{
    // to illustrate the event....
    EventMouse* e = (EventMouse*)event;
    std::string str = "MousePosition X:";
    str = str + std::to_string((int)e->getCursorX()) + " Y:" + std::to_string((int)e->getCursorY());
    log(str.c_str());
}