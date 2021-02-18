#include "PushBoxGameApp.h"

PushBoxGameApp::PushBoxGameApp() {
    m_pPushBoxMap = NULL;
    m_pStatusMap = NULL;
}

PushBoxGameApp::~PushBoxGameApp() {
    if (m_pPushBoxMap) {
        delete m_pPushBoxMap;
        m_pPushBoxMap = NULL;
    }
    if (m_pStatusMap) {
        delete m_pStatusMap;
        m_pStatusMap = NULL;
    }
}

void PushBoxGameApp::Play() {
    Init();
    Render();
    Destroy();
}

void PushBoxGameApp::Init() {
    initscr();
    start_color();
    cbreak();
    refresh();
    // color setting
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_WHITE);  // 벽
    init_pair(4, COLOR_WHITE, COLOR_BLUE);  // 상자
    init_pair(5, COLOR_WHITE, COLOR_RED); // 목적지

    m_pPushBoxMap = new PushBoxMap(3, 3, 12, 30);
    m_pStatusMap = new StatusMap(40, 3, 30, 8);
}

void PushBoxGameApp::Render() {
    m_pPushBoxMap->Draw();
    m_pStatusMap->Draw();
    while (1) {
        m_pPushBoxMap->Draw();
        m_pPushBoxMap->Redraw(m_pStatusMap);
        m_pStatusMap->Draw();
    }
}


void PushBoxGameApp::Destroy() {
    getch();
    endwin();
    delete m_pPushBoxMap;
    delete m_pStatusMap;
}
