#include <iostream>
#include <string>
#include <memory>

#include "CShapeManager.h"
#include "IShape.h"
#include "CLineSegment.h"
#include "CCircle.h"
#include "CTriangle.h"
#include "CRectangle.h"

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

void ProcessInput(CShapeManager& manager)
{
    std::string cmd;
    while (std::cin >> cmd)
    {
        try
        {
            auto shape = ReadShape(std::cin, cmd);
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

int main()
{
    CShapeManager manager;

    ProcessInput(manager);

    if (manager.GetShapes().empty())
    {
        std::cout << "No valid shapes provided.\n";
        return 0;
    }

    manager.PrintAll();
    std::cout << "\n";

    PrintExtrema(manager);

    return 0;
}
