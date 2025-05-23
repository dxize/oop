#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>
#include "CStringStack.h"

CStringStack::CStringStack() noexcept
    : m_data(nullptr), m_size(0), m_capacity(0) {}

CStringStack::CStringStack(const CStringStack& other)
    : m_data(nullptr), m_size(0), m_capacity(0) 
{
    if (other.m_size > 0) 
    {
        std::string* tmp = allocate_and_copy(other.m_data, other.m_size, other.m_capacity);
        m_data = tmp;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
    }
}

CStringStack::CStringStack(CStringStack&& other) noexcept
    : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity) 
{
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}

CStringStack::CStringStack::~CStringStack() noexcept 
{
    destroy_data();
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
        destroy_data();
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
    ensure_capacity(m_size + 1);
    try
    {
        new (&m_data[m_size]) std::string(s);
    }
    catch (...)
    {
        throw;
    }
    ++m_size;
}

void CStringStack::push(std::string&& s)
{
    if (m_size == m_capacity)
    {
        ensure_capacity(m_size + 1);
    }
    new (&m_data[m_size]) std::string(std::move(s));
    ++m_size;
}


void CStringStack::pop() 
{
    if (empty()) 
    {
        throw StackEmpty();
    }
    --m_size;
    m_data[m_size].~basic_string();
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

std::string* CStringStack::allocate_and_copy(const std::string* src, size_t size, size_t capacity)
{
    std::string* buffer = static_cast<std::string*>(::operator new[](capacity * sizeof(std::string)));

    size_t i = 0;
    try 
    {
        for (; i < size; ++i) 
        {
            new (&buffer[i]) std::string(src[i]);
        }
    }
    catch (...) 
    {
        for (size_t j = 0; j < i; ++j)
        {
            buffer[j].~basic_string();
        }
        ::operator delete[](buffer);
        throw MemoryError();
    }

    return buffer;
}


void CStringStack::ensure_capacity(size_t minCapacity)  //переименовать функции и одумать более / поправить форматирвоание
{
    if (minCapacity <= m_capacity)
    {
        return;
    }

    size_t newCap = (m_capacity == 0 ? 1 : m_capacity * 2);

    if (newCap < minCapacity)
    {
        newCap = minCapacity;
    }
    std::string* newData = allocate_and_copy(m_data, m_size, newCap);
    size_t old_size = m_size;
    destroy_data();
    m_data = newData;
    m_size = old_size;
    m_capacity = newCap;
}

void CStringStack::destroy_data() noexcept 
{   
    if (m_data) 
    {
        for (size_t i = 0; i < m_size; ++i) 
        {
            m_data[i].~basic_string();
        }
        ::operator delete[](m_data);
    }
    m_data = nullptr;
    m_size = 0;
    m_capacity = 0;
}
