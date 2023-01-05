#define SPEED 1.0
#include "Game.h"

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
    _sprite = Sprite::create("pokemon.png");
    _JumpSprite = Sprite::create("CloseSelected.png");
    _spriteBody = PhysicsBody::createBox(Size(85.0f, 120.0f), PhysicsMaterial(0.0f, 1.5f, 0.2f));
    _JumpBox = PhysicsBody::createBox(Size(50, 50), PhysicsMaterial(0.0f, 0.0f, 0.0f));
    _moveDir = -1;
    _jump = 450.0;
    _time = 30.0;
    _isJumping = false;
}

Game::~Game() {}

//path, posX, posY, sizeX, sizeY
auto Game::createWall(char* SpritePath, float posX, float posY, float sizeX, float sizeY)
{
    cocos2d::Sprite* spriteBox = Sprite::create(SpritePath);
    spriteBox->setPosition(Vec2(posX, posY));
    cocos2d::PhysicsBody* Box = PhysicsBody::createBox(Size(sizeX, sizeY), PhysicsMaterial(0.0f, 0.0f, 0.0f));
    Box->setDynamic(false);
    Box->setCollisionBitmask(2);
    Box->setContactTestBitmask(true);
    spriteBox->addComponent(Box);
    return spriteBox;
}

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



    if (_sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        //player
        _sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, 70));

        _spriteBody->setDynamic(true);
        _spriteBody->setVelocityLimit(100.0);
        _spriteBody->setPositionOffset(Size(0.0f, -5.0f));
        _spriteBody->setRotationEnable(false);
        _spriteBody->setCollisionBitmask(1);
        _spriteBody->setContactTestBitmask(true);
        _sprite->addComponent(_spriteBody);
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
    char* path2 = "Game.png";
    char* poke = "./img/pokemon.png";

    //walls
    auto Lwall = createWall(path2, origin.x, visibleSize.height / 2 + origin.y, 5.0, 320.0);
    auto Rwall = createWall(path2, visibleSize.width + origin.x, visibleSize.height / 2 + origin.y, 5.0, 320.0);
    addChild(Lwall);
    addChild(Rwall);

    //Floor
    cocos2d::Sprite* FloorSprite = Sprite::create(path);
    FloorSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, 0.0));
    cocos2d::PhysicsBody* FloorBox = PhysicsBody::createBox(Size(300.0, 5.0), PhysicsMaterial(1.0f, 0.1f, 1.0f));
    FloorBox->setDynamic(false);
    FloorBox->setCollisionBitmask(4);
    FloorBox->setContactTestBitmask(true);
    FloorSprite->addComponent(FloorBox);
    addChild(FloorSprite);

    //jump box test

    _JumpSprite->setPosition(Vec2(150, 30));
    _JumpBox->setDynamic(false);
    _JumpBox->setCollisionBitmask(3);
    _JumpBox->setContactTestBitmask(true);
    _JumpSprite->addComponent(_JumpBox);
    addChild(_JumpSprite);

    this->addChild(_sprite);



    this->scheduleUpdate();
    return true;
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

bool Game::onContactBegin(cocos2d::PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();

    // check if the bodies have collided
    if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        //float posx = _sprite->getPositionX();
        log("COLLISION HAS OCCURED WITH A WALL");
        //stopAllActions();
        //_sprite->setPosition(posx, _sprite->getPositionY());
        _moveDir = _moveDir * -1;
    }
    if (((1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask()) || (3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask())) && _isGrounded)
    {

        log("COLLISION HAS OCCURED WITH JUMP BOX");
        _spriteBody->applyImpulse(Vec2(0, _jump));
        _JumpSprite->removeFromParent();

    }
    else if (((1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask()) || (3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask())) && !_isGrounded)
    {
    }

    if ((1 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask()) || (4 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {

        log("GROUNDED");
        _isGrounded = true;

    }

    return true;
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
    //log(str.c_str());
}