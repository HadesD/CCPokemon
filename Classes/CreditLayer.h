//
//  CreditLayer.h
//  MenuTutorial
//
//  Created by Denger on 14-2-12.
//
// Mới thêm lớp Credíts

#ifndef __MenuTutorial__CreditLayer__
#define __MenuTutorial__CreditLayer__

#include "cocos2d.h"
#include "SceneManager.h"

USING_NS_CC;

class CreditLayer : public cocos2d::Layer
{
public:
    CreditLayer();
    ~CreditLayer();
    virtual bool init();
    void back(Object* pSender);
    
    CREATE_FUNC(CreditLayer);
};


#endif //* defined(__MenuTutorial__CreditLayer__) */
