#include "CCanvas.h"
#include "../CPoint.h"
#include <GLFW/glfw3.h>

// Реализация DrawLine с const
void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor) const 
{
    // Код рисования линии (пример для OpenGL):
    glColor3ub((lineColor >> 16) & 0xFF, (lineColor >> 8) & 0xFF, lineColor & 0xFF);
    glBegin(GL_LINES);
    glVertex2i(from.x, from.y);
    glVertex2i(to.x, to.y);
    glEnd();
}

// Реализация FillPolygon
void CCanvas::FillPolygon(std::vector<CPoint> points, uint32_t fillColor) const 
{
    // Код заполнения полигона (пример для OpenGL):
    glColor3ub((fillColor >> 16) & 0xFF, (fillColor >> 8) & 0xFF, fillColor & 0xFF);
    glBegin(GL_POLYGON);
    for (const auto& point : points) 
    {
        glVertex2i(point.x, point.y);
    }
    glEnd();
}

// Реализация DrawCircle
void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor) const 
{
    // Код рисования окружности (пример для OpenGL):
    glColor3ub((lineColor >> 16) & 0xFF, (lineColor >> 8) & 0xFF, lineColor & 0xFF);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; ++i) 
    {
        float angle = i * 3.14159f / 180;
        int x = center.x + radius * cos(angle);
        int y = center.y + radius * sin(angle);
        glVertex2i(x, y);
    }
    glEnd();
}

// Реализация FillCircle
void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor) const 
{
    // Код заполнения окружности (пример для OpenGL):
    glColor3ub((fillColor >> 16) & 0xFF, (fillColor >> 8) & 0xFF, fillColor & 0xFF);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(center.x, center.y);
    for (int i = 0; i <= 360; ++i) 
    {
        float angle = i * 3.14159f / 180;
        int x = center.x + radius * cos(angle);
        int y = center.y + radius * sin(angle);
        glVertex2i(x, y);
    }
    glEnd();
}