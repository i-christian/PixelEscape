#include "../../inc/graphics.h"

/* Error string buffer */
char errstr[256];

/**
 * gfxGetError - Get the graphics error string.
 *
 * Returns: The graphics error string.
 */
const char* gfxGetError(void) {
    return (errstr);
}

/**
 * gfxSetError - Set the graphics error string.
 *
 * @str: The error message to set.
 * @showSdlErr: Flag indicating whether to append SDL error message.
 *
 * Returns: Nothing.
 */
void gfxSetError(char* str, char showSdlErr) {
    if(showSdlErr)
        sprintf(errstr, "%s: %s", str, SDL_GetError());
    else
        sprintf(errstr, "%s", str);
}
