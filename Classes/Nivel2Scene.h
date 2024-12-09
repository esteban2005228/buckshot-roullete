#ifndef __NIVEL2_SCENE_H__
#define __NIVEL2_SCENE_H__

#include "cocos2d.h"
#include <functional>

class Nivel2Scene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Nivel2Scene);

private:
    // Variables de vidas
    int playerLives = 5;
    int dealerLives = 5;

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

#endif // __NIVEL2_SCENE_H__
