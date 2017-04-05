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

	SDL_Window *window;

	SDL_Init(SDL_INIT_VIDEO);

	// Create an application window
	window = SDL_CreateWindow(
		"A Software Renderer",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1000,
		600,
		SDL_WINDOW_OPENGL
		);

	// Check that the window was successfully created
	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	// We're using a basic SDL renderer to put our framebuffer on the screen
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


	// Create a scene and set the camera up
	Scene* myScene = new Scene(1000, 600);
	myScene->cameraPosition = vec3(4.f, 4.f, -6.f);
	myScene->cameraRotation = vec3(30.f, 45.f, 0.f);

	// Make a monkey object, loading it's model and creating a shader for it.
	Model* monkeyModel = new Model("Assets/monkey.obj");
	SceneObject* monkey = new SceneObject(monkeyModel);
	FlatShader* monkeyShader = new FlatShader();
	monkey->shader = monkeyShader;
	monkey->scale = vec3(3.f, 3.f, 3.f);
	//myScene->AddObject(monkey);

	Model* fireHydrantModel = new Model("Assets/Chest.obj");
	SceneObject* fireHydrant = new SceneObject(fireHydrantModel);
	fireHydrant->shader = new FlatShader();
	fireHydrant->position = vec3(0, 0, 0);
	fireHydrant->rotation = vec3(0, 5, 0);
	fireHydrant->scale = vec3(3, 3, 3);
	myScene->AddObject(fireHydrant);

	// Render the scene and make a fullscreen texture from it that we can put on the screen.
	SDL_Texture* fullscreenTexture = SDL_CreateTextureFromSurface(renderer, myScene->Render());
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, fullscreenTexture, NULL, NULL);
	SDL_RenderPresent(renderer);

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
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}