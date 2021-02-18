#include "PushBoxMap.h"

PushBoxMap::PushBoxMap(int x, int y, int height, int width)
        : CWindow(x, y, width + 3, height + 2) {
    box(m_pWindow, 0, 0);
    mvwprintw(m_pWindow, 0, 3, "< Push Box Game >");

    // m_mapData 를 m_mapData1 의 데이터로 초기화
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            m_mapData[i][j] = m_mapData1[i][j];
        }
    }
    //position to position1
    for (int i = 0; i < 2; i++) {
        position[i] = position1[i];
    }
}

PushBoxMap::PushBoxMap() {
}

PushBoxMap::~PushBoxMap() {
}

void PushBoxMap::SetMapData(int y, int x, int data) {
    m_mapData[y][x] = data;
}

void PushBoxMap::Draw() {
    wattron(m_pWindow, COLOR_PAIR(1));
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            switch (m_mapData[i][j]) {
                case -1: // 데이터가 없는 경우
                case 0:  // 길
                case 4:  // 바깥
                    mvwprintw(m_pWindow, i + 2, j + 12, "%s", ".");
                    break;
                case 1:  // 벽
                    wattron(m_pWindow, COLOR_PAIR(3));
                    mvwprintw(m_pWindow, i + 2, j + 12, "%s", " ");
                    wattroff(m_pWindow, COLOR_PAIR(3));
                    break;
                case 2:  // 상자
                    wattron(m_pWindow, COLOR_PAIR(4));
                    mvwprintw(m_pWindow, i + 2, j + 12, "%s", "B");
                    wattroff(m_pWindow, COLOR_PAIR(4));
                    break;
                case 3:  // 목적지
                    wattron(m_pWindow, COLOR_PAIR(5));
                    mvwprintw(m_pWindow, i + 2, j + 12, "%s", "-");
                    wattroff(m_pWindow, COLOR_PAIR(5));
                    break;
                case 5: // 캐릭터
                    mvwprintw(m_pWindow, i + 2, j + 12, "%s", "&");
                    break;
                case 6: // 캐릭터 + 목적지
                    wattron(m_pWindow, COLOR_PAIR(5));
                    mvwprintw(m_pWindow, i + 2, j + 12, "%s", "&");
                    wattroff(m_pWindow, COLOR_PAIR(5));
                    break;
                case 7: // 박스 + 목적지
                    wattron(m_pWindow, COLOR_PAIR(5));
                    mvwprintw(m_pWindow, i + 2, j + 12, "%s", "B");
                    wattroff(m_pWindow, COLOR_PAIR(5));
                    break;
            }
        }
    }
    wattroff(m_pWindow, COLOR_PAIR(1));
    wrefresh(m_pWindow);
}

void PushBoxMap::Redraw(StatusMap *m_pStatusMap) {
    keypad(stdscr, TRUE);
    int key = getch();
    if (m_pStatusMap->m_level <= 5) {
        switch (key) {
            case KEY_UP :
                //box and road
                if (m_mapData[position[0] - 1][position[1]] == 2 && m_mapData[position[0] - 2][position[1]] == 0) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0] - 1][position[1]] = 5;
                    m_mapData[position[0] - 2][position[1]] = 2;
                    position[0]--;
                    m_pStatusMap->step();
                    m_pStatusMap->push();

                }
                    //road
                else if (m_mapData[position[0] - 1][position[1]] == 0) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0] - 1][position[1]] = 5;
                    position[0]--;
                    m_pStatusMap->step();
                }
                    //box and target
                else if (m_mapData[position[0] - 1][position[1]] == 2 && m_mapData[position[0] - 2][position[1]] == 3) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0] - 1][position[1]] = 5;
                    m_mapData[position[0] - 2][position[1]] = 7;
                    position[0]--;
                    m_pStatusMap->step();
                    m_pStatusMap->push();
                    m_pStatusMap->homerunUp();
                }
                    //target
                else if (m_mapData[position[0] - 1][position[1]] == 3) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0] - 1][position[1]] = 6;
                    position[0]--;
                    m_pStatusMap->step();
                }
                    //box with target and target
                else if (m_mapData[position[0] - 1][position[1]] == 7 && m_mapData[position[0] - 2][position[1]] == 3) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0] - 1][position[1]] = 6;
                    m_mapData[position[0] - 2][position[1]] = 7;
                    position[0]--;
                    m_pStatusMap->step();
                    m_pStatusMap->push();
                }
                    //box with target and road
                else if (m_mapData[position[0] - 1][position[1]] == 7 && m_mapData[position[0] - 2][position[1]] == 0) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0] - 1][position[1]] = 6;
                    m_mapData[position[0] - 2][position[1]] = 2;
                    position[0]--;
                    m_pStatusMap->step();
                    m_pStatusMap->push();
                    m_pStatusMap->homerunDown();
                }
                break;
            case KEY_DOWN :
                //box and road
                if (m_mapData[position[0] + 1][position[1]] == 2 && m_mapData[position[0] + 2][position[1]] == 0) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0] + 1][position[1]] = 5;
                    m_mapData[position[0] + 2][position[1]] = 2;
                    position[0]++;
                    m_pStatusMap->step();
                    m_pStatusMap->push();
                }
                    //road
                else if (m_mapData[position[0] + 1][position[1]] == 0) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0] + 1][position[1]] = 5;
                    position[0]++;
                    m_pStatusMap->step();
                }
                    //box and target
                else if (m_mapData[position[0] + 1][position[1]] == 2 && m_mapData[position[0] + 2][position[1]] == 3) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0] + 1][position[1]] = 5;
                    m_mapData[position[0] + 2][position[1]] = 7;
                    position[0]++;
                    m_pStatusMap->step();
                    m_pStatusMap->push();
                    m_pStatusMap->homerunUp();
                }
                    //target
                else if (m_mapData[position[0] + 1][position[1]] == 3) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0] + 1][position[1]] = 6;
                    position[0]++;
                    m_pStatusMap->step();
                }
                    //box with target and target
                else if (m_mapData[position[0] + 1][position[1]] == 7 && m_mapData[position[0] + 2][position[1]] == 3) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0] + 1][position[1]] = 6;
                    m_mapData[position[0] + 2][position[1]] = 7;
                    position[0]++;
                    m_pStatusMap->step();
                    m_pStatusMap->push();
                }
                    //box with target and road
                else if (m_mapData[position[0] + 1][position[1]] == 7 && m_mapData[position[0] + 2][position[1]] == 0) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0] + 1][position[1]] = 6;
                    m_mapData[position[0] + 2][position[1]] = 2;
                    position[0]++;
                    m_pStatusMap->step();
                    m_pStatusMap->push();
                    m_pStatusMap->homerunDown();
                }
                break;
            case KEY_LEFT :
                //box and road
                if (m_mapData[position[0]][position[1] - 1] == 2 && m_mapData[position[0]][position[1] - 2] == 0) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0]][position[1] - 1] = 5;
                    m_mapData[position[0]][position[1] - 2] = 2;
                    position[1]--;
                    m_pStatusMap->step();
                    m_pStatusMap->push();
                }
                    //road
                else if (m_mapData[position[0]][position[1] - 1] == 0) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0]][position[1] - 1] = 5;
                    position[1]--;
                    m_pStatusMap->step();
                }
                    //box and target
                else if (m_mapData[position[0]][position[1] - 1] == 2 && m_mapData[position[0]][position[1] - 2] == 3) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0]][position[1] - 1] = 5;
                    m_mapData[position[0]][position[1] - 2] = 7;
                    position[1]--;
                    m_pStatusMap->step();
                    m_pStatusMap->push();
                    m_pStatusMap->homerunUp();
                }
                    //target
                else if (m_mapData[position[0]][position[1] - 1] == 3) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0]][position[1] - 1] = 6;
                    position[1]--;
                    m_pStatusMap->step();
                }
                    //box with target and target
                else if (m_mapData[position[0]][position[1] - 1] == 7 && m_mapData[position[0]][position[1] - 2] == 3) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0]][position[1] - 1] = 6;
                    m_mapData[position[0]][position[1] - 2] = 7;
                    position[1]--;
                    m_pStatusMap->step();
                    m_pStatusMap->push();
                }
                    //box with target and road
                else if (m_mapData[position[0]][position[1] - 1] == 7 && m_mapData[position[0]][position[1] - 2] == 0) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0]][position[1] - 1] = 6;
                    m_mapData[position[0]][position[1] - 2] = 2;
                    position[1]--;
                    m_pStatusMap->step();
                    m_pStatusMap->push();
                    m_pStatusMap->homerunDown();
                }
                break;
            case KEY_RIGHT:
                //box and road
                if (m_mapData[position[0]][position[1] + 1] == 2 && m_mapData[position[0]][position[1] + 2] == 0) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0]][position[1] + 1] = 5;
                    m_mapData[position[0]][position[1] + 2] = 2;
                    position[1]++;
                    m_pStatusMap->step();
                    m_pStatusMap->push();
                }
                    //road
                else if (m_mapData[position[0]][position[1] + 1] == 0) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0]][position[1] + 1] = 5;
                    position[1]++;
                    m_pStatusMap->step();
                }
                    //box and target
                else if (m_mapData[position[0]][position[1] + 1] == 2 && m_mapData[position[0]][position[1] + 2] == 3) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0]][position[1] + 1] = 5;
                    m_mapData[position[0]][position[1] + 2] = 7;
                    position[1]++;
                    m_pStatusMap->step();
                    m_pStatusMap->push();
                    m_pStatusMap->homerunUp();
                }
                    //target
                else if (m_mapData[position[0]][position[1] + 1] == 3) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0]][position[1] + 1] = 6;
                    position[1]++;
                    m_pStatusMap->step();
                }
                    //box with target and target
                else if (m_mapData[position[0]][position[1] + 1] == 7 && m_mapData[position[0]][position[1] + 2] == 3) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0]][position[1] + 1] = 6;
                    m_mapData[position[0]][position[1] + 2] = 7;
                    position[1]++;
                    m_pStatusMap->step();
                    m_pStatusMap->push();
                }
                    //box with target and road
                else if (m_mapData[position[0]][position[1] + 1] == 7 && m_mapData[position[0]][position[1] + 2] == 0) {
                    if (m_mapData[position[0]][position[1]] == 5) m_mapData[position[0]][position[1]] = 0;
                    else if (m_mapData[position[0]][position[1]] == 6) m_mapData[position[0]][position[1]] = 3;
                    m_mapData[position[0]][position[1] + 1] = 6;
                    m_mapData[position[0]][position[1] + 2] = 2;
                    position[1]++;
                    m_pStatusMap->step();
                    m_pStatusMap->push();
                    m_pStatusMap->homerunDown();

                }
                break;
                //RESET
            case KEY_HOME:
                setAllMapData(m_pStatusMap->m_level, m_pStatusMap);
                m_pStatusMap->reset();
                break;
        }
        gameLevelUp(m_pStatusMap->homerun, m_pStatusMap->m_level, m_pStatusMap);
    }
}

void PushBoxMap::setAllMapData(int level, StatusMap *m_pStatusMap) {
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            switch (level) {
                case 1:
                    m_mapData[i][j] = m_mapData1[i][j];
                    position[0] = position1[0];
                    position[1] = position1[1];
                    break;
                case 2:
                    m_mapData[i][j] = m_mapData2[i][j];
                    position[0] = position2[0];
                    position[1] = position2[1];
                    break;
                case 3:
                    m_mapData[i][j] = m_mapData3[i][j];
                    position[0] = position3[0];
                    position[1] = position3[1];
                    break;
                case 4:
                    m_mapData[i][j] = m_mapData4[i][j];
                    position[0] = position4[0];
                    position[1] = position4[1];
                    break;
                case 5:
                    m_mapData[i][j] = m_mapData5[i][j];
                    position[0] = position5[0];
                    position[1] = position5[1];
                    break;
            }
        }
    }
    m_pStatusMap->reset();
}

void PushBoxMap::gameLevelUp(int homerun, int level, StatusMap *m_pStatusMap) {
    if (homerun == 3 && level != 3) {
            m_pStatusMap->levelUp();

        switch (level) {
            case 1:
                setAllMapData(2, m_pStatusMap);
                break;
            case 2:
                setAllMapData(3, m_pStatusMap);
                break;
            case 4:
                setAllMapData(5, m_pStatusMap);
                break;
            case 5:
                m_pStatusMap->finish();
                break;
        }

    }
    else if (homerun == 6 && level == 3) {
        m_pStatusMap->levelUp();
        setAllMapData(4, m_pStatusMap);
    }
}