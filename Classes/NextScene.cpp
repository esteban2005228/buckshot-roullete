#include "NextScene.h"
#include "HelloWorldScene.h"
#include "Nivel1.h" // Para redirigir a la escena nivel1
#include <iomanip>
#include <sstream>

USING_NS_CC;

Scene* NextScene::createScene()
{
    return NextScene::create();
}

bool NextScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Vector para almacenar los frames de la primera animación
    Vector<SpriteFrame*> firstAnimFrames;

    for (int i = 106; i <= 199; i++)
    {
        std::stringstream ss;
        ss << "scene" << std::setw(5) << std::setfill('0') << i << ".jpg";
        std::string frameName = ss.str();

        auto spriteFrame = SpriteFrame::create(frameName, Rect(0, 0, 1920, 1080));
        if (spriteFrame)
        {
            firstAnimFrames.pushBack(spriteFrame);
        }
        else
        {
            CCLOG("No se pudo cargar el frame: %s", frameName.c_str());
        }
    }

    if (firstAnimFrames.empty())
    {
        CCLOG("No se encontraron frames para la primera animación.");
        return false;
    }

    auto firstAnimation = Animation::createWithSpriteFrames(firstAnimFrames, 0.05f);
    auto firstAnimate = Animate::create(firstAnimation);

    // Crear y almacenar el sprite principal
    mainSprite = Sprite::createWithSpriteFrame(firstAnimFrames.front());
    mainSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    float scaleX = visibleSize.width / mainSprite->getContentSize().width;
    float scaleY = visibleSize.height / mainSprite->getContentSize().height;
    mainSprite->setScale(scaleX, scaleY);

    this->addChild(mainSprite);

    // Callback para ejecutar la segunda animación al finalizar la primera
    auto playSecondAnimation = CallFunc::create([this]() {
        Vector<SpriteFrame*> secondAnimFrames;

        for (int i = 200; i <= 250; i++)
        {
            std::stringstream ss;
            ss << "scene" << std::setw(5) << std::setfill('0') << i << ".jpg";
            std::string frameName = ss.str();

            auto spriteFrame = SpriteFrame::create(frameName, Rect(0, 0, 1920, 1080));
            if (spriteFrame)
            {
                secondAnimFrames.pushBack(spriteFrame);
            }
            else
            {
                CCLOG("No se pudo cargar el frame: %s", frameName.c_str());
            }
        }

        if (secondAnimFrames.empty())
        {
            CCLOG("No se encontraron frames para la segunda animación.");
            return;
        }

        auto secondAnimation = Animation::createWithSpriteFrames(secondAnimFrames, 0.05f);
        auto secondAnimate = Animate::create(secondAnimation);

        mainSprite->runAction(RepeatForever::create(secondAnimate));
        });

    auto sequence = Sequence::create(firstAnimate, playSecondAnimation, nullptr);
    mainSprite->runAction(sequence);

    // Crear el botón para reproducir otra animación
    auto anotherAnimationButton = MenuItemImage::create(
        "puertaInvisibleRecortadaa.png",
        "puertaInvisibleRecortadaa.png",
        CC_CALLBACK_1(NextScene::playAnotherAnimationCallback, this));

    if (anotherAnimationButton)
    {
        anotherAnimationButton->setScale(2.0f);
        anotherAnimationButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    }
    else
    {
        CCLOG("No se pudo cargar el botón de otra animación.");
    }

    // Crear el botón de regreso
    auto backButton = MenuItemImage::create(
        "back_button.png",
        "back_button_pressed.png",
        CC_CALLBACK_1(NextScene::menuBackCallback, this));

    if (backButton)
    {
        backButton->setScale(0.3f);
        backButton->setPosition(Vec2(origin.x + backButton->getContentSize().width * backButton->getScale() / 2,
            origin.y + visibleSize.height - backButton->getContentSize().height * backButton->getScale() / 2));
    }
    else
    {
        CCLOG("No se pudo cargar el botón de regreso.");
    }

    auto menu = Menu::create(backButton, anotherAnimationButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void NextScene::playAnotherAnimationCallback(Ref* pSender)
{
    CCLOG("Reproduciendo la tercera animación...");

    Vector<SpriteFrame*> anotherAnimFrames;

    for (int i = 111; i <= 202; i++)
    {
        std::stringstream ss;
        ss << "frame" << std::setw(5) << std::setfill('0') << i << ".jpg";
        std::string frameName = ss.str();

        auto spriteFrame = SpriteFrame::create(frameName, Rect(0, 0, 1920, 1080));
        if (spriteFrame)
        {
            anotherAnimFrames.pushBack(spriteFrame);
        }
    }

    if (anotherAnimFrames.empty())
    {
        CCLOG("No se encontraron frames para la nueva animación.");
        return;
    }

    auto anotherAnimation = Animation::createWithSpriteFrames(anotherAnimFrames, 0.05f);
    auto anotherAnimate = Animate::create(anotherAnimation);

    // Capturar el último frame antes de la transición
    auto lastFrame = anotherAnimFrames.back();

    // Callback para ir a nivel1 al finalizar la tercera animación
    auto goToNivel1 = CallFunc::create([lastFrame]() {
        auto nivel1Scene = Nivel1Scene::createSceneWithFrame(lastFrame); // Pasar el último frame
        Director::getInstance()->replaceScene(TransitionFade::create(1.0, nivel1Scene));
        });

    auto sequence = Sequence::create(anotherAnimate, goToNivel1, nullptr);

    if (mainSprite)
    {
        mainSprite->stopAllActions();
        mainSprite->runAction(sequence);
    }
}

void NextScene::menuBackCallback(Ref* pSender)
{
    auto helloWorldScene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, helloWorldScene));
}
