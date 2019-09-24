#ifndef DATE_H
#define DATE_H

using uint = unsigned int;

class Date {
    private:
        uint day, month, year;
    public:
        Date(uint day = 1, uint month = 1, uint year = 1970);
        Date(const Date&);
        ~Date();

        // Format dd/mm/yyyy
        Date &setDate(uint day, uint month, uint year); 

        uint getDay() const;
        uint getMonth() const;
        uint getYear() const;

        void printDate() const; // Format dd/mm/yyyy
};

#endif