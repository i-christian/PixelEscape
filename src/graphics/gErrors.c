#include "../../inc/graphics.h"

/* Error string buffer */
char errstr[256];

/**gfxGetError - a getter graphics errors function
 *Return: nothing
 */
const char* gfxGetError(void) {
    return (errstr);
}

/**gfxSetError - a setter graphics errors function
 *@str: param1
 *@showSdlErr: param2
 *Return: nothing
 */
void gfxSetError(char* str, char showSdlErr) {
    if(showSdlErr)
        sprintf(errstr, "%s: %s", str, SDL_GetError());
    else
        sprintf(errstr, "%s", str);
}
