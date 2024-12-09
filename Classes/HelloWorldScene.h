#ifndef __HELLO_WORLD_SCENE_H__
#define __HELLO_WORLD_SCENE_H__

#include "cocos2d.h"

// Aseg�rate de que esta clase se llama exactamente igual que el archivo
class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    // Declaraci�n del m�todo onSpriteButtonPressed para el bot�n sprite
    void onSpriteButtonPressed(cocos2d::Ref* pSender);

    // Otros m�todos
    void menuBackCallback(cocos2d::Ref* pSender);
    void startAnimation();

    CREATE_FUNC(HelloWorld);
};

#endif // __HELLO_WORLD_SCENE_H__
