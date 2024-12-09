#include "HelloWorldScene.h"
#include "MenuScene.h"
#include "NextScene.h"  // Asegúrate de que este archivo esté incluido
#include <sstream>
#include <iomanip>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}

bool HelloWorld::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Botón de regreso al menú
    auto backButton = MenuItemImage::create(
        "back_button.png",
        "back_button_pressed.png",
        CC_CALLBACK_1(HelloWorld::menuBackCallback, this));

    if (backButton == nullptr ||
        backButton->getContentSize().width <= 0 || backButton->getContentSize().height <= 0)
    {
        problemLoading("'back_button.png'");
    }
    else
    {
        backButton->setScale(0.3f);
        backButton->setPosition(Vec2(origin.x + backButton->getContentSize().width * backButton->getScale() / 2,
            origin.y + visibleSize.height - backButton->getContentSize().height * backButton->getScale() / 2));
    }

    auto menuWithBackButton = Menu::create(backButton, nullptr);
    menuWithBackButton->setPosition(Vec2::ZERO);
    this->addChild(menuWithBackButton, 1);

    // Crear el sprite del botón que cambia a la siguiente escena
    auto spriteButton = MenuItemSprite::create(
        Sprite::create("puertaInvisibleRecortadaa.png"),
        Sprite::create("puertaInvisibleRecortadaa.png"),
        CC_CALLBACK_1(HelloWorld::onSpriteButtonPressed, this));  // Cambia a NextScene

    if (spriteButton == nullptr)
    {
        problemLoading("'puertaInvisibleRecortadaa.png'");
    }
    else
    {
        spriteButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4));
        spriteButton->setScale(0.5f);
    }

    auto menuWithSpriteButton = Menu::create(spriteButton, nullptr);
    menuWithSpriteButton->setPosition(Vec2::ZERO);
    this->addChild(menuWithSpriteButton, 1);

    // Iniciar la animación
    this->startAnimation();

    return true;
}

void HelloWorld::startAnimation()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vector<SpriteFrame*> animFrames;
    for (int i = 1; i <= 100; i++)
    {
        std::stringstream ss;
        ss << "scene" << std::setw(5) << std::setfill('0') << i << ".jpg";
        std::string frameName = ss.str();

        auto sprite = Sprite::create(frameName);
        if (sprite)
        {
            float scaleX = visibleSize.width / sprite->getContentSize().width;
            float scaleY = visibleSize.height / sprite->getContentSize().height;
            sprite->setScale(scaleX, scaleY);

            auto frame = sprite->getSpriteFrame();
            animFrames.pushBack(frame);
        }
    }

    if (animFrames.empty())
    {
        CCLOG("No se pudieron cargar los frames para la animación.");
        return;
    }

    auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    auto animate = Animate::create(animation);

    auto sprite = Sprite::createWithSpriteFrame(animFrames.front());
    sprite->setPosition(visibleSize / 2);
    float scaleX = visibleSize.width / sprite->getContentSize().width;
    float scaleY = visibleSize.height / sprite->getContentSize().height;
    sprite->setScale(scaleX, scaleY);

    this->addChild(sprite);

    sprite->runAction(RepeatForever::create(animate));
}

void HelloWorld::menuBackCallback(Ref* pSender)
{
    auto menuScene = MenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, menuScene));
}

// Callback para el sprite botón que cambia de escena
void HelloWorld::onSpriteButtonPressed(Ref* pSender)
{
    // Cambiar a la siguiente escena
    auto nextScene = NextScene::createScene();  // Asegúrate de que esta clase esté bien definida
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, nextScene));
}
