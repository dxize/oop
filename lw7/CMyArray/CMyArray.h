#pragma once

#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <utility>
#include <memory>

template <typename T>
class CMyArray 
{
public:
    CMyArray()
        : m_data(nullptr), m_size(0), m_capacity(0) {}

    CMyArray(const CMyArray& other)
        : m_data(nullptr), m_size(0), m_capacity(0) 
    {
        Resize(other.m_size);
        std::copy(other.m_data, other.m_data + m_size, m_data); //утечка памяти(обернуть в рай кетч если что освободить память)
    }

    CMyArray(CMyArray&& other)
        : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity) 
    {
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    CMyArray& operator=(const CMyArray& other) 
    {
        if (this != &other) {
            CMyArray tmp(other);
            Swap(tmp);
        }
        return *this;
    }

    CMyArray& operator=(CMyArray&& other)  
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

    ~CMyArray() noexcept //нужно задестроить
    {
        delete[] m_data;
    }

    void PushBack(const T& value) 
    {
        if (m_size == m_capacity) 
        {
            ResizeBuffer(m_capacity ? m_capacity * 2 : 1);
        }
        m_data[m_size++] = value; 
    }

    void PushBack(T&& value) 
    {
        if (m_size == m_capacity)
        {
            ResizeBuffer(m_capacity ? m_capacity * 2 : 1);
        }
        m_data[m_size++] = std::move(value); 
    }

    void Resize(size_t newSize) 
    {
        if (newSize > m_capacity) 
        {
            ResizeBuffer(newSize);
        }
        for (size_t i = m_size; i < newSize; ++i) 
        {
            m_data[i] = T{};
        }
        m_size = newSize;
    }

    void Clear() noexcept 
    {
        std::destroy_n(m_data, m_size);
        m_size = 0;
    }

    size_t Size() const noexcept 
    {
        return m_size;
    }

    T& operator[](size_t index) 
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Index out of bounds");
        }
        return m_data[index];
    }

    const T& operator[](size_t index) const 
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Index out of bounds");
        }
        return m_data[index];
    }

    T* begin() noexcept 
    { 
        return m_data; 
    }
    T* end() noexcept 
    { 
        return m_data + m_size; 
    }
    const T* begin() const noexcept 
    { 
        return m_data; 
    }
    const T* end() const noexcept 
    { 
        return m_data + m_size; 
    }

    std::reverse_iterator<T*> rbegin() noexcept 
    {
        return std::reverse_iterator<T*>(end());
    }
    std::reverse_iterator<T*> rend() noexcept 
    {
        return std::reverse_iterator<T*>(begin());
    }
    std::reverse_iterator<const T*> rbegin() const noexcept 
    {
        return std::reverse_iterator<const T*>(end());
    }
    std::reverse_iterator<const T*> rend() const noexcept 
    {
        return std::reverse_iterator<const T*>(begin());
    }

private:
    T* m_data;
    size_t m_size;
    size_t m_capacity;

    void ResizeBuffer(size_t newCapacity) 
    {
        if (newCapacity < m_size)
        {
            throw std::runtime_error("New capacity cannot be less than current size.");
        }

        T* newData = new T[newCapacity]; //можно использовать initialized_copy_n 
        for (size_t i = 0; i < m_size; ++i) //можно использовать initialized_copy_n 
        {
            newData[i] = std::move(m_data[i]);
        }
        delete[] m_data;
        m_data = newData;
        m_capacity = newCapacity;
    }

    void Swap(CMyArray& other) noexcept 
    {
        std::swap(m_data, other.m_data);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
    }
};
