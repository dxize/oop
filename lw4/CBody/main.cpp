#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>

#include "CBody.h"
#include "CSphere.h"
#include "CParallelepiped.h"
#include "CCone.h"
#include "CCylinder.h"
#include "CCompound.h"
#include "CBodyManager.h"

enum class BodyType { Sphere, Parallelepiped, Cone, Cylinder, Compound, Unknown };

BodyType parseBodyType(const std::string& s) 
{
    if (s == "Sphere")         return BodyType::Sphere;
    if (s == "Parallelepiped") return BodyType::Parallelepiped;
    if (s == "Cone")           return BodyType::Cone;
    if (s == "Cylinder")       return BodyType::Cylinder;
    if (s == "Compound")       return BodyType::Compound;
    return BodyType::Unknown;
}

std::shared_ptr<CBody> ReadBody(std::istream& in, const std::string& cmd, const std::vector<std::shared_ptr<CBody>>& tempList) 
{
    switch (parseBodyType(cmd)) 
    {
    case BodyType::Sphere: 
    {
        double r, d; in >> r >> d;
        return std::make_shared<CSphere>(r, d);
    }
    case BodyType::Parallelepiped: 
    {
        double w, h, dp, dens; in >> w >> h >> dp >> dens;
        return std::make_shared<CParallelepiped>(w, h, dp, dens);
    }
    case BodyType::Cone: 
    {
        double r, h, dens; in >> r >> h >> dens;
        return std::make_shared<CCone>(r, h, dens);
    }
    case BodyType::Cylinder: 
    {
        double r, h, dens; in >> r >> h >> dens;
        return std::make_shared<CCylinder>(r, h, dens);
    }
    case BodyType::Compound: 
    {
        int N; in >> N;
        auto compound = std::make_shared<CCompound>();
        for (int i = 0; i < N; ++i) 
        {
            int idx; in >> idx;
            if (idx < 1 || idx > static_cast<int>(tempList.size())) 
            {
                throw std::out_of_range("Bad index for Compound");
            }
            compound->AddChildBody(tempList[idx - 1]);
        }
        return compound;
    }
    default:
        throw std::invalid_argument("Unknown command: " + cmd);
    }
}

void PrintResults(const CBodyManager& manager) 
{

    manager.PrintAll();

    auto maxMassBody = manager.FindMaxMass();
    if (maxMassBody) 
    {
        std::cout << "\nMax mass body:\n" << maxMassBody->ToString() << "\n";
    }

    auto minWeightBody = manager.FindMinWeightInWater();
    if (minWeightBody) 
    {
        std::cout << "\nMin weight-in-water body:\n" << minWeightBody->ToString() << "\n";
    }
}

void ProcessInputLoop(CBodyManager& manager, std::vector<std::shared_ptr<CBody>>& tempList) 
{
    std::string cmd;
    while (std::cin >> cmd) 
    {
        try 
        {
            auto body = ReadBody(std::cin, cmd, tempList);
            manager.AddBody(body);
            tempList.push_back(body);
        }
        catch (const std::exception& e) 
        {
            std::cerr << "Error processing command \"" << cmd << "\": " << e.what() << "\n";
        }
    }
}


int main() 
{
    CBodyManager manager;
    std::vector<std::shared_ptr<CBody>> tempList;
    std::string cmd;

    ProcessInputLoop(manager, tempList);
    PrintResults(manager);

    return 0;
}
