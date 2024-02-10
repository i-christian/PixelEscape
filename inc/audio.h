#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include "config.h"

#define BACKGROUND_MUSIC_FILE "./src/assets/music/mysterious-sci-fi.wav"
/**
 * struct AudioData - global audio variables
 * @audioDeviceID: member1
 * @audioSpec: member2
 * @audioBuffer: member3
 * @audioLength: member4
 * @rw: pointer
 */
typedef struct AudioData
{
    SDL_AudioDeviceID audioDeviceID;
    SDL_AudioSpec audioSpec;
    Uint8 *audioBuffer;
    Uint32 audioLength;
    SDL_RWops *rw;
} AudioData;

extern AudioData audioData;
/* Functions declarations */
int loadBackgroundMusic(AudioData *audioData);
void audioCallback(void *userdata, Uint8 *stream, Uint32 len);
int initSDLAudio(AudioData *audioData);
void playBackgroundMusic(AudioData *audioData);
void closeSDLAudio(AudioData *audioData);
void audioWrapper(void *userdata, Uint8 *stream, int len);
#endif /* !_AUDIO_H_ */
