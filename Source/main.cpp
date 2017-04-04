#include "SDL.h"
#include "Scene.h"
#undef main
#include <stdio.h>
#include <utility>
#include <algorithm>
#include <limits>
#include "Model.h"
#include "FlatShader.h"
#include "SmoothShader.h"

int main(int argc, char* argv[]) {

	SDL_Window *window;                    // Declare a pointer

	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

										// Create an application window with the following settings:
	window = SDL_CreateWindow(
		"A Software Renderer",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		1000,                               // width, in pixels
		600,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
		);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	Scene* myScene = new Scene(1000, 600);
	//myScene->cameraPosition = Maths::Vec3f(0.0f, 0.0f,-8.0f);
	myScene->cameraPosition = Maths::Vec3f(-4.f, 4.f, -6.f);
	myScene->cameraRotation = Maths::Vec3f(30.f, -45.f, 0.f);

	Model* monkeyModel = new Model("Assets/monkey.obj");
	SceneObject* monkey = new SceneObject(monkeyModel);
	FlatShader* monkeyShader = new FlatShader();
	monkey->shader = monkeyShader;
	monkey->scale = Maths::Vec3f(3.f, 3.f, 3.f);
	//myScene->AddObject(monkey);

	Model* fireHydrantModel = new Model("Assets/Chest.obj");
	SceneObject* fireHydrant = new SceneObject(fireHydrantModel);
	fireHydrant->shader = new SmoothShader();
	fireHydrant->position = Maths::Vec3f(0, 0, -2);
	fireHydrant->rotation = Maths::Vec3f(0, 5, 0);
	fireHydrant->scale = Maths::Vec3f(3, 3, 3);
	myScene->AddObject(fireHydrant);

	SDL_Texture* fullscreenTexture = SDL_CreateTextureFromSurface(renderer, myScene->Render());
	while (true)
	{
		SDL_Event test_event;
		while (SDL_PollEvent(&test_event))
		{
			switch (test_event.type)
			{
			case SDL_QUIT:
				SDL_DestroyWindow(window);
				SDL_Quit();
				return 0;
				break;
			default:
				break;
			}
		}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, fullscreenTexture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
	return 0;
}