#include "MenuScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* MenuScene::createScene() {
    return MenuScene::create();
}

bool MenuScene::init() {
    if (!Scene::init()) {
        return false;
    }

    //AudioEngine::play2d("musica para el juego buckshot roullete.mp3");

    // Crear el fondo
    auto background = Sprite::create("background_menu.png");

    // Obtener el tama�o de la pantalla y el tama�o de la imagen de fondo
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto bgSize = background->getContentSize();

    // Calcular la escala en funci�n del tama�o de la pantalla
    float scaleX = visibleSize.width / bgSize.width;
    float scaleY = visibleSize.height / bgSize.height;
    background->setScale(scaleX, scaleY);

    // Posicionar el fondo en el centro de la pantalla
    background->setPosition(visibleSize / 2);
    this->addChild(background, 0);

    // Crear el t�tulo del juego
    auto labelTitle = Label::createWithTTF("Buckshot Roulette", "fonts/CinzelDecorative-Regular.ttf", 50);
    labelTitle->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 150));
    this->addChild(labelTitle, 1);

    // Bot�n para jugar
    auto labelPlay = Label::createWithTTF("Jugar", "fonts/CinzelDecorative-Regular.ttf", 24);
    auto menuItemPlay = MenuItemLabel::create(labelPlay, CC_CALLBACK_1(MenuScene::menuPlayCallback, this));

    // Bot�n para volver al men� principal
    auto labelBack = Label::createWithTTF("Volver al men� principal", "fonts/CinzelDecorative-Regular.ttf", 24);
    auto menuItemBack = MenuItemLabel::create(labelBack, CC_CALLBACK_1(MenuScene::menuBackCallback, this));

    // Bot�n para salir completamente del juego
    auto labelExit = Label::createWithTTF("Salir del juego", "fonts/CinzelDecorative-Regular.ttf", 24);
    auto menuItemExit = MenuItemLabel::create(labelExit, CC_CALLBACK_1(MenuScene::menuExitGameCallback, this));

    // Crear el men� con los tres botones
    auto menu = Menu::create(menuItemPlay, menuItemBack, menuItemExit, nullptr);
    menu->alignItemsVerticallyWithPadding(10);
    this->addChild(menu, 1);

    return true;
}

// Funci�n para el bot�n de jugar
void MenuScene::menuPlayCallback(Ref* pSender) {
    auto scene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}

// Funci�n para volver al men� principal
void MenuScene::menuBackCallback(Ref* pSender) {
    auto scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}

// Funci�n para salir del juego
void MenuScene::menuExitGameCallback(Ref* pSender) {
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);  // Para dispositivos iOS
#endif
}
