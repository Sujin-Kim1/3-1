#ifndef PUSHBOXGAME_STATUSMAP_H
#define PUSHBOXGAME_STATUSMAP_H

#include "CWindow.h"

class StatusMap : public CWindow {
public:
    StatusMap(int x, int y, int width, int height);

    ~StatusMap();

    virtual void Draw();

    void step();

    void push();

    void reset();

    void homerunUp();

    void homerunDown();

    void levelUp();

    void finish();

    int homerun;
    int m_level;
protected:
    int m_step;
    int m_push;
    bool isFinish;
};

#endif //PUSHBOXGAME_STATUSMAP_H
