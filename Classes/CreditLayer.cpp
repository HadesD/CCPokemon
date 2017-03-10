//
//  CreditLayer.cpp
//  MenuTutorial
//
//  Created by Denger on 14-2-12.
//
//

#include "CreditLayer.h"

USING_NS_CC;

// Hàm tạo và hàm hủy
CreditLayer::CreditLayer()
{
}

CreditLayer::~CreditLayer()
{
}

bool CreditLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
	// Tạo 1 menu tên "Back"
	auto back = MenuItemFont::create("Back", CC_CALLBACK_1(CreditLayer::back,this));
	auto menu = Menu::create(back, NULL);
	menu->setPosition(visibleSize.width/2, visibleSize.height/2);
	this->addChild(menu);
	
	return true;
	
	/*
    auto back = MenuItemFont::create("back", CC_CALLBACK_1(CreditLayer::back, this));
    auto menu = Menu::create(back, NULL);
    menu->setPosition(visibleSize.width/2, visibleSize.height/2);
    this->addChild(menu);
    
    return true;
	
	*/
}


void CreditLayer::back(Object* pSender)
{
    SceneManager::goMenu();
}
