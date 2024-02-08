#ifndef GFX_H
#define GFX_H

#include <SDL2/SDL_video.h>
#include <math.h>
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

/* Used to identify a texture structure in memory */
#define TEX_TAG 0x55AA

/*
 * SDL textures are stored in VRAM, so we need to manage
 * a RAM-persistent copy of the texture's pixel data that we
 * can write to. Allocated textures are stored in a linked
 * list so we can keep track of them all easily.
 */
typedef struct ManagedTexture_ ManagedTexture_;
struct ManagedTexture_ {
    void* pixelData; /* RAM copy of the texture */
    SDL_Texture* texture;
    Uint32 pitch;
    ManagedTexture_* next;
    ManagedTexture_* prev;
    Uint16 magicTag;
};

typedef struct SDL_Instance {
  SDL_Window *window;
  SDL_Renderer *renderer;
} SDL_Instance;

/*Initialise external variable */
extern ManagedTexture_* managedTextures;
extern SDL_Instance gInstance;
extern unsigned int screenWidth;
extern unsigned int screenHeight;

#define RGBtoABGR(R,G,B)   (0xFF000000 | ((B) << 16) | ((G) << 8) | (R))
const char* gfxGetError();
void gfxSetError(char* str, char showSdlErr);


/*functions used */
int initGFX(char* title, unsigned int width, unsigned int height);
void* createTexture(unsigned int width, unsigned int height);
int destroyTexture(void* texture);
void displayFullscreenTexture(void* texture);
void destroyGFX();

/*drawing functions */
void setDrawColor(int r, int g, int b, int a);
void drawLine(int x1, int y1, int x2, int y2);
void fillRect(int x, int y, int w, int h);
void drawRect(int x, int y, int w, int h);
void presentRenderer();
void clearRenderer();

Uint32* generateXorTexture(int size, int redmask, int greenmask, int bluemask);
Uint32* generateRedXorTexture(int size);
Uint32* generateGreenXorTexture(int size);
Uint32* generateBlueXorTexture(int size);
Uint32* generateGrayXorTexture(int size);


#endif /* GFX_H */
