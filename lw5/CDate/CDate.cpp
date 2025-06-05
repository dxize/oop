#include "CDate.h"
#include <iomanip>  
#include <sstream>


CDate::CDate(unsigned day, Month month, unsigned year) //сделать лучше(валидацию через фроу)
{
    m_valid = true;
    if (year < MIN_YEAR || year > MAX_YEAR)
    {
        m_valid = false;
    }
    int m = static_cast<int>(month);
    if (m < 1 || m > 12) // вынести месяцы в константы
    {
        m_valid = false;
    }
    if (day < 1 || (m_valid && day > static_cast<unsigned>(daysInMonth(m, year))))
    {
        m_valid = false;
    }
    if (m_valid)
    {
        m_days = dateToDays(static_cast<int>(day), m, static_cast<int>(year));
    }
    else
    {
        m_days = 0;
    }
}

CDate::CDate(unsigned timestamp)
{
    if (timestamp <= static_cast<unsigned>(maxDays()))
    {
        m_valid = true;
        m_days = static_cast<long>(timestamp);
    }
    else
    {
        m_valid = false;
        m_days = 0;
    }
}

CDate::CDate()
    : m_days(0), m_valid(true)
{}


unsigned CDate::GetDay() const
{
    if (!m_valid)
    {
        return 0;
    }
    int d, m, y;
    daysToDate(m_days, d, m, y);
    return static_cast<unsigned>(d);
}

Month CDate::GetMonth() const
{
    if (!m_valid)
    {
        return static_cast<Month>(0);
    }
    int d, m, y;
    daysToDate(m_days, d, m, y);
    return static_cast<Month>(m);
}

unsigned CDate::GetYear() const
{
    if (!m_valid)
    {
        return 0;
    }
    int d, m, y;
    daysToDate(m_days, d, m, y);
    return static_cast<unsigned>(y);
}

WeekDay CDate::GetWeekDay() const
{
    if (!m_valid)
    {
        return static_cast<WeekDay>(-1);
    }
    int wd = static_cast<int>((4 + m_days) % 7);
    return static_cast<WeekDay>(wd);
}

bool CDate::IsValid() const
{
    return m_valid;
}


CDate& CDate::operator++()
{
    if (m_valid)
    {
        if (m_days + 1 > maxDays())
        {
            m_valid = false;
        }
        else
        {
            ++m_days;
        }
    }
    return *this;
}

CDate CDate::operator++(int)
{
    CDate temp = *this;
    ++(*this);
    return temp;
}

CDate& CDate::operator--()
{
    if (m_valid)
    {
        if (m_days - 1 < 0)
        {
            m_valid = false;
        }
        else
        {
            --m_days;
        }
    }
    return *this;
}

CDate CDate::operator--(int)
{
    CDate temp = *this;
    --(*this);
    return temp;
}


CDate CDate::operator+(long days) const
{
    if (!m_valid)
    {
        CDate result;
        result.m_valid = false;
        return result;
    }
    long nd = m_days + days;
    if (nd < 0 || nd > maxDays())
    {
        CDate result;
        result.m_valid = false;
        return result;
    }
    return CDate(static_cast<unsigned>(nd));
}

CDate operator+(long days, const CDate& d)
{
    return d + days;
}

CDate CDate::operator-(long days) const
{
    return *this + (-days);
}

long CDate::operator-(const CDate& o) const
{
    if (!m_valid || !o.m_valid)
    {
        return 0;
    }
    return m_days - o.m_days;
}

CDate& CDate::operator+=(long days)
{
    *this = *this + days;
    return *this;
}

CDate& CDate::operator-=(long days)
{
    *this = *this - days;
    return *this;
}


bool CDate::operator==(const CDate& o) const
{
    return m_valid && o.m_valid && m_days == o.m_days;
}

bool CDate::operator!=(const CDate& o) const
{
    return !(*this == o);
}

bool CDate::operator<(const CDate& o) const
{
    return m_valid && o.m_valid && m_days < o.m_days;
}

bool CDate::operator>(const CDate& o) const
{
    return o < *this;
}

bool CDate::operator<=(const CDate& o) const
{
    return !(*this > o);
}

bool CDate::operator>=(const CDate& o) const 
{
    return !(*this < o);
}

//использовать operator<=> (спейс шип)

std::ostream& operator<<(std::ostream& os, const CDate& d)
{
    if (!d.m_valid)
    {
        os << "INVALID";
    }
    else
    {
        int day, mon, year;
        CDate::daysToDate(d.m_days, day, mon, year);
        os << std::setw(2) << std::setfill('0') << day << "."
            << std::setw(2) << std::setfill('0') << mon << "."
            << std::setw(4) << std::setfill('0') << year;
    }
    return os;
}

std::istream& operator>>(std::istream& is, CDate& d)
{
    unsigned day, mon, year;
    char dot1, dot2;
    if (is >> day >> dot1 >> mon >> dot2 >> year
        && dot1 == '.' && dot2 == '.')
    {
        CDate temp(day, static_cast<Month>(mon), year);
        if (temp.IsValid())
        {
            d = temp;
        }
        else
        {
            d.m_valid = false;
        }
    }
    else
    {
        d.m_valid = false;
        is.setstate(std::ios::failbit);
    }
    return is;
}

bool CDate::isLeap(int y) //подумать как объединить с daysBeforeYear --> leapsUpTo()
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int CDate::daysInMonth(int m, int y)
{
    static int dm[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if (m == 2 && isLeap(y))
    {
        return 29;
    }
    return dm[m];
}

long CDate::daysBeforeYear(int Y)
{
    long years = (long)Y - MIN_YEAR; 
    auto leapsUpTo = [](int N) 
    {
        return N / 4 - N / 100 + N / 400;
    };
    long leaps = leapsUpTo(Y - 1) - leapsUpTo(MIN_YEAR - 1);
    return years * 365 + leaps;
}

long CDate::dateToDays(int d, int m, int y)
{
    long days = daysBeforeYear(y);

    for (int mm = 1; mm < m; ++mm)
    {
        days += daysInMonth(mm, y);
    }

    days += (d - 1);

    return days;
}

void CDate::daysToDate(long days, int& d, int& m, int& y)
{
    int yearCandidate = static_cast<int>(MIN_YEAR + days / 365); //приблизительно

    long dbf = daysBeforeYear(yearCandidate);

    while (dbf > days) 
    {
        --yearCandidate;
        dbf = daysBeforeYear(yearCandidate);
    }

    long daysInThisYear = isLeap(yearCandidate) ? 366 : 365;
    while (dbf + daysInThisYear <= days) 
    {
        dbf += daysInThisYear;
        ++yearCandidate;
        daysInThisYear = isLeap(yearCandidate) ? 366 : 365;
    }

    y = yearCandidate;

    long dayOfYear = days - dbf;

    int month = 1;
    while (true) 
    {
        int dim = daysInMonth(month, yearCandidate);
        if (dayOfYear < dim) 
        {
            break;
        }
        dayOfYear -= dim;
        ++month;
    }
    m = month;

    d = static_cast<int>(dayOfYear) + 1;
}//наименование dbf и dim изменить

long CDate::maxDays()
{
    return dateToDays(31, 12, MAX_YEAR);
}
