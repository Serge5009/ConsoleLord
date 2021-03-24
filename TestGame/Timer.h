#pragma once

class Timer
{
private:
    int StartTime;
    int PausedTime;
    bool Started;
    bool Paused;

public:
    Timer()
        : StartTime(0), PausedTime(0), Started(false), Paused(false) {}

    void Start();
    void Stop();
    void Pause();
    void Unpause();
    int GetTicks();

    inline bool IsStarted() const { return Started; }
    inline bool IsPaused() const { return Paused; }
};
