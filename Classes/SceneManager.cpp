//
//  SceneManager.cpp
//  MenuTutorial
//
//  Created by Denger on 14-2-12.
//
//

#include "SceneManager.h"
#include "PlayLayer.h"
#include "CreditLayer.h"

USING_NS_CC;

#define TRANSITION_DURATION (1.2f)

class FadeWhiteTransition : public TransitionFade
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFade::create(t, s, Color3B::WHITE);
    }
};

class FlipXRightOver : public TransitionFlipX
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFlipX::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
    }
};

class FlipYUpOver : public TransitionFlipY
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFlipY::create(t, s, TransitionScene::Orientation::UP_OVER);
    }
};

class ZoomFlipXLeftOver : public TransitionZoomFlipX
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionZoomFlipX::create(t, s, TransitionScene::Orientation::LEFT_OVER);
    }
};

class PageTransitionForward : public TransitionPageTurn
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        Director::getInstance()->setDepthTest(true);
        return TransitionPageTurn::create(t, s, false);
    }
};

class PageTransitionBackward : public TransitionPageTurn
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        Director::getInstance()->setDepthTest(true);
        return TransitionPageTurn::create(t, s, true);
    }
};

#define STRINGIFY(x) #x

#define TRANS(__className__) {                                      \
    [](float t, Scene* s){ return __className__::create(t,s);},     \
        STRINGIFY(__className__),                                   \
}
struct _transitions {
    std::function<TransitionScene*(float t, Scene* s)> function;
    const char * name;
} transitions[] = {
    TRANS(PageTransitionForward),
    TRANS(PageTransitionBackward),
    TRANS(FadeWhiteTransition),
    TRANS(ZoomFlipXLeftOver),
    TRANS(FlipXRightOver),
    TRANS(FlipYUpOver)
};


#define MAX_LAYER (sizeof(transitions) / sizeof(transitions[0]))


static int s_nSceneIdx = 0;

TransitionScene* createTransition(int index, float t, Scene* s)
{

    Director::getInstance()->setDepthTest(false);

    return transitions[index].function(t,s);
}


void SceneManager::goMenu()
{
    Layer *layer = MenuLayer::create();
    SceneManager::go(layer);
}

void SceneManager::goPlay()
{
    Layer *layer = PlayLayer::create();
    SceneManager::go(layer);
}

void SceneManager::goCredit()
{
    Layer *layer = CreditLayer::create();
    SceneManager::go(layer);
}

void SceneManager::go(Layer* layer)
{
    Director *director = Director::getInstance();
    Scene *newScene = SceneManager::wrap(layer);
    
    if ( director->getRunningScene() )
    {
        //director->replaceScene(TransitionFade::create(1.2f, newScene, Color3B::WHITE));
        s_nSceneIdx++;
        s_nSceneIdx = s_nSceneIdx % MAX_LAYER;
        Director::getInstance()->replaceScene(
                            createTransition(s_nSceneIdx, TRANSITION_DURATION, newScene));
    }
    else
    {
        director->runWithScene(newScene);
    }
}

Scene* SceneManager::wrap(Layer *layer)
{
    Scene *newScene = Scene::create();
    newScene->addChild(layer);
    return newScene;
}
