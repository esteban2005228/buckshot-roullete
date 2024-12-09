#include "WinScene.h"
#include "MenuScene.h"

USING_NS_CC;

Scene* WinScene::createScene()
{
    return WinScene::create();
}

bool WinScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Fondo de la escena
    auto background = LayerColor::create(Color4B(0, 0, 0, 255)); // Fondo negro
    this->addChild(background, -1);

    // Texto "Ganaste"
    auto label = Label::createWithTTF("¡Ganaste!", "fonts/Marker Felt.ttf", 48);
    if (label)
    {
        label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
        label->setColor(Color3B::WHITE); // Texto blanco
        this->addChild(label, 1);
    }

    // Botón para regresar al menú principal
    auto menuButton = MenuItemImage::create(
        "menu_button.png",    // Imagen normal
        "menu_button_pressed.png", // Imagen presionada
        [](Ref* sender) {
            auto menuScene = MenuScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1.0, menuScene));
        });

    if (menuButton)
    {
        menuButton->setScale(0.5f);
        menuButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));
    }

    auto menu = Menu::create(menuButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}
