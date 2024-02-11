#include "../../inc/audio.h"

/**
 * audioWrapper - Audio callback wrapper function.
 *
 * @userdata: Pointer to user data.
 * @stream: Pointer to the audio stream buffer.
 * @len: Length of the audio stream buffer.
 *
 * Description: This function serves as a wrapper for the audio callback function. It passes
 * the user data, audio stream buffer, and length to the audio callback function.
 *
 * Return: void
 */
void audioWrapper(void *userdata, Uint8 *stream, int len) {
    audioCallback(userdata, stream, len);
}
