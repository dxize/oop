#pragma once

#include <vector>
#include <memory>
#include "CBody.h"

class CBodyManager 
{
public:
    // Добавить тело в менеджер
    void AddBody(const std::shared_ptr<CBody>& body);

    // Вывести в консоль информацию обо всех телах
    void PrintAll() const;

    // Найти тело с максимальной массой
    std::shared_ptr<CBody> FindMaxMass() const;

    // Найти тело с минимальным "весом в воде"
    std::shared_ptr<CBody> FindMinWeightInWater() const;

private:
    std::vector<std::shared_ptr<CBody>> m_bodies;
};
