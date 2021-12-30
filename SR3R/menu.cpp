#include "pch.h"

int currentScroll = 1;
int optCount = 0;
int pedIndex = 0;
bool bBox, bSnap, bName, bParachute, bGoldenGun, bGodMode, bInfiSprint, bEvilCars, bEvilCars2, bMasc, bZomb, bNearestReticle;
bool menuOpen;

void blankFunction() {}

void giveCash(int amount)
{
	human_adjust_cash(player_local_player(), &amount, HUMAN_CASH_ADJUSTMENT_ACTIVITY_REWARD);
}
void createOptions()
{
	optCount = 0;

	MenuItem(new Option("ASGARD", optCount++, std::bind(blankFunction)));
	MenuItem(new Option("ESP BOX", optCount++, &bBox));
	MenuItem(new Option("ESP SNAPLINES", optCount++, &bSnap));
	MenuItem(new Option("ESP Nearest to Reticle", optCount++, &bNearestReticle));
	MenuItem(new Option("ESP NAMES", optCount++, &bName));
	MenuItem(new Option("Parachute Launch", optCount++, &bParachute));
	MenuItem(new Option("Golden Gun", optCount++, &bGoldenGun));
	MenuItem(new Option("God Mode", optCount++, &bGodMode));
	MenuItem(new Option("Infinite Sprint", optCount++, &bInfiSprint));
	MenuItem(new Option("Evil Cars", optCount++, &bEvilCars));
	MenuItem(new Option("Evil Cars2", optCount++, &bEvilCars2));
	MenuItem(new Option("Peds", optCount++, {"None", "Mascots", "Zombies"}, &pedIndex));
	MenuItem(new Option("Give $10000", optCount++, std::bind(giveCash, 1000000)));
	MenuItem(new Option("Take $10000", optCount++, std::bind(giveCash, -1000000)));
}

void drawOptions()
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
		menuOpen = !menuOpen;

	if (!menuOpen)
		return;

	createOptions();
	
	if (GetAsyncKeyState(VK_UP) & 1)
	{
		currentScroll--;
		if (currentScroll < 1)
			currentScroll = optCount - 1;
	}

	if (GetAsyncKeyState(VK_DOWN) & 1)
	{
		currentScroll++;
		if (currentScroll > optCount-1)
			currentScroll = 1;
	}

	if (!Opt[currentScroll]->comboIndex)
	{
		if (GetAsyncKeyState(VK_RIGHT) & 1)
			Opt[currentScroll]->action();
	}
	else
	{
		if (GetAsyncKeyState(VK_RIGHT) & 1)
		{
			if (2 > *Opt[currentScroll]->comboIndex)
				*Opt[currentScroll]->comboIndex += 1;
		}
		if (GetAsyncKeyState(VK_LEFT) & 1)
		{
			if (0 < *Opt[currentScroll]->comboIndex)
				*Opt[currentScroll]->comboIndex -= 1;
		}
	}

	BoundingBox(20, 20, 210, (optCount * 20), vec4_t(126, 66, 245, 1), 2);
	drawRect(20, 20, 210, (optCount * 20), vec4_t(0, 0, 0, 128)); //Background
	drawRect(20, 20, 210, 20, vec4_t(126, 66, 245, 1)); // Title Background
	drawRect(20, 21 + (currentScroll * 20), 210, 18, vec4_t(126, 66, 245, 180)); // Scrollbar

	for (auto items : Opt)
		items->Render();



	Opt.clear();
}

