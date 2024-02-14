#include "../../inc/audio.h"

AudioData audioData;

/**
 * loadBackgroundMusic - Loads background music into memory.
 *
 * @audioData: Pointer to the AudioData structure.
 *
 * This function loads the background music file into memory, allocates memory
 * for the audio buffer, and reads the background music data into the buffer.
 *
 * Return: TRUE if the background music is loaded successfully, FALSE otherwise.
 */
int loadBackgroundMusic(AudioData *audioData) {
    audioData->rw = SDL_RWFromFile(BACKGROUND_MUSIC_FILE, "rb");
    if (audioData->rw == NULL) {
        fprintf(stderr, "Failed to load background music file: %s\n", SDL_GetError());
        return FALSE;
    }

    audioData->audioLength = SDL_RWsize(audioData->rw);
    audioData->audioBuffer = (Uint8 *)malloc(audioData->audioLength);
    if (audioData->audioBuffer == NULL) {
        fprintf(stderr, "Failed to allocate memory for background music: %s\n", SDL_GetError());
        SDL_RWclose(audioData->rw);
        return FALSE;
    }

    if (SDL_RWread(audioData->rw, audioData->audioBuffer, 1, audioData->audioLength) != audioData->audioLength) {
        fprintf(stderr, "Failed to read background music data: %s\n", SDL_GetError());
        SDL_RWclose(audioData->rw);
        free(audioData->audioBuffer);
        return FALSE;
    }

    SDL_RWclose(audioData->rw);
    return TRUE;
}

/**
 * audioCallback - Audio callback function.
 *
 * @userdata: Pointer to user data (unused).
 * @stream: Pointer to the audio stream buffer.
 * @len: Length of the audio stream buffer.
 *
 * This function is the callback used by SDL to fill the audio stream buffer.
 * It copies audio data from the internal audio buffer to the stream buffer.
 *
 * Return: void
 */
/*void audioCallback(void *userdata, Uint8 *stream, Uint32 len) {
    (void)userdata;
    if (audioData.audioLength == 0) {
        return;
    }

    len = (len > audioData.audioLength ? audioData.audioLength : len);
    SDL_memcpy(stream, audioData.audioBuffer, len);
    SDL_MixAudio(stream, audioData.audioBuffer, len, SDL_MIX_MAXVOLUME);
    audioData.audioBuffer += len;
    audioData.audioLength -= len;
}*/

void audioCallback(void *userdata, Uint8 *stream, Uint32 len) {
    (void)userdata;

    // Static variables to maintain state across function calls
    static Uint8 *audioBufferPtr = NULL;
    static Uint32 remainingLength = 0;

    // Initialize static variables on first function call
    if (audioBufferPtr == NULL || remainingLength == 0) {
        audioBufferPtr = audioData.audioBuffer;
        remainingLength = audioData.audioLength;
    }

    if (audioData.audioLength == 0) {
        return;
    }

    // If remaining length is less than len, loop back to the beginning
    if (remainingLength < len) {
        audioBufferPtr = audioData.audioBuffer;
        remainingLength = audioData.audioLength;
    }

    // Copy audio data from the internal audio buffer to the stream buffer
    SDL_memcpy(stream, audioBufferPtr, len);
    SDL_MixAudio(stream, audioBufferPtr, len, SDL_MIX_MAXVOLUME);

    // Update pointers and remaining length
    audioBufferPtr += len;
    remainingLength -= len;
}

/**
 * initSDLAudio - Initializes SDL audio subsystem and sets audio specifications.
 *
 * @audioData: Pointer to the AudioData structure.
 *
 * This function initializes the SDL audio subsystem, sets the desired audio
 * specifications, opens the audio device, and sets the audio callback function.
 *
 * Return: TRUE if SDL audio initializes successfully, FALSE otherwise.
 */
int initSDLAudio(AudioData *audioData) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL audio could not initialize! SDL Error: %s\n", SDL_GetError());
        return FALSE;
    }

    audioData->audioSpec.freq = 44100;
    audioData->audioSpec.format = AUDIO_S16SYS;
    audioData->audioSpec.channels = 2;
    audioData->audioSpec.samples = 2048;
    audioData->audioSpec.callback = audioWrapper;
    audioData->audioSpec.userdata = NULL;

    audioData->audioDeviceID = SDL_OpenAudioDevice(NULL, 0, &audioData->audioSpec, NULL, 0);
    if (audioData->audioDeviceID == 0) {
        fprintf(stderr, "Failed to open audio: %s\n", SDL_GetError());
        SDL_Quit();
        return FALSE;
    }

    return TRUE;
}

/**
 * playBackgroundMusic - Starts playing background music.
 *
 * @audioData: Pointer to the AudioData structure.
 *
 * This function resumes playing the background music by unpausing the audio device.
 *
 * Return: void
 */
void playBackgroundMusic(AudioData *audioData) {
    SDL_PauseAudioDevice(audioData->audioDeviceID, 0);
}

/**
 * closeSDLAudio - Frees resources and quits SDL audio subsystem.
 *
 * @audioData: Pointer to the AudioData structure.
 *
 * This function frees memory allocated for the audio buffer and closes the audio device.
 *
 * Return: void
 */
void closeSDLAudio(AudioData *audioData) {
    if (audioData->audioBuffer != NULL) {
        free(audioData->audioBuffer);
    }
    SDL_CloseAudioDevice(audioData->audioDeviceID);
}
