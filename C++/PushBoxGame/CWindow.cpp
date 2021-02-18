#include "CWindow.h"

CWindow::CWindow(int x, int y, int width, int height)
        : m_x(x), m_y(y), m_width(width), m_height(height) {
    m_pWindow = newwin(height, width, y, x);
    wrefresh(m_pWindow);
}

CWindow::CWindow() {
    CWindow(0, 0, 0, 0);
}

CWindow::~CWindow() {
    delwin(m_pWindow);
}

void CWindow::Draw() {
    box(m_pWindow, 0, 0);
    wrefresh(m_pWindow);
}
