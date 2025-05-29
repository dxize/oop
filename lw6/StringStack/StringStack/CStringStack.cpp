#include "CStringStack.h"
#include <algorithm> 

CStringStack::CStringStack() noexcept
    : m_data(nullptr)
    , m_size(0)
    , m_capacity(0)
{}

CStringStack::CStringStack(const CStringStack& other)
    : m_data(nullptr)
    , m_size(0)
    , m_capacity(0)
{
    if (other.m_size > 0) 
    {
        resize_buffer(other.m_size);
        for (size_t i = 0; i < other.m_size; ++i) 
        {
            m_data[i] = other.m_data[i];  
        }
        m_size = other.m_size;
    }
}

CStringStack::CStringStack(CStringStack&& other) noexcept
    : m_data(other.m_data)
    , m_size(other.m_size)
    , m_capacity(other.m_capacity)
{
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}

CStringStack::~CStringStack() noexcept
{
    delete[] m_data;
}

CStringStack& CStringStack::operator=(const CStringStack& other)
{
    if (this != &other) 
    {
        CStringStack tmp(other);
        swap(tmp);
    }
    return *this;
}

CStringStack& CStringStack::operator=(CStringStack&& other) noexcept
{
    if (this != &other) 
    {
        delete[] m_data;
        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }
    return *this;
}

void CStringStack::push(const std::string& s)
{
    if (m_size == m_capacity) 
    {
        resize_buffer(m_capacity ? m_capacity * 2 : 1);
    }
    m_data[m_size++] = s; 
}

void CStringStack::push(std::string&& s)
{
    if (m_size == m_capacity) 
    {
        resize_buffer(m_capacity ? m_capacity * 2 : 1);
    }
    m_data[m_size++] = std::move(s);
}

void CStringStack::pop()
{
    if (empty()) 
    {
        throw StackEmpty();
    }
    m_data[m_size].clear();
    --m_size;
}

const std::string& CStringStack::top() const
{
    if (empty()) 
    {
        throw StackEmpty();
    }
    return m_data[m_size - 1];
}

bool CStringStack::empty() const noexcept
{
    return m_size == 0;
}

size_t CStringStack::size() const noexcept
{
    return m_size;
}

void CStringStack::swap(CStringStack& other) noexcept
{
    std::swap(m_data, other.m_data);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
}

void CStringStack::resize_buffer(size_t newCapacity)
{
    if (newCapacity < m_size) 
    {
        return; 
    }

    std::string* newData = nullptr;
    try 
    {
        newData = new std::string[newCapacity];
    }
    catch (...) 
    {
        throw MemoryError();
    }

    for (size_t i = 0; i < m_size; ++i) 
    {
        newData[i] = std::move(m_data[i]);
    }

    delete[] m_data;
    m_data = newData;
    m_capacity = newCapacity;
}
