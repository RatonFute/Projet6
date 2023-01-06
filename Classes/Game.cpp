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

    MapColl();
    ActionMenu();

    if (_sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        for (int i = 0; i < 3; i++) {
            _sprite = Sprite::create("CloseSelected.png");
            _sprite->setPosition(Vec2(50, 250));
            _spriteBody = PhysicsBody::createBox(Size(20.0f, 20.0f), PhysicsMaterial(0.0f, 1.5f, 0.2f));
            _spriteBody->setDynamic(true);
            _spriteBody->setVelocityLimit(110);
            _spriteBody->setRotationEnable(false);
            _spriteBody->setCollisionBitmask(1);
            _spriteBody->setContactTestBitmask(true);
            _sprite->addComponent(_spriteBody);
        }
        //player
    }

    //collision listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Game::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    char* path = "CloseSelected.png";
    //char* path2 = "CloseSelected.png";
    //char* poke = "CloseSelected.png";

    //----------------SPRITES----------------
    
//    //walls
    Sprite* Lwall = createBlock(path, origin.x, visibleSize.height / 2 + origin.y, 5.0, 320.0, WALL);
    Sprite* Rwall = createBlock(path, visibleSize.width + origin.x, visibleSize.height / 2 + origin.y, 5.0, 320.0, WALL);
    Sprite* wallTopR = createBlock(path, 280, 180, 5.0, 50.0, WALL);
    addChild(Lwall);
    
    addChild(Rwall);
    //addChild(wallTopR);

    //end flag
    Sprite* Flag = createBlock(path, 200, 200, 5, 50.0, ENDFLAG);
    addChild(Flag);

//    //jump box
    //Sprite* JumpBox = createBlock(path, 300, 100, 20, 20, JUMPBOX);
    //addChild(JumpBox);

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

void Game::ActionMenu()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto menu_item_1 = MenuItemImage::create("pickaxe.png", "pickaxe.png", CC_CALLBACK_1(Game::Kamikaze, this));
    auto menu_item_2 = MenuItemImage::create("pickaxe.png", "pickaxe.png", CC_CALLBACK_1(Game::Kamikaze, this));
    auto menu_item_3 = MenuItemImage::create("explosion.png", "explosion2.png", CC_CALLBACK_1(Game::Kamikaze, this));
    auto menu_item_4 = MenuItemImage::create("explosion.png","explosion2.png", CC_CALLBACK_1(Game::Kamikaze, this));
    auto menu_item_5 = MenuItemImage::create("explosion.png","explosion2.png", CC_CALLBACK_1(Game::Kamikaze, this));

    auto* menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, menu_item_4, menu_item_5, NULL);
    menu->setPosition(Vec2(250, 57));
    menu->alignItemsHorizontally();
    this->addChild(menu);

}

void Game::Kamikaze(cocos2d::Ref* pSender)
{
}

void Game::Builder(cocos2d::Ref* pSender)
{
}

void Game::Jumper(cocos2d::Ref* pSender)
{
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
    if ((PLAYER == a->getCollisionBitmask() && FLOOR == b->getCollisionBitmask()) || (WALL == a->getCollisionBitmask() && PLAYER == b->getCollisionBitmask()))
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

void Game::MapColl()
{
    auto map = TMXTiledMap::create("Map.tmx");
    this->addChild(map);


    TMXObjectGroup* collisions_SOL = map->getObjectGroup("Collide");
    ValueVector& rectangle_array_SOL = collisions_SOL->getObjects();

    for (cocos2d::Value& rectangle_box_SOL : rectangle_array_SOL) {
        cocos2d::ValueMap rectangle_box_properties = rectangle_box_SOL.asValueMap();

        Node* node = Node::create();
        PhysicsBody* box = PhysicsBody::createEdgeBox(Size(rectangle_box_properties["width"].asInt(), rectangle_box_properties["height"].asInt()));
        box->setCollisionBitmask(3);
        box->setContactTestBitmask(true);

        node->setPhysicsBody(box);

        node->setPositionX(rectangle_box_properties["x"].asInt() + rectangle_box_properties["width"].asInt() / 2);
        node->setPositionY(rectangle_box_properties["y"].asInt() + rectangle_box_properties["height"].asInt() / 2);

        box->setGravityEnable(false);
        box->setDynamic(false);
        node->setVisible(false);
        this->addChild(node, 20);
    }
}
