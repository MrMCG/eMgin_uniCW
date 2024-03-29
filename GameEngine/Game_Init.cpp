#include "StdAfx.h"
#include "Game_Init.h"

CGame_Init::CGame_Init(void)
{
	// ------------------------- INIT SDL -------------------------
	csdl_setup = new CSDL_Setup();

	// ------------------------- INIT Resources -------------------------
	SDL_Renderer* renderer = csdl_setup->GetRenderer();
	resources = new CResources(renderer);

	// ------------------------- Add Textures -------------------------
	resources->AddTEX(renderer, "player.png"); // 1 = player sprite
	resources->AddTEX(renderer, "landscape.bmp"); // 2 = background
	resources->AddTEX(renderer, "bullet.png"); // 3 = bullet tex
	resources->AddTEX(renderer, "metalCrate.png"); // 4 = crate Tex
	resources->AddTEX(renderer, "sheetMetal.png"); // 5 = floor tex
	resources->AddTEX(renderer, "debug/tileSize.png"); // 6 = tile debug tex
	resources->AddTEX(renderer, "backdrop.png"); // 7 = writing backdrop 1
	resources->AddTEX(renderer, "enemy.png"); // 8 = enemy tex

	// ------------------------- Add Sounds -------------------------
	resources->AddSND("explosion.wav"); // 1 = explosion
	resources->AddSND("laser.wav"); // 2 = laser
	resources->AddSND("thruster.wav"); // 3 = thruster

	// ------------------------- Add Music -------------------------
	resources->AddMSC("level1.mp3"); // 1 = game music

	// ------------------------- Add Input listeners -------------------------
	input = NULL;
	input = new CInput();
	input->Add(new CKeyboard_Event(SDLK_w)); // 0
	input->Add(new CKeyboard_Event(SDLK_s)); // 1
	input->Add(new CKeyboard_Event(SDLK_a)); // 2
	input->Add(new CKeyboard_Event(SDLK_d)); // 3
	input->Add(new CKeyboard_Event(SDLK_ESCAPE)); // 4
	input->Add(new CKeyboard_Event(SDLK_r)); // 5
	input->Add(new CKeyboard_Event(SDLK_QUOTE)); // 6
	input->Add(new CKeyboard_Event(SDLK_SEMICOLON)); // 7
	input->Add(new CKeyboard_Event(SDLK_SPACE)); // 8
	input->Add(new CKeyboard_Event(SDLK_e), "e"); // 9

	// set level names/directories
	levels[0] = "level1/";
	levels[1] = "level2/";
	levels[2] = "level3/";
}

CGame_Init::~CGame_Init(void)
{
	delete csdl_setup;
	delete resources;
	delete input;
}

void CGame_Init::Run()
{
	resources->PlayMusic(1, -1); // start music
	int currentLevel = 0;
	while (csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{
		// load new game
		game = new CLevel(csdl_setup, resources, input, levels[currentLevel]);

		if (game->GameLoop()) // if player wins and continues
		{
			currentLevel++; // move to next level
			currentLevel %= LEVELS; // loop through levels
		}

		delete game; // delete previous game
	}
}
