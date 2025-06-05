#pragma once
 
#include <iostream>
#include <sstream>

enum class Month
{
    JANUARY = 1, FEBRUARY, MARCH, APRIL,
    MAY, JUNE, JULY, AUGUST, SEPTEMBER,
    OCTOBER, NOVEMBER, DECEMBER
};

enum class WeekDay
{
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
    THURSDAY, FRIDAY, SATURDAY
};

class CDate
{
public:
    CDate(unsigned day, Month month, unsigned year);
    explicit CDate(unsigned timestamp);
    CDate();

    unsigned GetDay() const;
    Month GetMonth() const;
    unsigned GetYear() const;
    WeekDay GetWeekDay() const;

    bool IsValid() const;

    CDate& operator++();
    CDate operator++(int);

    CDate& operator--();
    CDate operator--(int);

    CDate operator+(long days) const;
    friend CDate operator+(long days, const CDate& d);

    CDate operator-(long days) const;
    long operator-(const CDate& o) const;

    CDate& operator+=(long days);
    CDate& operator-=(long days);

    bool operator==(const CDate& o) const;
    bool operator!=(const CDate& o) const;
    bool operator<(const CDate& o) const;
    bool operator>(const CDate& o) const;
    bool operator<=(const CDate& o) const;
    bool operator>=(const CDate& o) const;

    friend std::ostream& operator<<(std::ostream& os, const CDate& d);
    friend std::istream& operator>>(std::istream& is, CDate& d);

private:
    long m_days;
    bool m_valid;

    static constexpr int MIN_YEAR = 1970;
    static constexpr int MAX_YEAR = 9999;

    static bool isLeap(int y);
    static int daysInMonth(int m, int y);
    static long dateToDays(int d, int m, int y);
    static long daysBeforeYear(int Y);
    static void daysToDate(long days, int& d, int& m, int& y);
    static long maxDays();
};
