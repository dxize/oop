#pragma once

#include <cstddef>   
#include <string>
#include <iostream>

class CMyString
{
public:
    CMyString();
    CMyString(const char* pString);
    CMyString(const char* pString, size_t length);
    CMyString(const CMyString& other);
    CMyString(CMyString&& other) noexcept;
    CMyString(const std::string& stlString);
    ~CMyString();

    CMyString& operator=(const CMyString& other);
    CMyString& operator=(CMyString&& other) noexcept;

    size_t GetLength() const;
    const char* GetStringData() const;
    size_t GetCapacity() const;

    CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
    void Clear();

    CMyString& operator+=(const CMyString& rhs);

    friend CMyString operator+(const CMyString& lhs, const CMyString& rhs);
    friend CMyString operator+(const std::string& lhs, const CMyString& rhs);
    friend CMyString operator+(const char* lhs, const CMyString& rhs);


    bool operator==(const CMyString& other) const;
    bool operator!=(const CMyString& other) const;
    bool operator< (const CMyString& other) const;
    bool operator> (const CMyString& other) const;
    bool operator<=(const CMyString& other) const;
    bool operator>=(const CMyString& other) const;

    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const CMyString& str);
    friend std::istream& operator>>(std::istream& is, CMyString& str);

private:
    char* m_data = nullptr;
    size_t m_length = 0;
    size_t m_capacity = 0;

    static const char EMPTYSTRING[1];

    void dataAcquisition(const char* pString, size_t length);
    void reserve(size_t newCapacity);
    void destroyData();
};
