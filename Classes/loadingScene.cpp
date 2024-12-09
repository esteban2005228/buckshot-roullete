#include "LoadingScene.h"
#include "MenuScene.h"
#include "cocos2d.h"

USING_NS_CC;

Scene* LoadingScene::createScene() {
    return LoadingScene::create();
}

bool LoadingScene::init() {
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Crear un fondo para la pantalla de carga
    auto background = Sprite::create("loading_background.png"); // Asegúrate de tener esta imagen en Resources
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    background->setContentSize(Size(visibleSize.width, visibleSize.height));
    this->addChild(background);

   

    // Programar el cambio a la escena de menú después de 3 segundos
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(LoadingScene::goToMenuScene), 3.0f);

    return true;
}

void LoadingScene::goToMenuScene(float dt) {
    // Cambiar a la escena de menú
    auto scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}
