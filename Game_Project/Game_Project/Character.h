#pragma once
#include <vector>
#include "CharacterSkill.h"
#include <raylib.h>
struct CharacterArt {
	std::vector<Texture2D> InGameModel;//Carousel animation while flying
	Texture2D Illustraion;
	Sound UltimateSound;
	Sound Hit;
	std::vector<Sound> VocieList;

};
struct Stats {
	int ap, hp, mp;
};

class Character
{
private:
	int cid;
	CharacterArt cArt;
	Stats cStats;
	CharacterSkill cSkill;
public:

};

