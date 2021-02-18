#ifndef PUSHBOXGAME_PUSHBOXMAP_H
#define PUSHBOXGAME_PUSHBOXMAP_H
#define MAX_SIZE 10

#include <ncurses.h>
#include "StatusMap.h"
#include "CWindow.h"

class StatusMap;

class PushBoxMap : public CWindow {
public:
    PushBoxMap(int x, int y, int width, int height);

    PushBoxMap();

    ~PushBoxMap();

    virtual void Draw();

    void Redraw(StatusMap *m_pStatusMap);

    void SetMapData(int x, int y, int data);

    void setAllMapData(int level, StatusMap *m_pStatusMap);

    void gameLevelUp(int homerun, int level, StatusMap *m_pStatusMap);

    int m_level;


protected:
    int m_mapData[MAX_SIZE][MAX_SIZE];
    int position[2];
    int position1[2] = {5, 2};
    int m_mapData1[MAX_SIZE][MAX_SIZE] =
            {{1, 1, 1, 1, 1, 4},
             {1, 0, 0, 0, 1, 4},
             {1, 3, 3, 3, 1, 4},
             {1, 2, 2, 2, 1, 1},
             {1, 0, 0, 0, 0, 1},
             {1, 0, 5, 0, 0, 1},
             {1, 1, 1, 1, 1, 1}};

    int position2[2] = {2, 6};
    int m_mapData2[MAX_SIZE][MAX_SIZE] =
            {{1, 1, 1, 1, 1, 1, 1, 1},
             {1, 3, 0, 0, 0, 0, 0, 1},
             {1, 0, 3, 2, 2, 2, 5, 1},
             {1, 3, 0, 0, 0, 0, 0, 1},
             {1, 1, 1, 1, 1, 0, 0, 1},
             {4, 4, 4, 4, 1, 1, 1, 1}};

    int position3[2] = {6, 3};
    int m_mapData3[MAX_SIZE][MAX_SIZE] =
            {{1, 1, 1, 1, 1, 1, 1},
             {1, 0, 0, 0, 0, 0, 1},
             {1, 0, 3, 2, 3, 0, 1},
             {1, 0, 2, 3, 2, 0, 1},
             {1, 0, 3, 2, 3, 0, 1},
             {1, 0, 2, 3, 2, 0, 1},
             {1, 0, 0, 5, 0, 0, 1},
             {1, 1, 1, 1, 1, 1, 1}};

    int position4[2] = {2, 2};
    int m_mapData4[MAX_SIZE][MAX_SIZE] =
            {{1, 1, 1, 1, 4, 4, 4},
             {1, 3, 0, 1, 1, 4, 4},
             {1, 3, 5, 0, 1, 4, 4},
             {1, 3, 0, 2, 1, 4, 4},
             {1, 1, 2, 0, 1, 1, 1},
             {4, 1, 0, 2, 0, 0, 1},
             {4, 1, 0, 0, 0, 0, 1},
             {4, 1, 0, 0, 1, 1, 1},
             {4, 1, 1, 1, 1, 4, 4}};


    int position5[2] = {4, 6};
    int m_mapData5[MAX_SIZE][MAX_SIZE] =
            {{4, 1, 1, 1, 1, 4, 4, 4, 4, 4},
             {4, 1, 0, 0, 1, 1, 1, 1, 4, 4},
             {4, 1, 0, 0, 0, 0, 0, 1, 1, 4},
             {1, 1, 0, 1, 1, 0, 0, 0, 1, 4},
             {1, 3, 0, 3, 1, 0, 5, 2, 1, 1},
             {1, 0, 0, 0, 1, 0, 2, 2, 0, 1},
             {1, 0, 0, 3, 1, 0, 0, 0, 0, 1},
             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
};


#endif //PUSHBOXGAME_PUSHBOXMAP_H
