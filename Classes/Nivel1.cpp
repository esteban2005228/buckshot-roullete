#include "Nivel1.h"
#include "GameplayScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* Nivel1Scene::createSceneWithFrame(SpriteFrame* lastFrame)
{
    auto scene = Nivel1Scene::create();

    if (lastFrame)
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        auto background = Sprite::createWithSpriteFrame(lastFrame);
        if (background)
        {
            background->setName("background");
            background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

            float scaleX = visibleSize.width / background->getContentSize().width;
            float scaleY = visibleSize.height / background->getContentSize().height;
            background->setScale(scaleX, scaleY);

            scene->addChild(background, -1);
        }
    }

    return scene;
}

bool Nivel1Scene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Botón para regresar
    auto backButton = MenuItemImage::create(
        "back_button.png",
        "back_button_pressed.png",
        CC_CALLBACK_1(Nivel1Scene::menuBackCallback, this));

    if (backButton)
    {
        backButton->setScale(0.3f);
        backButton->setPosition(Vec2(
            origin.x + backButton->getContentSize().width * backButton->getScale() / 2,
            origin.y + visibleSize.height - backButton->getContentSize().height * backButton->getScale() / 2));
    }

    auto menu = Menu::create(backButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // Crear un fondo opaco para las instrucciones
    auto instructionLayer = LayerColor::create(Color4B(0, 0, 0, 230), visibleSize.width, visibleSize.height / 2);
    instructionLayer->setPosition(Vec2(0, visibleSize.height / 4));
    this->addChild(instructionLayer, 2);

    // Agregar texto de las instrucciones
    auto instructions = Label::createWithSystemFont(
        "Instrucciones del Juego:\n\n"
        "- Elige correctamente a quién disparas; las balas pueden ser reales o falsas.\n"
        "- Tienes 3 vidas al igual que él; cuida tus vidas.\n"
        "- Sobrevive para ir al siguiente nivel y estar más cerca de tu libertad.\n\n"
        "¡Buena suerte!",
        "fonts/CinzelDecorative-Regular.ttf",
        24);

    instructions->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    instructions->setColor(Color3B::WHITE);
    instructions->setAlignment(TextHAlignment::CENTER);
    this->addChild(instructions, 3);

    // Crear un texto interactivo "Okay" para quitar las instrucciones
    auto okayLabel = Label::createWithSystemFont("Okay", "Arial", 28);
    auto okayButton = MenuItemLabel::create(okayLabel, [](Ref* sender) {
        // Cambiar a GameplayScene
        auto gameplayScene = GameplayScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, gameplayScene));
        });

    okayButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4));
    auto okayMenu = Menu::create(okayButton, nullptr);
    okayMenu->setPosition(Vec2::ZERO);
    this->addChild(okayMenu, 4);

    return true;
}

void Nivel1Scene::menuBackCallback(Ref* pSender)
{
    auto helloWorldScene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, helloWorldScene));
}
