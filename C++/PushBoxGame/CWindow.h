#ifndef PUSHBOXGAME_CWINDOW_H
#define PUSHBOXGAME_CWINDOW_H

#include <ncurses.h>

class CWindow {
public:
    CWindow(int x, int y, int width, int height);

    CWindow();

    virtual ~CWindow();

    virtual void Draw();

    virtual WINDOW *GetWindow() const { return m_pWindow; };

protected:
    int m_width;
    int m_height;
    int m_x, m_y;
    WINDOW *m_pWindow;
};


#endif //PUSHBOXGAME_CWINDOW_H
