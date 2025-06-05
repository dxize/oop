#include "CMyString.h"
#include <algorithm> 
#include <cassert>
#include <cstring>    
#include <utility>    

const char CMyString::EMPTYSTRING[1] = { '\0' }; //для чего нам выделять отдельно строку эмптистринг

void CMyString::dataAcquisition(const char* pString, size_t length)
{
    m_capacity = length;
    m_length = length;
    m_data = new char[m_capacity + 1];
    std::memcpy(m_data, pString, length);
    m_data[m_length] = '\0';
}

void CMyString::reserve(size_t newCapacity)
{
    if (newCapacity <= m_capacity) 
    {
        return;
    }
    char* newBuf = new char[newCapacity + 1];
    if (m_length > 0) 
    {
        std::memcpy(newBuf, m_data, m_length);
    }
    newBuf[m_length] = '\0';

    if (m_data != EMPTYSTRING) 
    {
        delete[] m_data;
    }
    m_data = newBuf;
    m_capacity = newCapacity;
}

void CMyString::destroyData()
{
    if (m_data != nullptr && m_data != EMPTYSTRING) 
    {
        delete[] m_data;
    }
    m_data = const_cast<char*>(EMPTYSTRING);
    m_length = 0;
    m_capacity = 0;
}

CMyString::CMyString()
    : m_data(const_cast<char*>(EMPTYSTRING))
    , m_length(0)
    , m_capacity(0)
{}

CMyString::CMyString(const char* pString)
    : m_data(const_cast<char*>(EMPTYSTRING))
    , m_length(0)
    , m_capacity(0)
{
    if (pString == nullptr) 
    {
        return;
    }
    size_t len = 0;
    while (pString[len] != '\0') 
    {
        ++len;
    }
    if (len == 0) 
    {
        return;
    }
    dataAcquisition(pString, len);
}

CMyString::CMyString(const char* pString, size_t length)
    : m_data(const_cast<char*>(EMPTYSTRING))
    , m_length(0)
    , m_capacity(0)
{
    if (pString == nullptr || length == 0) 
    {
        return;
    }
    dataAcquisition(pString, length);
}

CMyString::CMyString(const CMyString& other)
    : m_data(const_cast<char*>(EMPTYSTRING))
    , m_length(0)
    , m_capacity(0)
{
    if (other.m_length == 0) 
    {
        return;
    }
    dataAcquisition(other.m_data, other.m_length);
}


CMyString::CMyString(CMyString&& other) noexcept
    : m_data(other.m_data)
    , m_length(other.m_length)
    , m_capacity(other.m_capacity)
{
    other.m_data = const_cast<char*>(EMPTYSTRING);
    other.m_length = 0;
    other.m_capacity = 0;
}

CMyString::CMyString(const std::string& stlString)
    : m_data(const_cast<char*>(EMPTYSTRING))
    , m_length(0)
    , m_capacity(0)
{
    if (stlString.size() == 0) 
    {
        return;
    }

    dataAcquisition(stlString.data(), stlString.size());
}

CMyString::~CMyString()
{
    destroyData();
}

CMyString& CMyString::operator=(const CMyString& other)
{
    if (this == &other) 
    {
        return *this; 
    }
    destroyData();

    if (other.m_length == 0) 
    {
        return *this;
    }

    dataAcquisition(other.m_data, other.m_length);
    return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
    if (this == &other) 
    {
        return *this;
    }
 
    destroyData();

    m_data = other.m_data;
    m_length = other.m_length;
    m_capacity = other.m_capacity;
    
    other.m_data = const_cast<char*>(EMPTYSTRING);
    other.m_length = 0;
    other.m_capacity = 0;
    return *this;
}


size_t CMyString::GetLength() const
{
    return m_length;
}

const char* CMyString::GetStringData() const
{
    return m_data;
}

size_t CMyString::GetCapacity() const
{
    return m_capacity;
}


CMyString CMyString::SubString(size_t start, size_t length) const
{
    if (!length)
    {
        length = SIZE_MAX;
    }
    if (start >= m_length) 
    {
        return CMyString();
    }
    size_t maxAllowed = m_length - start;
    size_t actualLen = (length == SIZE_MAX) ? maxAllowed : std::min(maxAllowed, length);
    return CMyString(m_data + start, actualLen);
}

void CMyString::Clear()
{
    m_length = 0;
    m_data[0] = '\0';
}


CMyString& CMyString::operator+=(const CMyString& rhs)
{
    if (rhs.m_length == 0) 
    {
        return *this; 
    }
    size_t needed = m_length + rhs.m_length;
    if (needed > m_capacity) 
    {
        size_t newCap = std::max(size_t{ 1 }, m_capacity);
        while (newCap < needed) 
        {
            newCap *= 2;
        }
        reserve(newCap);
    }

    std::memcpy(m_data + m_length, rhs.m_data, rhs.m_length);
    m_length += rhs.m_length;
    return *this;
}

CMyString operator+(const CMyString& lhs, const CMyString& rhs)
{
    CMyString result(lhs);
    result += rhs;
    return result;
}

CMyString operator+(const std::string& lhs, const CMyString& rhs)
{
    CMyString temp(lhs);
    temp += rhs;
    return temp;
}

CMyString operator+(const char* lhs, const CMyString& rhs)
{
    CMyString temp(lhs);
    temp += rhs;
    return temp;
}

bool CMyString::operator==(const CMyString& other) const
{
    if (m_length != other.m_length) 
    {
        return false;
    }

    return std::memcmp(m_data, other.m_data, m_length) == 0;
}

bool CMyString::operator!=(const CMyString& other) const
{
    return !(*this == other);
}

bool CMyString::operator<(const CMyString& other) const
{
    size_t minLen = std::min(m_length, other.m_length);
    int cmp = std::memcmp(m_data, other.m_data, minLen);
    if (cmp < 0) 
    {
        return true;
    }
    if (cmp > 0) 
    {
        return false;
    }
    return (m_length < other.m_length);
}

bool CMyString::operator>(const CMyString& other) const
{
    return other < *this;
}

bool CMyString::operator<=(const CMyString& other) const
{
    return !(*this > other);
}

bool CMyString::operator>=(const CMyString& other) const
{
    return !(*this < other);
}

char& CMyString::operator[](size_t index)
{
    assert(index < m_length);
    return m_data[index];
}

const char& CMyString::operator[](size_t index) const
{
    assert(index < m_length);
    return m_data[index];
}

std::ostream& operator<<(std::ostream& os, const CMyString& str)
{
    if (str.m_length > 0) 
    {
        os.write(str.m_data, str.m_length);
    }
    return os;
}

std::istream& operator>>(std::istream& is, CMyString& str)
{
    std::string temp;
    if (!(is >> temp)) 
    {
        str.destroyData();
        is.setstate(std::ios::failbit);
        return is;
    }
    str = CMyString(temp);
    return is;
}
