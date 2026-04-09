#ifndef PLAY_LISTENER_H
#define PLAY_LISTENER_H

class PlayListener {
    public:

    virtual void selectPoint(Point pos) = 0;

    virtual void confirmStrike() = 0;

    virtual ~PlayListener() = default;
};

#endif