#include "Timer.h"
#include <SDL.h>

void Timer::Start()
{
    Started = true;
    Paused = false;

    StartTime = SDL_GetTicks();
    PausedTime = 0;
}

void Timer::Stop()
{
    Started = false;
    Paused = false;

    StartTime = 0;
    PausedTime = 0;
}

void Timer::Pause()
{
    if (Started && !Paused)
    {
        Paused = true;

        PausedTime = SDL_GetTicks() - StartTime;
        StartTime = 0;
    }
}

void Timer::Unpause()
{
    if (Started && Paused)
    {
        Paused = false;

        StartTime = SDL_GetTicks() - PausedTime;
        PausedTime = 0;
    }
}

int Timer::GetTicks()
{
    if (Started)
        return Paused ? PausedTime : SDL_GetTicks() - StartTime;

    return 0;
}