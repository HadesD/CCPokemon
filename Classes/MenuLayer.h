//
//  MenuLayer.h
//  MenuTutorial
//
//  Created by Denger on 14-2-12.
//
//

#ifndef __MenuTutorial__MenuLayer__
#define __MenuTutorial__MenuLayer__

#include "stdafx.h"
#include "cocos2d.h"

USING_NS_CC;

class MenuLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    
	void onNewGame(Ref* pSender);
	void onCredits(Ref* pSender);
    
    
    CREATE_FUNC(MenuLayer);
};

#endif //* defined(__MenuTutorial__MenuLayer__) */
