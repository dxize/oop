#pragma once

#include <string>
#include <exception>
#include <utility>

struct StackEmpty : public std::exception
{
    const char* what() const noexcept override;
};

struct MemoryError : public std::bad_alloc
{
    const char* what() const noexcept override;
};

class CStringStack
{
public:
    CStringStack() noexcept;
    CStringStack(const CStringStack& other);
    CStringStack(CStringStack&& other) noexcept;
    ~CStringStack() noexcept;

    CStringStack& operator=(const CStringStack& other);
    CStringStack& operator=(CStringStack&& other) noexcept;

    void push(const std::string& s);
    void push(std::string&& s);
    void pop();
    const std::string& top() const;
    bool empty() const noexcept;
    size_t size() const noexcept;

    void swap(CStringStack& other) noexcept;

private:
    std::string* m_data;
    size_t  m_size;
    size_t  m_capacity;

    void resize_buffer(size_t newCapacity);
};
