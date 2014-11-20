//
//  HelloWorldScene.h
//  BreakoutCocos2D-x
//
//  Created by Clawoo on 9/15/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//
#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__

#define COCOS2D_DEBUG 1

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"

#include "Box2D/Box2D.h"


//#include "Box2D.h"
//#include "external/Box2D/Box2D.h"

#include "MyContactListener.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"

#include "GLES-Render.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer {
public:
    ~HelloWorld();
    HelloWorld();
    // returns a Scene that contains the HelloWorld as the only child

    static cocos2d::Scene* createScene();
    virtual bool init();

//    virtual void draw();


    void onTouchesBegan(const std::vector<cocos2d::Touch *>& touches,Event *event);

    void onTouchesMoved(const std::vector<Touch *>& touches,Event *event);
    void onTouchesCancelled(const std::vector<Touch *>& touches,Event *event);
    void onTouchesEnded(const std::vector<Touch *>& touches,Event *event);

    void update(float dt);

    CREATE_FUNC(HelloWorld);
    
private:
    b2World* _world;
    b2Body *_groundBody;
    b2Fixture *_bottomFixture;
    b2Fixture *_ballFixture;
    b2Body *_paddleBody;
    b2Fixture *_paddleFixture;
    b2MouseJoint *_mouseJoint;
    
    MyContactListener *_contactListener;

//    GLESDebugDraw *m_debugDraw;
};

#endif // __HELLO_WORLD_H__
