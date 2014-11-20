//
//  HelloWorldScene.cpp
//  BreakoutCocos2D-x
//
//  Created by Clawoo on 9/15/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//
#include "HelloWorldScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define PTM_RATIO 32

HelloWorld::~HelloWorld()
{
/*
    CC_SAFE_DELETE(_world);
    _groundBody = NULL;
    delete _contactListener;
*/
}
HelloWorld::HelloWorld()
{

}

bool HelloWorld::init()
{

//    setTouchEnabled(true);
    
	Size winSize = Director::getInstance()->getWinSize();
    
	// Define the gravity vector.
	b2Vec2 gravity;
	gravity.Set(0.0f,0.0f);
//	gravity.SetZero();
	
	// Do we want to let bodies sleep?
	bool doSleep = true;
    
	// Construct a world object, which will hold and simulate the rigid bodies.
//	_world = new b2World(gravity, doSleep);
	_world = new b2World(gravity);

	_world->SetAllowSleeping(doSleep);


//	m_debugDraw = new GLESDebugDraw (PTM_RATIO);
//	_world->SetDebugDraw(m_debugDraw);

    // Create edges around the entire screen
	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0); // bottom-left corner
	
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	_groundBody = _world->CreateBody(&groundBodyDef);
	
	// Define the ground box shape.
	b2PolygonShape groundBox;


//	Vect *lp;

	b2Vec2 lbp[4];

//	lp->add(Vec2());
	lbp[0].Set(0,0);

//	lbp->add(b2Vec2(0,0));
	lbp[1].Set(winSize.width/PTM_RATIO,0);


//	lbp->add(b2Vec2(winSize.width/PTM_RATIO,0));
	lbp[2].Set(winSize.width/PTM_RATIO,winSize.height/PTM_RATIO);

//	lbp->add(b2Vec2(winSize.width/PTM_RATIO,winSize.height/PTM_RATIO));
	lbp[3].Set(0,winSize.height/PTM_RATIO);

//	lbp->add(b2Vec2(0,winSize.height/PTM_RATIO));

	groundBox.Set(lbp,4);


	_bottomFixture = _groundBody->CreateFixture(&groundBox, 0);



	// bottom
//	groundBox.SetAsEdge(b2Vec2(0,0), b2Vec2(winSize.width/PTM_RATIO,0));
//	_bottomFixture = _groundBody->CreateFixture(&groundBox, 0);
	
	// top
//	groundBox.SetAsEdge(b2Vec2(0,winSize.height/PTM_RATIO), b2Vec2(winSize.width/PTM_RATIO,winSize.height/PTM_RATIO));
//	_groundBody->CreateFixture(&groundBox, 0);
	
	// left
//	groundBox.SetAsEdge(b2Vec2(0,winSize.height/PTM_RATIO), b2Vec2(0,0));
//	_groundBody->CreateFixture(&groundBox, 0);
	
	// right
//	groundBox.SetAsEdge(b2Vec2(winSize.width/PTM_RATIO,winSize.height/PTM_RATIO), b2Vec2(winSize.width/PTM_RATIO,0));
//	_groundBody->CreateFixture(&groundBox, 0);
    

    // Create sprite and add it to the layer
	Sprite *ball = Sprite::create("Ball.jpg");
//    ball->setPosition(ccp(100, 100));
	ball->setPosition(winSize.width/2,winSize.height/2);
    ball->setTag(1);
    this->addChild(ball);
    
    // Create ball body
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
//    ballBodyDef.position.Set(100/PTM_RATIO, 100/PTM_RATIO);
    ballBodyDef.position.Set(winSize.width/2/PTM_RATIO, winSize.height/2/PTM_RATIO);
    ballBodyDef.userData = ball;
    
    b2Body *ballBody = _world->CreateBody(&ballBodyDef);
    
    // Create circle shape
    b2CircleShape circle;
    circle.m_radius = 26.0/PTM_RATIO;
    
    // Create shape definition and add body
    b2FixtureDef ballShapeDef;
    ballShapeDef.shape = &circle;
    ballShapeDef.density = 1.0f;
    ballShapeDef.friction = 0.f;
    ballShapeDef.restitution = 1.0f;
    _ballFixture = ballBody->CreateFixture(&ballShapeDef);
    
    b2Vec2 force = b2Vec2(-10000, 0);
    ballBody->ApplyLinearImpulse(force, ballBodyDef.position,true);
//    ballBody->ApplyForce(force, ballBodyDef.position,true);

    
    Sprite *paddle = Sprite::create("Paddle.jpg");
    paddle->setPosition(ccp(winSize.width/2, winSize.height/10));
    this->addChild(paddle);
    
    // Create paddle body
    b2BodyDef paddleBodyDef;
    paddleBodyDef.type = b2_dynamicBody;
    paddleBodyDef.position.Set(winSize.width/2/PTM_RATIO, winSize.height/10/PTM_RATIO);
//    paddleBodyDef.type = b2_staticBody;
    paddleBodyDef.userData = paddle;
    _paddleBody = _world->CreateBody(&paddleBodyDef);
    
    // Create paddle shape
    b2PolygonShape paddleShape;
    paddleShape.SetAsBox(paddle->getContentSize().width/PTM_RATIO/2, 
                         paddle->getContentSize().height/PTM_RATIO/2);
    

    // Create shape definition and add to body
    b2FixtureDef paddleShapeDef;
    paddleShapeDef.shape = &paddleShape;
    paddleShapeDef.density = 10.0f;
    paddleShapeDef.friction = 0.4f;
    paddleShapeDef.restitution = 0.1f;
    _paddleFixture = _paddleBody->CreateFixture(&paddleShapeDef);
    
    // Restrict paddle along the x axis
    b2PrismaticJointDef jointDef;
    b2Vec2 worldAxis(1.0f, 0.0f);
    jointDef.collideConnected = true;
    jointDef.Initialize(_paddleBody, _groundBody, 
                        _paddleBody->GetWorldCenter(), worldAxis);
    _world->CreateJoint(&jointDef);

    // in C++ you need to initialize objects to NULL
    _mouseJoint = NULL;
    

    // Create contact listener
    _contactListener = new MyContactListener();
    _world->SetContactListener(_contactListener);
    

    for(int i = 0; i < 4; i++) {
        
//        static int padding=20;
        static int padding=winSize.width/20;
        
        // Create block and add it to the layer
        Sprite *block = Sprite::create("Block.jpg");
        int xOffset = winSize.width*((int) ((4-i)/4)) + padding+block->getContentSize().width/2+((block->getContentSize().width+padding)*i);
//        block->setPosition(ccp(xOffset, 250));
        block->setPosition(ccp(xOffset, winSize.height/3));
        block->setTag(2);
        this->addChild(block);
        
        // Create block body
        b2BodyDef blockBodyDef;
//        blockBodyDef.type = b2_dynamicBody;
        blockBodyDef.type = b2_staticBody;

        blockBodyDef.position.Set(xOffset/PTM_RATIO, winSize.height/3/PTM_RATIO);
        blockBodyDef.userData = block;
        b2Body *blockBody = _world->CreateBody(&blockBodyDef);
        
        // Create block shape
        b2PolygonShape blockShape;
        blockShape.SetAsBox(block->getContentSize().width/PTM_RATIO/2,
                            block->getContentSize().height/PTM_RATIO/2);
        
        // Create shape definition and add to body
        b2FixtureDef blockShapeDef;
        blockShapeDef.shape = &blockShape;
        blockShapeDef.density = 10.0;
        blockShapeDef.friction = 0.0;
        blockShapeDef.restitution = 0.1f;
        blockBody->CreateFixture(&blockShapeDef);
        
    }
    


/**/
    auto listener= EventListenerTouchAllAtOnce::create();

    listener->onTouchesBegan=CC_CALLBACK_2(HelloWorld::onTouchesBegan,this);
    listener->onTouchesMoved=CC_CALLBACK_2(HelloWorld::onTouchesMoved,this);
    listener->onTouchesEnded=CC_CALLBACK_2(HelloWorld::onTouchesCancelled,this);
    listener->onTouchesEnded=CC_CALLBACK_2(HelloWorld::onTouchesEnded,this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

/**/

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("background-music-aac.mp3");

//    this->schedule(schedule_selector(HelloWorld::tick));
    this->scheduleUpdate();



    return true;
}

/*
void HelloWorld::draw()
{

	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	//world->DrawDebugData();
	
	// restore default GL states
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);


	CCLayer::draw();
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
	kmGLPushMatrix();
	_world->DrawDebugData();
	kmGLPopMatrix();

}
*/

void HelloWorld::update(float dt)
{
	//It is recommended that a fixed time step is used with Box2D for stability
	//of the simulation, however, we are using a variable time step here.
	//You need to make an informed choice, the following URL is useful
	//http://gafferongames.com/game-physics/fix-your-timestep/
	
	int velocityIterations = 8;
	int positionIterations = 1;
    
	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	_world->Step(dt, velocityIterations, positionIterations);
//	_world->Step(dt,8,1);
	
    bool blockFound = false;
    
	//Iterate over the bodies in the physics world
	for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL) {
			//Synchronize the AtlasSprites position and rotation with the corresponding body
			Sprite* myActor = (Sprite*)b->GetUserData();
			myActor->setPosition(Vec2( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
			myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
            
            if (myActor->getTag() == 1) {
                static int maxSpeed = 10;
                
                b2Vec2 velocity = b->GetLinearVelocity();
                float32 speed = velocity.Length();
                
                if (speed > maxSpeed) {
                    b->SetLinearDamping(0.5);
                } else if (speed < maxSpeed) {
                    b->SetLinearDamping(0.0);
                }
                
            }
            
            if (myActor->getTag() == 2) {
                blockFound = true;
            }
		}	
	}
    
    std::vector<b2Body *>toDestroy;
    std::vector<MyContact>::iterator pos;
    for(pos = _contactListener->_contacts.begin(); 
        pos != _contactListener->_contacts.end(); ++pos) {
        MyContact contact = *pos;
        
        if ((contact.fixtureA == _bottomFixture && contact.fixtureB == _ballFixture) ||
            (contact.fixtureA == _ballFixture && contact.fixtureB == _bottomFixture)) {
            GameOverScene *gameOverScene = GameOverScene::create();
            gameOverScene->getLayer()->getLabel()->setString("You Lose! :[");
//            Director::getInstance()->replaceScene(gameOverScene);
        } 
        
        b2Body *bodyA = contact.fixtureA->GetBody();
        b2Body *bodyB = contact.fixtureB->GetBody();
        if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL) {
            Sprite *spriteA = (Sprite *) bodyA->GetUserData();
            Sprite *spriteB = (Sprite *) bodyB->GetUserData();
            
            // Sprite A = ball, Sprite B = Block
            if (spriteA->getTag() == 1 && spriteB->getTag() == 2) {
                if (std::find(toDestroy.begin(), toDestroy.end(), bodyB) 
                    == toDestroy.end()) {
                    toDestroy.push_back(bodyB);
                }
            }
            // Sprite B = block, Sprite A = ball
            else if (spriteA->getTag() == 2 && spriteB->getTag() == 1) {
                if (std::find(toDestroy.begin(), toDestroy.end(), bodyA) 
                    == toDestroy.end()) {
                    toDestroy.push_back(bodyA);
                }
            }        
        }                 
    }
    
    std::vector<b2Body *>::iterator pos2;
    for(pos2 = toDestroy.begin(); pos2 != toDestroy.end(); ++pos2) {
        b2Body *body = *pos2;     
        if (body->GetUserData() != NULL) {
            Sprite *sprite = (Sprite *) body->GetUserData();
            this->removeChild(sprite, true);
        }
        _world->DestroyBody(body);
    }
    
    if (!blockFound)
    {
        GameOverScene *gameOverScene = GameOverScene::create();
        gameOverScene->getLayer()->getLabel()->setString("You Win!");
        Director::getInstance()->replaceScene(gameOverScene);
    }
    
    if (toDestroy.size() > 0)
    {
        SimpleAudioEngine::getInstance()->playEffect("blip.mp3");
    }
}

void HelloWorld::onTouchesBegan(const std::vector<cocos2d::Touch *>& touches, cocos2d::Event *event)
{
    if (_mouseJoint != NULL) return;
    
//    Touch *myTouch = (Touch *)touches->anyObject();'
    Touch *myTouch = (Touch *) *touches.begin();

    Point location = myTouch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    b2Vec2 locationWorld = b2Vec2(location.x/PTM_RATIO, location.y/PTM_RATIO);
    
    if (_paddleFixture->TestPoint(locationWorld)) {
        b2MouseJointDef md;
        md.bodyA = _groundBody;
        md.bodyB = _paddleBody;
        md.target = locationWorld;
        md.collideConnected = true;
        md.maxForce = 1000.0f * _paddleBody->GetMass();
        
        _mouseJoint = (b2MouseJoint *)_world->CreateJoint(&md);
        _paddleBody->SetAwake(true);
    }
}

void HelloWorld::onTouchesMoved(const std::vector<cocos2d::Touch *>& touches, cocos2d::Event *event)
{
    if (_mouseJoint == NULL) return;
    
//    Touch *myTouch = (Touch *)touches->anyObject();
    Touch *myTouch = (Touch *) *touches.begin();

    Point location = myTouch->getLocationInView();
    location = Director::sharedDirector()->convertToGL(location);
    b2Vec2 locationWorld = b2Vec2(location.x/PTM_RATIO, location.y/PTM_RATIO);

    _mouseJoint->SetTarget(locationWorld);
}

void HelloWorld::onTouchesCancelled(const std::vector<cocos2d::Touch *>& touches, cocos2d::Event *event)
{
    if (_mouseJoint) 
    {
        _world->DestroyJoint(_mouseJoint);
        _mouseJoint = NULL;
    }
}

void HelloWorld::onTouchesEnded(const std::vector<cocos2d::Touch *>& touches, cocos2d::Event *event)
{
    if (_mouseJoint) 
    {
        _world->DestroyJoint(_mouseJoint);
        _mouseJoint = NULL;
    }  
}

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();

    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}
