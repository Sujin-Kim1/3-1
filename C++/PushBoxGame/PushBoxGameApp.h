#ifndef PUSHBOXGAME_PUSHBOXAPP_H
#define PUSHBOXGAME_PUSHBOXAPP_H

#include <ncurses.h>
#include "PushBoxMap.h"
#include "StatusMap.h"

class PushBoxMap;

class StatusMap;


class PushBoxGameApp {
public:
    PushBoxGameApp();

    ~PushBoxGameApp();

    void Play();

protected:
    PushBoxMap *m_pPushBoxMap;
    StatusMap *m_pStatusMap;

    void Init();

    void Render();

    void Destroy();
};


#endif //PUSHBOXGAME_PUSHBOXAPP_H
