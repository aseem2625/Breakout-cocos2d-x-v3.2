#ifndef _GAME_OVER_SCENE_H_
#define _GAME_OVER_SCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class GameOverLayer : public LayerColor
{
public:
    CREATE_FUNC(GameOverLayer);
    CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*, _label, Label);
	
    virtual ~GameOverLayer();
    bool init();
    void gameOverDone();
	
};

class GameOverScene : public Scene
{
public:
    CREATE_FUNC(GameOverScene);
    CC_SYNTHESIZE_READONLY(GameOverLayer*, _layer, Layer);

    ~GameOverScene();
    bool init();
};

#endif // _GAME_OVER_SCENE_H_
