//
//  SceneManager.h
//  MenuTutorial
//
//  Created by Denger on 14-2-12.
//
//

#ifndef __MenuTutorial__SceneManager__
#define __MenuTutorial__SceneManager__

#include "cocos2d.h"
#include "MenuLayer.h"

class SceneManager : public cocos2d::Object
{
public:
    SceneManager() {};
    ~SceneManager() {};
    
    static void goMenu();
    static void goPlay(); // Mới thêm
    static void goCredit(); // Mới thêm
private:
    static void go(cocos2d::Layer* layer);
    static cocos2d::Scene* wrap(cocos2d::Layer *layer);
};

#endif //* defined(__MenuTutorial__SceneManager__) */
