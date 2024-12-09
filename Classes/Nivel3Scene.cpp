#include "Nivel3Scene.h"
#include "MenuScene.h"
#include "WinScene.h"
#include <iomanip>
#include <sstream>

USING_NS_CC;

Scene* Nivel3Scene::createScene()
{
    return Nivel3Scene::create();
}

bool Nivel3Scene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Fondo base
    auto background = Sprite::create("background.jpg");
    if (background)
    {
        background->setPosition(visibleSize / 2);
        float scaleX = visibleSize.width / background->getContentSize().width;
        float scaleY = visibleSize.height / background->getContentSize().height;
        background->setScale(scaleX, scaleY);
        this->addChild(background, -1);
    }

    // Botón para regresar al menú principal
    auto backButton = MenuItemImage::create(
        "back_button.png",
        "back_button_pressed.png",
        CC_CALLBACK_1(Nivel3Scene::menuBackCallback, this));

    if (backButton)
    {
        backButton->setScale(0.3f);
        backButton->setPosition(Vec2(origin.x + backButton->getContentSize().width * backButton->getScale() / 2,
            origin.y + visibleSize.height - backButton->getContentSize().height * backButton->getScale() / 2));
    }

    auto menuWithBackButton = Menu::create(backButton, nullptr);
    menuWithBackButton->setPosition(Vec2::ZERO);
    this->addChild(menuWithBackButton, 1);

    // Reproducir animación inicial
    playInitialAnimation();

    return true;
}

void Nivel3Scene::playInitialAnimation()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vector<SpriteFrame*> animFrames;

    for (int i = 1; i <= 125; i++)
    {
        std::stringstream ss;
        ss << "frames" << std::setw(5) << std::setfill('0') << i << ".jpg";
        auto sprite = Sprite::create(ss.str());
        if (sprite)
        {
            float scaleX = visibleSize.width / sprite->getContentSize().width;
            float scaleY = visibleSize.height / sprite->getContentSize().height;
            sprite->setScale(scaleX, scaleY);

            auto frame = sprite->getSpriteFrame();
            if (frame)
            {
                animFrames.pushBack(frame);
            }
        }
    }

    if (!animFrames.empty())
    {
        auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
        auto animate = Animate::create(animation);

        auto sprite = Sprite::createWithSpriteFrame(animFrames.front());
        sprite->setPosition(visibleSize / 2);

        float scaleX = visibleSize.width / sprite->getContentSize().width;
        float scaleY = visibleSize.height / sprite->getContentSize().height;
        sprite->setScale(scaleX, scaleY);

        this->addChild(sprite, 2);
        sprite->runAction(Sequence::create(
            animate,
            CallFunc::create([this]() {
                // Mostrar botón para iniciar la animación de pistolGrab
                auto pistolButton = MenuItemImage::create(
                    "puertaInvisibleRecortadaa.png",
                    "puertaInvisibleRecortadaa.png",
                    CC_CALLBACK_1(Nivel3Scene::handlePistolButton, this));
                pistolButton->setScale(0.2f);
                pistolButton->setPosition(Director::getInstance()->getVisibleSize() / 2);

                auto pistolMenu = Menu::create(pistolButton, nullptr);
                pistolMenu->setPosition(Vec2::ZERO);
                this->addChild(pistolMenu, 3);
                }),
            nullptr));
    }
}

void Nivel3Scene::handlePistolButton(Ref* sender)
{
    auto button = static_cast<Node*>(sender);
    if (button && button->getParent())
    {
        button->removeFromParent();
    }

    playPistolGrabAnimation();
}

void Nivel3Scene::playPistolGrabAnimation()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vector<SpriteFrame*> pistolFrames;

    // Cargar frames de pistolGrab
    for (int i = 33; i <= 55; i++)
    {
        std::stringstream ss;
        ss << "pistolGrab" << std::setw(5) << std::setfill('0') << i << ".jpg";
        auto sprite = Sprite::create(ss.str());
        if (sprite)
        {
            float scaleX = visibleSize.width / sprite->getContentSize().width;
            float scaleY = visibleSize.height / sprite->getContentSize().height;
            sprite->setScale(scaleX, scaleY);

            auto frame = sprite->getSpriteFrame();
            if (frame)
            {
                pistolFrames.pushBack(frame);
            }
        }
    }

    if (!pistolFrames.empty())
    {
        auto pistolAnimation = Animation::createWithSpriteFrames(pistolFrames, 0.1f);
        auto pistolAnimate = Animate::create(pistolAnimation);

        auto pistolSprite = Sprite::createWithSpriteFrame(pistolFrames.front());
        pistolSprite->setPosition(visibleSize / 2);

        float scaleX = visibleSize.width / pistolSprite->getContentSize().width;
        float scaleY = visibleSize.height / pistolSprite->getContentSize().height;
        pistolSprite->setScale(scaleX, scaleY);

        this->addChild(pistolSprite, 2);
        pistolSprite->runAction(Sequence::create(
            pistolAnimate,
            CallFunc::create([this]() {
                handlePlayerTurn();
                }),
            nullptr));
    }
}

void Nivel3Scene::handlePlayerTurn()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto dealerChoice = Sprite::create("dealer_choice.png");
    auto selfChoice = Sprite::create("self_choice.png");

    if (dealerChoice)
    {
        dealerChoice->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200));
        dealerChoice->setScale(0.1f);
        this->addChild(dealerChoice, 3);

        auto dealerListener = EventListenerTouchOneByOne::create();
        dealerListener->onTouchBegan = [this, dealerChoice](Touch* touch, Event* event) {
            if (dealerChoice->getBoundingBox().containsPoint(touch->getLocation()))
            {
                dealerChoice->removeFromParent();
                Vector<SpriteFrame*> animFrames;

                bool isRealBullet = determineBulletOutcome();
                if (isRealBullet)
                {
                    dealerLives--;
                    loadAnimationFrames(dealerLives == 0 ? "matasADealer" : "disparoADealerReal", 1, dealerLives == 0 ? 146 : 108, animFrames);
                }
                else
                {
                    loadAnimationFrames("disparoADealerFalso", 1, 132, animFrames);
                }

                playAnimation(animFrames, [this]() {
                    handleDealerTurn();
                    });

                return true;
            }
            return false;
            };
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(dealerListener, dealerChoice);
    }

    if (selfChoice)
    {
        selfChoice->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 200));
        selfChoice->setScale(0.1f);
        this->addChild(selfChoice, 3);

        auto selfListener = EventListenerTouchOneByOne::create();
        selfListener->onTouchBegan = [this, selfChoice](Touch* touch, Event* event) {
            if (selfChoice->getBoundingBox().containsPoint(touch->getLocation()))
            {
                selfChoice->removeFromParent();
                Vector<SpriteFrame*> animFrames;

                bool isRealBullet = determineBulletOutcome();
                if (isRealBullet)
                {
                    playerLives--;
                    loadAnimationFrames(playerLives == 0 ? "dealerTeMata" : "suicidio", 1, playerLives == 0 ? 245 : 104, animFrames);

                    playAnimation(animFrames, [this]() {
                        if (playerLives == 0)
                        {
                            auto menuScene = MenuScene::createScene();
                            Director::getInstance()->replaceScene(TransitionFade::create(1.0, menuScene));
                        }
                        else
                        {
                            handleDealerTurn();
                        }
                        });
                }
                else
                {
                    loadAnimationFrames("suicidioFalso", 1, 166, animFrames);
                }

                playAnimation(animFrames, [this]() {
                    handleDealerTurn();
                    });

                return true;
            }
            return false;
            };
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(selfListener, selfChoice);
    }
}

void Nivel3Scene::handleDealerTurn()
{
    Vector<SpriteFrame*> animFrames;

    bool isRealBullet = determineBulletOutcome();
    if (isRealBullet)
    {
        playerLives--;
        loadAnimationFrames(playerLives == 0 ? "dealerTeMata" : "dealerTeDispara", 1, playerLives == 0 ? 245 : 107, animFrames);

        playAnimation(animFrames, [this]() {
            if (playerLives == 0)
            {
                auto menuScene = MenuScene::createScene();
                Director::getInstance()->replaceScene(TransitionFade::create(1.0, menuScene));
            }
            else
            {
                handlePlayerTurn();
            }
            });
    }
    else
    {
        loadAnimationFrames("dealerTeDisparaFalso", 1, 125, animFrames);

        playAnimation(animFrames, [this]() {
            handlePlayerTurn();
            });
    }
}


void Nivel3Scene::checkGameOver()
{
    if (playerLives == 0)
    {
        auto menuScene = MenuScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0, menuScene));
    }
    else if (dealerLives == 0)
    {
        auto WinScene = WinScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0, WinScene));
    }
}


void Nivel3Scene::playAnimation(Vector<SpriteFrame*>& frames, std::function<void()> callback)
{
    if (!frames.empty())
    {
        auto animation = Animation::createWithSpriteFrames(frames, 0.1f);
        auto animate = Animate::create(animation);

        auto sprite = Sprite::createWithSpriteFrame(frames.front());
        sprite->setPosition(Director::getInstance()->getVisibleSize() / 2);
        sprite->setScale(Director::getInstance()->getVisibleSize().width / sprite->getContentSize().width);

        this->addChild(sprite, 3);

        if (callback)
        {
            sprite->runAction(Sequence::create(animate, CallFunc::create(callback), RemoveSelf::create(), nullptr));
        }
        else
        {
            sprite->runAction(Sequence::create(animate, RemoveSelf::create(), nullptr));
        }
    }
}

bool Nivel3Scene::determineBulletOutcome()
{
    return CCRANDOM_0_1() > 0.5f;
}

void Nivel3Scene::loadAnimationFrames(const std::string& baseName, int startFrame, int endFrame, Vector<SpriteFrame*>& frames)
{
    for (int i = startFrame; i <= endFrame; i++)
    {
        std::stringstream ss;
        ss << baseName << std::setw(5) << std::setfill('0') << i << ".jpg";
        auto sprite = Sprite::create(ss.str());
        if (sprite)
        {
            auto frame = sprite->getSpriteFrame();
            if (frame)
            {
                frames.pushBack(frame);
            }
        }
    }
}

void Nivel3Scene::menuBackCallback(cocos2d::Ref* pSender)
{
    auto menuScene = MenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, menuScene));
}
