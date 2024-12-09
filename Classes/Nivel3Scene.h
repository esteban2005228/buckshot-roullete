#ifndef __NIVEL3_SCENE_H__
#define __NIVEL3_SCENE_H__

#include "cocos2d.h"
#include <functional>

class Nivel3Scene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Nivel3Scene);

private:
    // Variables de vidas
    int playerLives = 7;
    int dealerLives = 7;

    // Métodos principales
    void handlePistolButton(cocos2d::Ref* sender);
    void handlePlayerTurn();
    void handleDealerTurn();
    void playAnimation(cocos2d::Vector<cocos2d::SpriteFrame*>& frames, std::function<void()> callback = nullptr);
    void loadAnimationFrames(const std::string& baseName, int startFrame, int endFrame, cocos2d::Vector<cocos2d::SpriteFrame*>& frames);
    bool determineBulletOutcome();
    void updateLivesIndicator();
    void checkGameOver();
    void playInitialAnimation();
    void playPistolGrabAnimation();
    void menuBackCallback(cocos2d::Ref* pSender);
};

#endif // __NIVEL3_SCENE_H__
