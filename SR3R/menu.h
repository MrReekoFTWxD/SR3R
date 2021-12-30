#pragma once

extern int currentScroll, pedIndex;
extern bool bBox, bSnap, bName, bParachute, bGoldenGun, bGodMode, bInfiSprint, bEvilCars, bEvilCars2, bMasc, bZomb, bNearestReticle;


class MenuItem
{
public:
	MenuItem() {}
	~MenuItem() {}

	MenuItem(Option* item)
	{
		Opt.emplace_back(item);
	}
};

void drawOptions();
