// LoadingScene.h
#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"

class LoadingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    // M�todo para pasar al men� principal despu�s de la carga
    void goToMenuScene(float dt); // M�todo que cambia a MenuScene

    CREATE_FUNC(LoadingScene);
};

#endif // __LOADING_SCENE_H__
