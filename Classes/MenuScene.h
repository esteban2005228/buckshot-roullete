#pragma once

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

class MenuScene : public cocos2d::Scene
{
public:
    // Método estático para crear la escena
    static cocos2d::Scene* createScene();

    // Inicialización de la escena
    virtual bool init();

    // Callback para comenzar el juego
    void menuPlayCallback(cocos2d::Ref* pSender);

    // Callback para regresar al menú
    void menuBackCallback(cocos2d::Ref* pSender);

    // Callback para salir del juego
    void menuExitGameCallback(cocos2d::Ref* pSender);

    // Implementar el método "create" manualmente
    CREATE_FUNC(MenuScene);
};
