#ifndef DATE_H
#define DATE_H

//enum Month {Jan, Feb, Mar, Apr, May, Jun, July, Aug, Sep, Oct, Nov, Dec};

class Date {
    private:
        unsigned int year, month, day;
    public:
        Date();
        Date(unsigned int, unsigned int, unsigned int);
        Date(const Date&);
        ~Date();

        // set functions
        void setDate(unsigned int, unsigned int, unsigned int);
        void setDay(unsigned int);        
        void setMonth(unsigned int);
        void setYear(unsigned int);

        //get functions
        unsigned int getDay() const;
        unsigned int getMonth() const;
        unsigned int getYear() const;

        void printDate() const; // Format dd/mm/yyyy
};

#endif