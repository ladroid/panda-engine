//
// Created by Lado on 3/7/20.
//

#ifndef LOTOS_TIMER_H
#define LOTOS_TIMER_H

#include "SDL2/SDL.h"

class Timer
{
private:
    int m_StartTime;
    int m_PausedTime;
    bool m_Started;
    bool m_Paused;

public:
    Timer() : m_StartTime(0), m_PausedTime(0), m_Started(false), m_Paused(false) {}

    void start() {
        m_Started = true;
        m_Paused = false;

        m_StartTime = SDL_GetTicks();
        m_PausedTime = 0;
    }
    void stop() {
        m_Started = false;
        m_Paused = false;

        m_StartTime = 0;
        m_PausedTime = 0;
    }
    void pause() {
        if (m_Started && !m_Paused)
        {
            m_Paused = true;

            m_PausedTime = SDL_GetTicks() - m_StartTime;
            m_StartTime = 0;
        }
    }
    void unpause() {
        if (m_Started && m_Paused)
        {
            m_Paused = false;

            m_StartTime = SDL_GetTicks() - m_PausedTime;
            m_PausedTime = 0;
        }
    }
    int getTicks() {
        if (m_Started) {
            return m_Paused ? m_PausedTime : SDL_GetTicks() - m_StartTime;
        }

        return 0;
    }

    inline bool isStarted() const {
        return m_Started;
    }
    inline bool isPaused() const {
        return m_Paused;
    }
};

#endif //LOTOS_TIMER_H
