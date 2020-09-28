/*
  timer.cpp - Class to create and manage timers.
  Created by Ricardo Steijn, September 22, 2020.
*/

#include "timer.h"

Timer::Timer(unsigned long milliseconds) {
    // Create a new timer.
    this->timeToElapse = milliseconds;
}

void Timer::start() {
    // start the timer.
    this->startTime = millis();
    this->isStarted = true;
}

void Timer::stop() {
    // stop the timer.
    this->isStarted = false;

    Serial.print("Timer stopped. ");
    Serial.print("Time ellapsed until stop: ");
    Serial.println(this->getElapsedTime());
}

void Timer::restart() {
    // restart the timer at any point.
    if (!(this->done())) this->startTime = millis();
    else this->start();
}

void Timer::set(unsigned long milliseconds) {
    // set a new time for the timer.
    this->timeToElapse = milliseconds;
}

void Timer::waitFor() {
    // block until the timer is complete.
    while (!(this->done())) {}
}

bool Timer::done() {
    // return if the timer is done.
    if (!(this->isStarted)) return false;
    if ((millis() - this->startTime) >= this->timeToElapse) {
        return true;
    }
    return false;
}

unsigned long Timer::getElapsedTime() {
    // get the ellapsed time for the timer.
    return millis() - this->startTime;
}