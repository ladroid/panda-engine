//
// Created by Lado on 4/7/20.
//

#ifndef LOTOS_AUDIO_H
#define LOTOS_AUDIO_H

#include <string>
#include "EntityComponent.h"
#include "SDL2/SDL.h"

class Audio : public Component {
private:
    std::string fileAudo = "";
    bool currentState;
    enum FUNC { ERROR = 0, WAITING ,PAUSED, STOPPED, PLAYING };
    SDL_AudioSpec want, have;
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;
    SDL_AudioDeviceID deviceId;
public:
    Audio(std::string pathAudio) {
        fileAudo = pathAudio;
    }

    void init() override {
        if(SDL_Init(SDL_INIT_AUDIO) != 1) {
            if(SDL_OpenAudio(&want, &have) == -1) {
                std::cerr << "Error initializing audio device...\n";
                currentState = ERROR;
            } else {
                currentState = WAITING;
            }
        }
    }

    void play() {
        if(currentState != ERROR) {
            if(SDL_Init(SDL_INIT_AUDIO) == 0) {
                currentState = PLAYING;
                SDL_LoadWAV(fileAudo.c_str(), &wavSpec, &wavBuffer, &wavLength);
                deviceId = SDL_OpenAudioDevice(nullptr, 0, &wavSpec, nullptr, 0);
                int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
                if(success > 0) {
                    std::cout << "Success!!!" << std::endl;
                }
                SDL_PauseAudioDevice(deviceId, 0);
                SDL_Delay(3000);
            } else {
                this->pause();
            }
        }
    }

    void pause() {
        if(currentState != ERROR) {
            SDL_PauseAudioDevice(deviceId, 1);
        }
    }

    bool isPlaying() {
        return currentState == PLAYING;
    }

    bool isPaused() {
        return currentState == PAUSED;
    }

    bool isStopped() {
        return currentState == STOPPED;
    }

    ~Audio() {
        SDL_CloseAudioDevice(deviceId);
        SDL_CloseAudio();
        SDL_FreeWAV(wavBuffer);
        SDL_Quit();
    }
};

#endif //LOTOS_AUDIO_H
