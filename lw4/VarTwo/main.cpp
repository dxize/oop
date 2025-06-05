//rectangle 100 200 300 200 000000 8B4513
//triangle 100 200 400 200 250 50 000000 8B0000
//rectangle 200 300 100 100 000000 4682B4
//circle 450 100 50 FFFF00 FFFF00
//rectangle 0 400 600 100 000000 00AA00

#include <iostream>
#include <string>
#include <memory>
#include <fstream>

#include <GLFW/glfw3.h>

#include "CShapeManager.h"
#include "IShape.h"
#include "CLineSegment.h"
#include "CCircle.h"
#include "CTriangle.h"
#include "CRectangle.h"

#include "./DrawShapes/ICanvasDrawable.h"
#include "./DrawShapes/ICanvas.h"
#include "./DrawShapes/CCanvas.h"

enum class ShapeType { Line, Circle, Triangle, Rectangle, Unknown };

ShapeType ParseShapeType(const std::string& s)
{
    if (s == "line")      return ShapeType::Line;
    if (s == "circle")    return ShapeType::Circle;
    if (s == "triangle")  return ShapeType::Triangle;
    if (s == "rectangle") return ShapeType::Rectangle;
    return ShapeType::Unknown;
}

std::shared_ptr<IShape> ReadShape(std::istream& in, const std::string& cmd)
{
    using std::stoul;

    switch (ParseShapeType(cmd))
    {
    case ShapeType::Line:
    {
        double x1, y1, x2, y2;
        std::string outlineHex;
        if (!(in >> x1 >> y1 >> x2 >> y2 >> outlineHex))
            throw std::invalid_argument("Invalid line format");
        return std::make_shared<CLineSegment>(
            CPoint{ x1, y1 },
            CPoint{ x2, y2 },
            stoul(outlineHex, nullptr, 16)
        );
    }
    case ShapeType::Circle:
    {
        double x, y, r;
        std::string outlineHex, fillHex;
        if (!(in >> x >> y >> r >> outlineHex >> fillHex))
            throw std::invalid_argument("Invalid circle format");
        return std::make_shared<CCircle>(
            CPoint{ x, y },
            r,
            stoul(outlineHex, nullptr, 16),
            stoul(fillHex, nullptr, 16)
        );
    }
    case ShapeType::Triangle:
    {
        double x1, y1, x2, y2, x3, y3;
        std::string outlineHex, fillHex;
        if (!(in >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> outlineHex >> fillHex))
            throw std::invalid_argument("Invalid triangle format");
        return std::make_shared<CTriangle>(
            CPoint{ x1, y1 },
            CPoint{ x2, y2 },
            CPoint{ x3, y3 },
            stoul(outlineHex, nullptr, 16),
            stoul(fillHex, nullptr, 16)
        );
    }
    case ShapeType::Rectangle:
    {
        double x, y, w, h;
        std::string outlineHex, fillHex;
        if (!(in >> x >> y >> w >> h >> outlineHex >> fillHex))
            throw std::invalid_argument("Invalid rectangle format");
        return std::make_shared<CRectangle>(
            CPoint{ x, y },
            CPoint{ x + w, y + h },
            stoul(outlineHex, nullptr, 16),
            stoul(fillHex, nullptr, 16)
        );
    }
    default:
        throw std::invalid_argument("Unknown shape type: " + cmd);
    }
}

bool IsValidNameInputFile(std::ifstream& inputFile)
{
    if (!inputFile)
    {
        return false;
    }

    return true;
}

void ProcessInput(CShapeManager& manager, std::string& inputFileName)
{
    std::cin >> inputFileName;
    std::ifstream inputFile(inputFileName);

    if (IsValidNameInputFile(inputFile))
    {
        std::string cmd;
        while (inputFile >> cmd)
        {
            try
            {
                auto shape = ReadShape(inputFile, cmd);
                manager.AddShape(shape);
            }
            catch (const std::exception& ex)
            {
                std::cerr << "Error parsing \"" << cmd << "\": "
                    << ex.what() << std::endl;
                std::string skip;
                std::getline(std::cin, skip);
            }
        }
    }
}

void PrintExtrema(const CShapeManager& manager)
{
    if (auto maxArea = manager.FindShapeWithMaxArea())
    {
        std::cout << "Shape with max area:\n"
            << maxArea->ToString() << "\n\n";
    }

    if (auto minPerim = manager.FindShapeWithMinPerimeter())
    {
        std::cout << "Shape with min perimeter:\n"
            << minPerim->ToString() << "\n";
    }
}

GLFWwindow* CreateApplicationWindow() {
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed!\n";
        return nullptr;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Shapes", nullptr, nullptr);
    if (!window) {
        std::cerr << "Window creation failed!\n";
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    return window;
}

// 2. Настройка проекции
void SetupProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 800, 600, 0, -1, 1); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Rendering(GLFWwindow*& window, CShapeManager& manager)
{
    CCanvas canvas;

    // 3) Цикл отрисовки
    while (!glfwWindowShouldClose(window))
    {
        // очистить экран белым
        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        // нарисовать все фигуры
        for (auto& shp : manager.GetShapes())
        {
            if (auto d = std::dynamic_pointer_cast<ICanvasDrawable>(shp))
            {
                d->Draw(canvas);
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void DrawPic(CShapeManager& manager)
{
    GLFWwindow* window = CreateApplicationWindow();

    if (window)
    {
        // Настройка OpenGL
        SetupProjection();

        Rendering(window, manager);

        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

int main()
{
    CShapeManager manager;
    std::string stop;

    while (stop != "exit" && !std::cin.eof() && !std::cin.fail())
    {
        ProcessInput(manager, stop);

        if (manager.GetShapes().empty())
        {
            std::cout << "No valid forms provided or file not found.\n";
            continue;
        }
    }

    manager.PrintAll();
    PrintExtrema(manager);

    DrawPic(manager);

    return 0;
}