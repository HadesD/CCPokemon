#include "stdafx.h"

std::string RES_DIR = "res";

std::string RD_MAPS = RES_DIR + "/Maps";

std::string RD_SOUNDS = RES_DIR + "/Sounds";
std::string RD_S_MUSICS = RD_SOUNDS + "/Musics";
std::string RD_S_EFFECTS = RD_SOUNDS + "/Effects";
std::string RD_S_THEMES = RD_SOUNDS + "/Themes";

std::string RD_CHARACTERS = RES_DIR + "/Characters";
std::string RD_C_POKEMONS = RD_CHARACTERS + "/Pokemons";
std::string RD_C_TRAINERS = RD_CHARACTERS + "/Trainers";

std::string RD_UI = RES_DIR + "/UI";
std::string RD_UI_FONTS = RD_UI + "/Fonts";

std::string RD_PARTICLES = RES_DIR + "/Particles";

void playSound(std::string filePath, SOUNDTYPE type, bool isLoop)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

	if (type == SOUNDTYPE::BACKGROUND)
	{
		audio->playBackgroundMusic((const char*)(RD_S_THEMES + "/" + filePath).c_str(), isLoop);
	}
	else if (type == SOUNDTYPE::EFFECT)
	{
		audio->playEffect((const char*)(RD_S_EFFECTS + "/" + filePath).c_str(), isLoop);
	}
	else
	{
		audio->playBackgroundMusic(filePath.c_str(), isLoop);
	}

}