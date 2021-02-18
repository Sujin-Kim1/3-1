#include "StatusMap.h"

StatusMap::StatusMap(int x, int y, int width, int height)
        : CWindow(x, y, width, height) {
    box(m_pWindow, 0, 0);
    mvwprintw(m_pWindow, 0, 3, "< STATUS >");  // 제목 출력

    m_step = 0;
    m_push = 0;
    m_level = 1;
    homerun = 0;
    isFinish = false;
}

StatusMap::~StatusMap() {
}

void StatusMap::Draw() {
    if (isFinish == false) {
        wattron(m_pWindow, COLOR_PAIR(2));
        mvwprintw(m_pWindow, 1, 2, "Step  :   ");
        mvwprintw(m_pWindow, 1, 2, "Step  : %d", m_step);
        mvwprintw(m_pWindow, 2, 2, "Push  :   ");
        mvwprintw(m_pWindow, 2, 2, "Push  : %d", m_push);
        mvwprintw(m_pWindow, 3, 2, "Level  : %d", m_level);
        mvwprintw(m_pWindow, 4, 2, "homerun : %d", homerun);
        mvwprintw(m_pWindow, 5, 2, "reset : Home (Window)");
        mvwprintw(m_pWindow, 6, 2, "reset : fn + <- (Mac)");
        wattroff(m_pWindow, COLOR_PAIR(2));
        wrefresh(m_pWindow);
    }
    else {
        wattron(m_pWindow, COLOR_PAIR(1));
        for (int i = 1; i <= 6; i++) {
            mvwprintw(m_pWindow, i, 2, "\t\t\t");
        }
        mvwprintw(m_pWindow, 3, 2, "\t SUCCESS !!!!");
        wattroff(m_pWindow, COLOR_PAIR(1));
        wrefresh(m_pWindow);
    }
}

void StatusMap::step() {
    m_step++;
}

void StatusMap::push() {
    m_push++;
}

void StatusMap::homerunUp() {
    homerun++;
}

void StatusMap::homerunDown() {
    homerun--;
}

void StatusMap::reset() {
    m_push = 0;
    m_step = 0;
    homerun = 0;
}

void StatusMap::levelUp() {
    m_level++;
}

void StatusMap::finish() {
    isFinish = true;
}