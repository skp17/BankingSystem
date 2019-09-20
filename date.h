#ifndef DATE_H
#define DATE_H

using uint = unsigned int;

class Date {
    private:
        uint year, month, day;
    public:
        Date(uint = 0, uint = 0, uint = 0);
        Date(const Date&);
        ~Date();

        // set functions
        void setDate(uint, uint, uint); // Format dd/mm/yyyy
        Date &setDay(uint);        
        Date &setMonth(uint);
        Date &setYear(uint);

        //get functions
        uint getDay() const;
        uint getMonth() const;
        uint getYear() const;

        void printDate() const; // Format dd/mm/yyyy
};

#endif