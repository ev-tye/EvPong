#include "sound.h"

#include <SDL3/SDL.h>

#define SAMPLE_RATE     44100
#define AMPLITUDE       3000
#define DURATION_MS     50

typedef struct { int frequency; int samples_remaining; bool active; } ToneState;

static ToneState tone = {0};
static SDL_AudioSpec spec = {0};
static SDL_AudioDeviceID dev_id = 0;
static SDL_AudioStream *stream = NULL;

static void SDLCALL AudioCallback(void *user_data, SDL_AudioStream *stream, int stream_frame_count, int stream_frame_size)
{
    if(!tone.active) return;

    const int num_samples = stream_frame_count;
    Sint16 *buffer = SDL_malloc(num_samples * sizeof(Sint16));
    if(!buffer)
    {
        return;
    }

    int wave_period = SAMPLE_RATE / tone.frequency;
    for(int i = 0; i < num_samples; ++i)
    {
        buffer[i] = (i % wave_period) < (wave_period / 2) ? AMPLITUDE : -AMPLITUDE;
    }

    int write_size = SDL_min(tone.samples_remaining, num_samples) * sizeof(Sint16);
    if(!SDL_PutAudioStreamData(stream, buffer, write_size))
    {
        SDL_free(buffer);
        return;
    }

    tone.samples_remaining -= (write_size / sizeof(Sint16));
    if(tone.samples_remaining <= 0) tone.active = false;
    SDL_free(buffer);
}

bool S_Init()
{
    if(!SDL_InitSubSystem(SDL_INIT_AUDIO)) return false;

    dev_id = SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK;

    spec.freq = SAMPLE_RATE;
    spec.format = SDL_AUDIO_S16;
    spec.channels = 1;

    stream = SDL_OpenAudioDeviceStream(dev_id, &spec, AudioCallback, NULL);
    if(!stream)
    {
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        return false;
    }

    SDL_ResumeAudioStreamDevice(stream);
    return true;
}

void S_Stop()
{
    SDL_DestroyAudioStream(stream);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void S_PlayBeep()
{
    tone.frequency = 880;
    tone.samples_remaining = (SAMPLE_RATE * DURATION_MS) / 1000;
    tone.active = true;
}

void S_PlayBoop()
{
    tone.frequency = 220;
    tone.samples_remaining = (SAMPLE_RATE * DURATION_MS) / 1000;
    tone.active = true;
}