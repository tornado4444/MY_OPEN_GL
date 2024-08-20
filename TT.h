#ifndef TT_H
#define TT_H

#include <GLFW/glfw3.h>

namespace TT {
    class Time {
    public:
        Time();
        void update();
        float getDelta();
        float getTime();

    private:
        float lastTime;
        float delta;
        float time;
    };
}

#endif // TT_H

