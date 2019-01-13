#pragma once
#include "Scene.h"
#include "Button.h"
#include"SDL_mixer.h"

class Menu : public Scene
{
	Button exitButton;
	Button rankingButton;
	Button playButton;
	Button soundButton;
	void loadTextures(Renderer* myRenderer);

public:
	Menu();
	~Menu();
	Mix_Music *arkanoid_Music;

	void Update(Controller* inputs);
	void Draw(Renderer* myRenderer);
};

