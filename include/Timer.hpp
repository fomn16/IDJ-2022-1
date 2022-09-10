#ifndef __TIMER_H__
#define __TIMER_H__

class Timer{
    public:
        Timer();

        void Update(float dt);
        void Restart();
        float Get();
    private:
        float time;
};

#endif