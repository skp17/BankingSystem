#ifndef DATE_H
#define DATE_H

using uint = unsigned int;

class Date {
    private:
        uint m_day, m_month, m_year;
    public:
        Date(uint m_day = 1, uint m_month = 1, uint m_year = 1970);
        Date(const Date&);
        ~Date();

        // Format dd/mm/yyyy
        Date &setDate(uint m_day, uint m_month, uint m_year); 

        uint getDay() const;
        uint getMonth() const;
        uint getYear() const;

        void printDate() const; // Format dd/mm/yyyy
};

#endif