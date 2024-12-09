#ifndef __HELLO_WORLD_SCENE_H__
#define __HELLO_WORLD_SCENE_H__

#include "cocos2d.h"

// Asegúrate de que esta clase se llama exactamente igual que el archivo
class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    // Declaración del método onSpriteButtonPressed para el botón sprite
    void onSpriteButtonPressed(cocos2d::Ref* pSender);

    // Otros métodos
    void menuBackCallback(cocos2d::Ref* pSender);
    void startAnimation();

    CREATE_FUNC(HelloWorld);
};

#endif // __HELLO_WORLD_SCENE_H__
