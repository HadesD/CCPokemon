//
//  PlayerLayer.h
//  MenuTutorial
//
//  Created by Denger on 14-2-12.
//
//

#ifndef __MenuTutorial__PlayerLayer__
#define __MenuTutorial__PlayerLayer__

#include "cocos2d.h"
#include "SceneManager.h"

USING_NS_CC;

class PlayLayer : public cocos2d::Layer
{
public:
    PlayLayer();
    ~PlayLayer();
    virtual bool init();
    void back(Object* pSender);

    CREATE_FUNC(PlayLayer);
};

#endif //* defined(__MenuTutorial__PlayerLayer__) */
