/*
  timer.cpp - Class to create and manage timers.
  Created by Ricardo Steijn, September 22, 2020.
*/

#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer {
public:
    Timer(unsigned long milliseconds);
    void start();
    void stop();
    void restart();
    void set(unsigned long milliseconds);
    void waitFor();
    bool done();
    unsigned long getElapsedTime();
private:
    unsigned long timeToElapse;
    unsigned long startTime;
    bool isStarted;
};

#endif