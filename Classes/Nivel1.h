#ifndef __NIVEL1_SCENE_H__
#define __NIVEL1_SCENE_H__

#include "cocos2d.h"

class Nivel1Scene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createSceneWithFrame(cocos2d::SpriteFrame* lastFrame);
    virtual bool init();

    CREATE_FUNC(Nivel1Scene);

private:
    void menuBackCallback(cocos2d::Ref* pSender);
};

#endif // __NIVEL1_SCENE_H__
