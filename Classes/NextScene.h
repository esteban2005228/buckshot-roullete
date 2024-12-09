#ifndef __NEXT_SCENE_H__
#define __NEXT_SCENE_H__

#include "cocos2d.h"

class NextScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    // Callback para reproducir otra animación
    void playAnotherAnimationCallback(cocos2d::Ref* pSender);

    // Callback para regresar al menú
    void menuBackCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(NextScene);

private:
    cocos2d::Sprite* mainSprite;  // Referencia al sprite principal
};

#endif // __NEXT_SCENE_H__
