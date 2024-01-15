#include <iostream>

using namespace std;

class Date {
public:
    int year_standard{1960};
    int month_standard{1};
    int day_standard{1};
    int hour_standard{0};
    int minute_standard{0};
    int second_standard{0};
    bool isOurEra{true};

    Date() {}

    Date(int year, int month, int day_standard, int hour, int minute, int second, bool isOurEra_) {
        this->year_standard = year;
        this->month_standard = month;
        this->day_standard = day_standard;
        this->hour_standard = hour;
        this->minute_standard = minute;
        this->second_standard = second;
        this->isOurEra = isOurEra_;
        normalizeDate();
    }

    Date(const Date& other) {
        year_standard = other.year_standard;
        month_standard = other.month_standard;
        day_standard = other.day_standard;
        hour_standard = other.hour_standard;
        minute_standard = other.minute_standard;
        second_standard = other.second_standard;
        isOurEra = other.isOurEra;
    }

    Date& operator=(const Date& other) {
        this->year_standard = other.year_standard;
        this->month_standard = other.month_standard;
        this->day_standard = other.day_standard;
        this->hour_standard = other.hour_standard;
        this->minute_standard = other.minute_standard;
        this->second_standard = other.second_standard;
        this->isOurEra = other.isOurEra;

        return *this;
    }

    Date& operator+=(const Date& other) {
        this->year_standard += other.year_standard;
        this->month_standard += other.month_standard;
        this->day_standard += other.day_standard;
        this->hour_standard += other.hour_standard;
        this->minute_standard += other.minute_standard;
        this->second_standard += other.second_standard;
        normalizeDate();
        return *this;
    }

    Date operator+(const Date& other) {
        Date date_result = *this;
        date_result.normalizeDate();
        return date_result += other;
    }

    Date& operator-=(const Date& other) {
        this->year_standard -= other.year_standard;
        this->month_standard -= other.month_standard;
        this->day_standard -= other.day_standard;
        this->hour_standard -= other.hour_standard;
        this->minute_standard -= other.minute_standard;
        this->second_standard -= other.second_standard;
        normalizeDate();
        return *this;
    }

    Date operator-(const Date& other) {
        Date date_result = *this;
        date_result.normalizeDate();
        return date_result -= other;
    }

    bool operator<(const Date& other) {
        if (isOurEra != other.isOurEra) return isOurEra > other.isOurEra;
        else if (year_standard != other.year_standard) return year_standard < other.year_standard;
        else if (month_standard != other.month_standard) return month_standard < other.month_standard;
        else if (day_standard != other.day_standard) return day_standard < other.day_standard;
        else if (hour_standard != other.hour_standard) return hour_standard < other.hour_standard;
        else if (minute_standard != other.minute_standard) return minute_standard < other.minute_standard;
        else if (second_standard != other.second_standard) return second_standard < other.second_standard;
        else return false;
    }

    bool operator>(const Date& other) {
        if (isOurEra != other.isOurEra) return isOurEra > other.isOurEra;
        else if (year_standard != other.year_standard) return year_standard > other.year_standard;
        else if (month_standard != other.month_standard) return month_standard > other.month_standard;
        else if (day_standard != other.day_standard) return day_standard > other.day_standard;
        else if (hour_standard != other.hour_standard) return hour_standard > other.hour_standard;
        else if (minute_standard != other.minute_standard) return minute_standard > other.minute_standard;
        else if (second_standard != other.second_standard) return second_standard > other.second_standard;
        else return false;
    }

    bool operator==(const Date& other) {
        return ((year_standard == other.year_standard) &&
                (month_standard == other.month_standard) &&
                (day_standard == other.day_standard) &&
                (hour_standard == other.hour_standard) &&
                (minute_standard == other.minute_standard) &&
                (second_standard == other.second_standard) &&
                (isOurEra == other.isOurEra));
    }

    friend ostream& operator<<(ostream& os, const Date& date) {
        bool flag = date.isOurEra;
        os << date.year_standard << " " << date.month_standard << " " << date.day_standard << ", "
           << date.hour_standard << ":" << date.minute_standard << ":" << date.second_standard;
        if (flag == true) os << " Нашей эры";
        else os << " До нашей эры";
        return os;
    }

    Date add(int year, int month, int day_standard, int hour, int minute, int second) {
        Date date_result = *this;
        date_result.year_standard += year;
        date_result.month_standard += month;
        date_result.day_standard += day_standard;
        date_result.hour_standard += hour;
        date_result.minute_standard += minute;
        date_result.second_standard += second;
        date_result.normalizeDate();
        return date_result;
    }

    Date subtract(int year, int month, int day_standard, int hour, int minute, int second) {
        Date date_result = *this;
        date_result.year_standard -= year;
        date_result.month_standard -= month;
        date_result.day_standard -= day_standard;
        date_result.hour_standard -= hour;
        date_result.minute_standard -= minute;
        date_result.second_standard -= second;
        date_result.normalizeDate();
        return date_result;
    }

     bool leap_Year(int year) {
        if (year % 4 != 0) {
            return false;
        } else if (year % 100 != 0) {
            return true;
        } else if (year % 400 != 0) {
            return false;
        } else {
            return true;
        }
    }

    int days_in_month(int year_standard, int month_standard) {
        if (month_standard == 1 || month_standard == 3 || month_standard == 5 || month_standard == 7 || month_standard == 8 || month_standard == 10 || month_standard == 12) {
            return 31;
        } else if (month_standard == 4 || month_standard == 6 || month_standard == 9 || month_standard == 11) {
            return 30;
        } else if (month_standard == 2) {
            return leap_Year(year_standard) ? 29 : 28;
        } else {
            return 0;
        }
    }

    void normalizeDate() {
        if(isOurEra && day_standard == 0){
            day_standard++;
        }
        if(isOurEra && month_standard == 0){
            month_standard++;
        }
        if(isOurEra && year_standard == 0){
            year_standard++;
        }
        if(!isOurEra && day_standard == 0){
            day_standard++;
        }
        if(!isOurEra && month_standard == 0){
            month_standard++;
        }
        if(!isOurEra && year_standard == 0){
            year_standard++;
        }
        while (month_standard > 12) {
            month_standard -= 12;
            year_standard++;
        }
        while (month_standard <= 0) {
            month_standard += 12;
            year_standard--;
        }
        while (day_standard > days_in_month(year_standard, month_standard)) {
            day_standard -= days_in_month(year_standard, month_standard);
            month_standard++;
        }
        if (day_standard <= 0) {
            month_standard--;
            day_standard += days_in_month(year_standard, month_standard);
        }
        while (hour_standard >= 24) {
            hour_standard -= 24;
            day_standard++;
        }
        while (hour_standard < 0) {
            hour_standard += 24;
            day_standard--;
        }
        while (minute_standard >= 60) {
            minute_standard -= 60;
            hour_standard++;
        }
        while (minute_standard < 0) {
            minute_standard += 60;
            hour_standard--;
        }
        while (second_standard < 0) {
            second_standard += 60;
            minute_standard--;
        }
        if (year_standard < 0){
            isOurEra = false;
            year_standard = abs(year_standard);
        }
    }

    

};

int main() {
    /*Date date1;
    Date date2(2004, 9, 9, 12, 0, 61, 1);
    cout << date1 << endl;
    cout << date2 << endl;
    date1+=date2;
    cout << date1 << endl;
    date1 = date2;
    cout << date1 << endl;
    cout << date2 << endl;
    Date date3(2014, 9, 9, 12, 5, 0, 1);
    Date date4(date3);
    cout << date4 << endl;
    date4 = date4.add(1,5,0,2,0,0);
    cout << date4 << endl;
    Date date5(2004, 9, 9, 12, 0, 0, 1);
    Date date6(2014, 9, 9, 12, 0, 0, 1);
    cout<<(date5>date6)<<endl;
    cout<<(date5<date6)<<endl;
    cout<<(date6>date5)<<endl;
    cout<<(date6<date5)<<endl;
    Date date7(2004, 9, 9, 12, 0, 0, 1);
    cout<<endl;
    cout<<(date5==date7)<<endl;
    cout<<(date6==date5)<<endl;
    date3+=date7;
    cout << date3 << endl;
    Date data8(2004, 9, 9, 12, 0, 61, 1);
    Date data9(2004, 9, 9, 12, 0, 61, 1);
    cout<<data8-data9<<endl;*/

    Date d1;
    cout << d1  << endl;
    Date d2(2060, 1, 1, 0, 0, 0, true);
    cout << (d1 > d2) << endl;
    cout << (d1 < d2) << endl;
    cout << (d1 == d2) << endl;
    Date d3 = d2.subtract(2060, 1, 1, 0, 0, 0);
    cout << endl;
    cout << d2.subtract(2060, 1, 1, 0, 0, 0) << endl;
    cout << endl;
    Date d4(d3 + d2 - d1);
    cout << d4 << endl;
    Date d5(d4);
    d4 += d5 - d4.add(40, 1, 1, 0, 0, 0);

    cout << d3 << endl;
    cout << d4 << endl;
    cout << d5 << endl;


    return 0;
}
