#define CATCH_CONFIG_MAIN
#define _USE_MATH_DEFINES
#include "../../../catch.hpp"

#include <sstream>
#include <memory>
#include <vector>
#include <cmath>

#include "../CPoint.h"
#include "../CLineSegment.h"
#include "../CTriangle.h"
#include "../CRectangle.h"
#include "../CCircle.h"
#include "../CShapeManager.h"  


// Тесты для класса точки CPoint
TEST_CASE("CPoint: создание и доступ к координатам", "[geometry][point]") {
    CPoint p;
    p.x = 1.5; p.y = -2.0;
    REQUIRE(p.x == Approx(1.5));
    REQUIRE(p.y == Approx(-2.0));
}

// Тесты для класса отрезка CLineSegment
TEST_CASE("CLineSegment: площадь, периметр и цвет", "[geometry][linesegment]") {
    CPoint a, b;
    a.x = 0; a.y = 0;
    b.x = 3; b.y = 4;
    CLineSegment seg(a, b, 0xFF0000u);
    // площадь отрезка всегда 0
    REQUIRE(seg.GetArea() == Approx(0.0));
    // длина отрезка (периметр) = 5
    REQUIRE(seg.GetPerimeter() == Approx(5.0));
    REQUIRE(seg.GetOutlineColor() == 0xFF0000u);

    SECTION("ToString содержит информацию об отрезке") {
        std::string s = seg.ToString();
        REQUIRE(s.find("Line Segment") != std::string::npos);
        REQUIRE(s.find("(0, 0)") != std::string::npos);
        REQUIRE(s.find("(3, 4)") != std::string::npos);
    }
}

// Тесты для триугольника CTriangle 
TEST_CASE("CTriangle: площадь, периметр и цвета", "[geometry][triangle]") {
    // Инициализация трёх вершин
    CPoint a; a.x = 0; a.y = 0;
    CPoint b; b.x = 4; b.y = 0;
    CPoint c; c.x = 0; c.y = 3;
    uint32_t outline = 0x0000FFu;
    uint32_t fill = 0x00FF00u;
    CTriangle tri(a, b, c, outline, fill);

    // Проверяем площадь и периметр
    REQUIRE(tri.GetArea() == Approx(6.0));
    REQUIRE(tri.GetPerimeter() == Approx(12.0));
    // Проверяем цвета
    REQUIRE(tri.GetOutlineColor() == outline);
    REQUIRE(tri.GetFillColor() == fill);

    // Проверяем возвращаемые вершины по координатам (методы GetVertex1/2/3)
    CPoint v1 = tri.GetVertex1();
    REQUIRE(v1.x == Approx(a.x)); REQUIRE(v1.y == Approx(a.y));
    CPoint v2 = tri.GetVertex2();
    REQUIRE(v2.x == Approx(b.x)); REQUIRE(v2.y == Approx(b.y));
    CPoint v3 = tri.GetVertex3();
    REQUIRE(v3.x == Approx(c.x)); REQUIRE(v3.y == Approx(c.y));
}

// Тесты для прямоугольника CRectangle с двумя точками
TEST_CASE("CRectangle: площадь, периметр и свойства (две точки)", "[geometry][rectangle]") {
    CPoint topLeft;
    topLeft.x = 1; topLeft.y = 5;
    CPoint bottomRight;
    bottomRight.x = 4; bottomRight.y = 1;
    uint32_t outline = 0x123456u;
    uint32_t fill = 0x654321u;
    CRectangle rect(topLeft, bottomRight, outline, fill);

    // Проверяем вычисленную ширину и высоту
    REQUIRE(rect.GetWidth() == Approx(3.0));
    REQUIRE(rect.GetHeight() == Approx(4.0));
    // Проверяем площадь и периметр
    REQUIRE(rect.GetArea() == Approx(3.0 * 4.0));
    REQUIRE(rect.GetPerimeter() == Approx(2 * (3.0 + 4.0)));
    // Проверяем цвета
    REQUIRE(rect.GetOutlineColor() == outline);
    REQUIRE(rect.GetFillColor() == fill);
    // Проверяем возвращаемые точки
    CPoint lt = rect.GetLeftTop();
    REQUIRE(lt.x == Approx(topLeft.x));
    REQUIRE(lt.y == Approx(topLeft.y));
    CPoint rb = rect.GetRightBottom();
    REQUIRE(rb.x == Approx(bottomRight.x));
    REQUIRE(rb.y == Approx(bottomRight.y));
}

// Тесты для круга CCircle
TEST_CASE("CCircle: радиус, площадь и периметр", "[geometry][circle]") {
    CPoint center;
    center.x = 2; center.y = 2;
    double r = 5;
    CCircle circle(center, r, 0xABCDEFu, 0xFEDCBAu);
    REQUIRE(circle.GetRadius() == Approx(r));
    REQUIRE(circle.GetArea() == Approx(M_PI * r * r));
    REQUIRE(circle.GetPerimeter() == Approx(2 * M_PI * r));
    REQUIRE(circle.GetOutlineColor() == 0xABCDEFu);
    REQUIRE(circle.GetFillColor() == 0xFEDCBAu);
}

// Тесты для парсера чтения фигур из потока
TEST_CASE("ShapeReader: чтение и ошибки парсера", "[geometry][parser]") {
    istringstream input(
        "rectangle 0 0 2 3 FF0000 00FF00\n"
        "circle 1 1 1 FFFF00 0000FF\n"
        "triangle 0 0 1 0 0 1 000000 FFFFFF\n"
    );
    vector<shared_ptr<IShape>> shapes;
    REQUIRE_NOTHROW(ReadShapes(input, shapes));
    REQUIRE(shapes.size() == 3);

    SECTION("Неизвестный тип фигуры") {
        istringstream bad("unknown 0 0 1");
        vector<shared_ptr<IShape>> out;
        REQUIRE_THROWS_AS(ReadShapes(bad, out), invalid_argument);
    }
    SECTION("Неправильный формат цвета") {
        istringstream badC("circle 0 0 1 GHIJKL 000000");
        vector<shared_ptr<IShape>> out;
        REQUIRE_THROWS_AS(ReadShapes(badC, out), invalid_argument);
    }
}

// Тесты для утилит поиска максимальной площади и минимального периметра
TEST_CASE("Utils: FindMaxArea и FindMinPerimeter", "[geometry][utils]") {
    vector<shared_ptr<IShape>> shapes;
    shapes.push_back(make_shared<CRectangle>(CPoint(0, 0), 2, 2, 0, 0)); // площадь 4, периметр 8
    shapes.push_back(make_shared<CCircle>(CPoint(0, 0), 1, 0, 0));          // площадь pi, периметр 2pi
    shapes.push_back(make_shared<CTriangle>(CPoint(0, 0), CPoint(1, 0), CPoint(0, 1), 0, 0)); // площадь 0.5, пер

    auto maxArea = FindMaxArea(shapes);
    REQUIRE(maxArea->GetArea() == Approx(4.0));

    auto minPeri = FindMinPerimeter(shapes);
    REQUIRE(minPeri->GetPerimeter() == Approx(2 * M_PI * 1));
}
