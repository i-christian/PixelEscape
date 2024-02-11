#include "../../inc/graphics.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>


ManagedTexture_* managedTextures = NULL;
SDL_Instance gInstance = { NULL, NULL };
unsigned int screenWidth = -1;
unsigned int screenHeight = -1;

/* Graphics functions for this game */

/**
 * initGFX - Initializing graphics.
 *
 * @title: The title of the game window.
 * @width: The width of the game window.
 * @height: The height of the game window.
 *
 * This function initializes the graphics components, creates an SDL window, and sets up a renderer.
 *
 * Return: 1 on success, 0 on failure.
 */
int initGFX(char* title, unsigned int width, unsigned int height)
{
	if(gInstance.window || gInstance.renderer) return 0;

	screenWidth = width;
    screenHeight = height;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        gfxSetError("Error initializing SDL", 1);
        return 0;
    }

    gInstance.window = SDL_CreateWindow(title, 50, 50, width, height, SDL_WINDOW_SHOWN);
    gInstance.renderer = SDL_CreateRenderer(gInstance.window, -1, SDL_RENDERER_SOFTWARE);

    if(!gInstance.window || !gInstance.renderer) {
        gfxSetError("Could not create SDL window", 1);
        return 0;
    }

    SDL_SetWindowTitle(gInstance.window, title);

    SDL_SetRenderDrawColor(gInstance.renderer, 255, 255, 255, 255);
    SDL_RenderClear(gInstance.renderer);
    SDL_RenderPresent(gInstance.renderer);

    return 1;
}

/**
 * createTexture - Create a managed texture.
 *
 * @width: The width of the texture.
 * @height: The height of the texture.
 *
 * This function creates a managed texture and returns a pointer to the pixel data.
 *
 * Return: A pointer to the pixel data of the created texture.
 */
void* createTexture(unsigned int width, unsigned int height)
{
    Uint32* data;
    ManagedTexture_* newmtex;
    if(!width || !height || !gInstance.renderer) {
        gfxSetError("SDL window has not been initialized yet", 0);
        return NULL;
    }

    newmtex = malloc(sizeof(ManagedTexture_)); if(!newmtex) { return NULL; }
    newmtex->pitch = width * sizeof(Uint32);
    newmtex->next = NULL;
    newmtex->prev = NULL;
    newmtex->magicTag  = TEX_TAG;

    newmtex->texture = SDL_CreateTexture(gInstance.renderer,
										 SDL_PIXELFORMAT_ABGR8888,
										 SDL_TEXTUREACCESS_STREAMING, width, height);
    if(!(newmtex->texture)) {
        free(newmtex);
        gfxSetError("Could not create texture", 1);
        return NULL;
    }

    data = malloc((sizeof(Uint32) * width * height) + sizeof(ManagedTexture_*)); if(!data) {free(newmtex); return NULL; }

    /*
     * Hide a pointer to the managed struct before the actual pixel data.
     *
     * This allows the caller to only have to worry about the data they
     * want, while still allowing this library to perform more complicated
     * management tasks given only a reference to the pixel data.
     */
    *((ManagedTexture_**)data) = newmtex;
    newmtex->pixelData = ((ManagedTexture_**)data) + 1;

    /* Insert the item into the linked list */
    if(managedTextures) {
        newmtex->next = managedTextures;
        managedTextures->prev = newmtex;
    }
    managedTextures = newmtex;


    return newmtex->pixelData;
}


/**
 * destroyTexture - Destroy a managed texture.
 *
 * @ptr: A pointer to the pixel data of the texture.
 *
 * This function destroys a managed texture and frees associated memory.
 *
 * Return: 1 on success, 0 on failure.
 */
int destroyTexture(void* ptr) {
    /* Recover the memory management structure before freeing anything */
    ManagedTexture_* mtex = *(((ManagedTexture_**)ptr) - 1);

    /* Don't do anything if it's not actually a managed structure */
    if(mtex->magicTag != TEX_TAG) {
        gfxSetError("Not a valid texture pointer", 0);
        return 0;
    }

    /* Prevent this structure from being somehow sent here again */
    mtex->magicTag = 0;

    /* Actual cleanup */
    free(((ManagedTexture_**)ptr) - 1);

    SDL_DestroyTexture(mtex->texture);

    if(mtex->prev) mtex->prev->next = mtex->next;
    if(mtex->next) mtex->next->prev = mtex->prev;
    if(managedTextures == mtex) managedTextures = mtex->next;
    free(mtex);

    return 1;
}


/**
 * displayFullscreenTexture - Display a managed texture in fullscreen.
 *
 * @texture: A pointer to the pixel data of the texture.
 *
 * This function updates and renders a managed texture in fullscreen.
 *
 * Return: void
 */
void displayFullscreenTexture(void* texture)
{
    ManagedTexture_* mtex;

    if(!gInstance.window || !gInstance.renderer) {
        gfxSetError("SDL window has not been initialized yet", 0);
        return;
    }

    /* Recover the managed texture structure */
    mtex = *(((ManagedTexture_**)texture) - 1);

    /* Don't do anything if it's not actually a managed texture */
    if(mtex->magicTag != TEX_TAG) {
        gfxSetError("Not a valid texture pointer", 0);
        return;
    }

    SDL_UpdateTexture(mtex->texture, NULL, mtex->pixelData, mtex->pitch);

    SDL_RenderClear(gInstance.renderer);
    SDL_RenderCopy(gInstance.renderer, mtex->texture, NULL, NULL);
    SDL_RenderPresent(gInstance.renderer);
}


/**
 * destroyGFX - Destroy graphics components.
 *
 * This function cleans up allocated textures and destroys SDL window and renderer.
 *
 * Return: void
 */
void destroyGFX()
{
    /* Destroy all allocated textures */
    while(managedTextures) destroyTexture(managedTextures->pixelData);

    /* Clean everything else up */
    if(gInstance.window && gInstance.renderer) {
        SDL_DestroyRenderer(gInstance.renderer);
        gInstance.renderer = NULL;
        SDL_DestroyWindow(gInstance.window);
        gInstance.window = NULL;

        SDL_Quit();
    }
}
