#include "../inc/main.h"
#include <SDL2/SDL_audio.h>
#include <stdio.h>

/*const short MAP[MAP_GRID_HEIGHT][MAP_GRID_WIDTH] = {
	{R, R, R, R, R, R, R, R, R, R},
	{R, 0, 0, 0, 0, 0, 0, 0, 0, R},
	{R, 0, 0, G, G, G, G, G, 0, R},
	{R, 0, 0, G, 0, 0, 0, G, 0, R},
	{R, 0, 0, G, 0, G, 0, G, 0, R},
	{R, 0, 0, 0, 0, G, 0, G, 0, R},
	{R, 0, G, G, G, G, 0, G, 0, R},
	{R, 0, 0, 0,
		0, 0, 0, G, 0, R},
	{R, 0, 0, 0, 0, 0, 0, 0, 0, R},
	{R, R, R, R, R, R, R, R, R, R}
};*/

const short MAP[MAP_GRID_HEIGHT][MAP_GRID_WIDTH] =
{
  {R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,R},
  {R,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,R},
  {R,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,R},
  {R,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,R},
  {R,0,0,0,0,0,G,G,G,G,G,0,0,0,0,B,0,B,0,B,0,0,0,R},
  {R,0,0,0,0,0,G,0,0,0,G,0,0,0,0,0,0,0,0,0,0,0,0,R},
  {R,0,0,0,0,0,G,0,0,0,G,0,0,0,0,B,0,0,0,B,0,0,0,R},
  {R,0,0,0,0,0,G,0,0,0,G,0,0,0,0,0,0,0,0,0,0,0,0,R},
  {R,0,0,0,0,0,G,G,0,G,G,0,0,0,0,B,0,B,0,B,0,0,0,R},
  {R,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,R},
  {R,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,R},
  {R,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,R},
  {R,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,R},
  {R,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,R},
  {R,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,R},
  {R,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,R},
  {R,G,G,G,G,G,G,G,G,0,0,0,0,0,0,0,0,0,0,0,0,0,0,R},
  {R,G,0,G,0,0,0,0,G,0,0,0,0,0,0,0,0,0,0,0,0,0,0,R},
  {R,G,0,0,0,0,B,0,G,0,0,0,0,0,0,0,0,0,0,0,0,0,0,R},
  {R,G,0,G,0,0,0,0,G,0,0,0,0,0,0,0,0,0,0,0,0,0,0,R},
  {R,G,0,G,G,G,G,G,G,0,0,0,0,0,0,0,0,0,0,0,0,0,0,R},
  {R,G,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,R},
  {R,G,G,G,G,G,G,G,G,0,0,0,0,0,0,0,0,0,0,0,0,0,0,R},
  {R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,R}
};


/**
 * render - rendering function
 * Return: Nothing
 */
void render(gameData *gameData)
{
	if (gameData->showMap)
	{
		clearRenderer();
		renderOverheadMap(gameData);
	} else
	{
		/* Draw projected scene */
		renderProjectedScene(gameData);
	}
}


int setupWindow(gameData *gameData) {
    int x, y;

    if(!initGFX("A 3D Raycasting Maze Adventure",
				WINDOW_WIDTH, WINDOW_HEIGHT))
	{
		return (FALSE);
	}

    gameData->screenBuffer = createTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
    gameData->redXorTexture = generateRedXorTexture(TEXTURE_SIZE);
    gameData->greenXorTexture = generateGreenXorTexture(TEXTURE_SIZE);
    gameData->blueXorTexture = generateBlueXorTexture(TEXTURE_SIZE);
    gameData->grayXorTexture = generateGrayXorTexture(TEXTURE_SIZE);
    gameData->TEXTURES[0] = gameData->redXorTexture;
    gameData->TEXTURES[R] = gameData->greenXorTexture;
    gameData->TEXTURES[2] = gameData->blueXorTexture;
    gameData->TEXTURES[3] = gameData->grayXorTexture;

    if(!gameData->screenBuffer)
		return (FALSE);

    /* Make the texture initially gray */
    for(x = 0; x < WINDOW_WIDTH; x++)
        for(y = 0; y < WINDOW_HEIGHT; y++)
            gameData->screenBuffer[(WINDOW_WIDTH * y) + x] = 0xFFAAAAAA;

    return (TRUE);
}

void initAudio(AudioData *audioData)
{
	audioData->audioBuffer = NULL;
    audioData->audioLength = 0;
    audioData->rw = NULL;

	if (!initSDLAudio(audioData))
	{
		fprintf(stderr, "failed to initialize audio");

	}

	if (!loadBackgroundMusic(audioData))
	{
		fprintf(stderr, "Failure to load Music\n");
	}
}

/**
 * main - the main entry of the program
 * Return: exit status
 */

int main(void)
{

	gameData gameData;
	gameData.screenBuffer = NULL;
	gameData.redXorTexture = NULL;
	gameData.greenXorTexture = NULL;
	gameData.blueXorTexture = NULL;
	gameData.grayXorTexture = NULL;
	/*initialize colors */
	gameData.COLORS[0] = RGBtoABGR(255, 0, 0);
    gameData.COLORS[R] = RGBtoABGR(0, 255, 0);
    gameData.COLORS[2] = RGBtoABGR(0, 0, 255);
    gameData.COLORS[3] = RGBtoABGR(128, 128, 128);
	/*program toggles */
	gameData.gameIsRunning = TRUE;
	gameData.showMap = TRUE;
	gameData.distortion = FALSE;
	gameData.slowRenderMode = 0;
	gameData.rayCastMode = 0;
	gameData.textureMode = 0;

	if (!setupWindow(&gameData))
	{
		fprintf(stderr, "Could not initialize raycaster!\n");
		return (EXIT_FAILURE);
	}

	initAudio(&audioData);
	initPlayer();
	initRaycaster();
	runGame(&gameData, &audioData);
	destroyGFX();
	return (EXIT_SUCCESS);
}
