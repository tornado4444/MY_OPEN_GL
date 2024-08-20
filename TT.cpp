#include "TT.h"

TT::Time::Time() {
    lastTime = (float)glfwGetTime();
    delta = 0.0f;
    time = 0.0f;
}

void TT::Time::update() {
    float currentTime = (float)glfwGetTime();
    delta = currentTime - lastTime;
    lastTime = currentTime;


    this -> time += delta;
}

float TT::Time::getDelta() {
    return delta;
}

float TT::Time::getTime() {
    return time;
}