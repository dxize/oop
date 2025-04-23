#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "CBody.h"

class CBodyManager {
public:
    // �������� ���� � ��������
    void AddBody(const std::shared_ptr<CBody>& body) {
        if (!body) {
            throw std::invalid_argument("Cannot add null body");
        }
        m_bodies.push_back(body);
    }

    // ������� � ������� ���������� ��� ���� �����
    void PrintAll() const {
        for (const auto& b : m_bodies) {
            std::cout << b->ToString() << "\n\n";
        }
    }

    // ����� ���� � ������������ ������
    std::shared_ptr<CBody> FindMaxMass() const {
        if (m_bodies.empty()) {
            return nullptr;
        }
        auto it = std::max_element(
            m_bodies.begin(), m_bodies.end(),
            [](auto& a, auto& b) { return a->GetMass() < b->GetMass(); }
        );
        return *it;
    }

    // ����� ���� � ����������� "����� � ����"
    std::shared_ptr<CBody> FindMinWeightInWater() const {
        if (m_bodies.empty()) {
            return nullptr;
        }
        constexpr double waterDensity = 1000.0;
        auto it = std::min_element(
            m_bodies.begin(), m_bodies.end(),
            [waterDensity](auto& a, auto& b) {
                double wa = a->GetMass() - waterDensity * a->GetVolume();
                double wb = b->GetMass() - waterDensity * b->GetVolume();
                return wa < wb;
            }
        );
        return *it;
    }

private:
    std::vector<std::shared_ptr<CBody>> m_bodies;
};
