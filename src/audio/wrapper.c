#include "../../inc/audio.h"

void audioWrapper(void *userdata, Uint8 *stream, int len) {
    audioCallback(userdata, stream, len);
}
