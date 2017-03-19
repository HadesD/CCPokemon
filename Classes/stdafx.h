#ifndef __STDAFX_H_CCPOKEMON__
#define __STDAFX_H_CCPOKEMON__

#include <iostream>
#include <SimpleAudioEngine.h>

#define COCOS2D_DEBUG 1

using namespace std;

extern std::string RES_DIR;

extern std::string RD_MAPS;

extern std::string RD_SOUNDS;
extern std::string RD_S_MUSICS;
extern std::string RD_S_EFFECTS;
extern std::string RD_S_THEMES;

extern std::string RD_CHARACTERS;
extern std::string RD_C_POKEMONS;
extern std::string RD_C_TRAINERS;

extern std::string RD_UI;
extern std::string RD_UI_FONTS;

enum SOUNDTYPE
{
	BACKGROUND,
	EFFECT,
};

extern void playSound(std::string filePath, SOUNDTYPE type, bool isLoop);

#endif