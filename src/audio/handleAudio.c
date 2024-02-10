#include "../../inc/audio.h"


AudioData audioData;
// Load background music into memory
int loadBackgroundMusic(AudioData *audioData)
{
    // Load the background music file
    audioData->rw = SDL_RWFromFile(BACKGROUND_MUSIC_FILE, "rb");
    if (audioData->rw == NULL) {
        fprintf(stderr, "Failed to load background music file: %s\n", SDL_GetError());
        return FALSE;
    }

    // Read the background music data
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

// Audio callback function
void audioCallback(void *userdata, Uint8 *stream, Uint32 len) {
	(void)userdata;
    if (audioData.audioLength == 0) {
        return;
    }

    len = (len > audioData.audioLength ? audioData.audioLength : len);
    SDL_memcpy(stream, audioData.audioBuffer, len);
    SDL_MixAudio(stream, audioData.audioBuffer, len, SDL_MIX_MAXVOLUME);
    audioData.audioBuffer += len;
    audioData.audioLength -= len;
}



// Function to initialize SDL audio
int initSDLAudio(AudioData *audioData) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL audio could not initialize! SDL Error: %s\n", SDL_GetError());
        return FALSE;
    }

    // Set the audio specifications
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

// Function to play background music
void playBackgroundMusic(AudioData *audioData) {
    SDL_PauseAudioDevice(audioData->audioDeviceID, 0); // Start playing audio
}

// Function to free resources and quit SDL audio
void closeSDLAudio(AudioData *audioData) {
    if (audioData->audioBuffer != NULL) {
        free(audioData->audioBuffer);
    }
    SDL_CloseAudioDevice(audioData->audioDeviceID);
}
