#ifndef DATE_H
#define DATE_H

#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>

using namespace std;
using uint = unsigned int;

class Date {
    private:
        uint m_day, m_month, m_year;

        friend class boost::serialization::access;
        template<class Archive>
        void save(Archive &ar, const uint version /* file_version */) const {
            // Version is always the latest when saving
            ar & m_day; 
            ar & m_month;
            ar & m_year;
        }
        template<class Archive>
        void load(Archive &ar, const uint version) {
            ar & m_day; 
            ar & m_month;
            ar & m_year;

            // Add new data members here in future version
            // if(version > 0)
        }
        BOOST_SERIALIZATION_SPLIT_MEMBER()
        
    public:
        Date(uint m_day = 1, uint m_month = 1, uint m_year = 1970);
        Date(const Date&);
        ~Date();

        // Format dd/mm/yyyy
        bool setDate(uint m_day, uint m_month, uint m_year);

        uint getDay() const;
        uint getMonth() const;
        uint getYear() const;

        void printDate() const; // Format dd/mm/yyyy
};

BOOST_CLASS_VERSION(Date, 0)

#endif /* DATE_H */