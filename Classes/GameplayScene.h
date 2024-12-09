#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include "cocos2d.h"
#include <functional>

class GameplayScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameplayScene);

private:
    // Variables de vidas
    int playerLives = 3;
    int dealerLives = 3;

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

#endif // __GAMEPLAY_SCENE_H__
