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

    Date(int year, int month, int day, int hour, int minute, int second, bool isOurEra_) {
        this->year_standard = year;
        this->month_standard = month;
        this->day_standard = day;
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
        if (this != &other) {
            year_standard = other.year_standard;
            month_standard = other.month_standard;
            day_standard = other.day_standard;
            hour_standard = other.hour_standard;
            minute_standard = other.minute_standard;
            second_standard = other.second_standard;
            isOurEra = other.isOurEra;
        }
        return *this;
    }

    Date& operator+=(const Date& other) {
        year_standard += other.year_standard;
        month_standard += other.month_standard;
        day_standard += other.day_standard;
        hour_standard += other.hour_standard;
        minute_standard += other.minute_standard;
        second_standard += other.second_standard;
        normalizeDate();
        return *this;
    }

    Date operator+(const Date& other) {
        Date date_result = *this;
        return date_result += other;
    }

    Date& operator-=(const Date& other) {
        year_standard -= other.year_standard;
        month_standard -= other.month_standard;
        day_standard -= other.day_standard;
        hour_standard -= other.hour_standard;
        minute_standard -= other.minute_standard;
        second_standard -= other.second_standard;
        normalizeDate();
        return *this;
    }

    Date operator-(const Date& other) {
        Date date_result = *this;
        return date_result -= other;
    }

    bool operator<(const Date& other) {
        if (year_standard != other.year_standard) return year_standard < other.year_standard;
        else if (month_standard != other.month_standard) return month_standard < other.month_standard;
        else if (day_standard != other.day_standard) return day_standard < other.day_standard;
        else if (hour_standard != other.hour_standard) return hour_standard < other.hour_standard;
        else if (minute_standard != other.minute_standard) return minute_standard < other.minute_standard;
        else if (second_standard != other.second_standard) return second_standard < other.second_standard;
        else if (isOurEra != other.isOurEra) return isOurEra > other.isOurEra;
        else return false;
    }

    bool operator>(const Date& other) {
        if (year_standard != other.year_standard) return year_standard > other.year_standard;
        else if (month_standard != other.month_standard) return month_standard > other.month_standard;
        else if (day_standard != other.day_standard) return day_standard > other.day_standard;
        else if (hour_standard != other.hour_standard) return hour_standard > other.hour_standard;
        else if (minute_standard != other.minute_standard) return minute_standard > other.minute_standard;
        else if (second_standard != other.second_standard) return second_standard > other.second_standard;
        else if (isOurEra != other.isOurEra) return isOurEra > other.isOurEra;
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
        os << date.year_standard << " " << date.month_standard << " " << date.day_standard << " "
           << date.hour_standard << " " << date.minute_standard << " " << date.second_standard;
        if (flag == true) os << " AD";
        else os << " BC";
        return os;
    }

    Date add(int year, int month, int day, int hour, int minute, int second) {
        Date date_result = *this;
        date_result.year_standard += year;
        date_result.month_standard += month;
        date_result.day_standard += day;
        date_result.hour_standard += hour;
        date_result.minute_standard += minute;
        date_result.second_standard += second;
        date_result.normalizeDate();
        return date_result;
    }

    Date subtract(int year, int month, int day, int hour, int minute, int second) {
        Date date_result = *this;
        date_result.year_standard -= year;
        date_result.month_standard -= month;
        date_result.day_standard -= day;
        date_result.hour_standard -= hour;
        date_result.minute_standard -= minute;
        date_result.second_standard -= second;
        date_result.normalizeDate();
        return date_result;
    }

    void normalizeDate() {

        minute_standard += second_standard / 60;
        second_standard %= 60;
        hour_standard += minute_standard / 60;
        minute_standard %= 60;

        int days_in_Month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        while (second_standard < 0) {
            second_standard += 60;
            minute_standard--;
        }

        while (minute_standard < 0) {
            minute_standard += 60;
            hour_standard--;
        }

        while (hour_standard < 0) {
            hour_standard += 24;
            day_standard--;
        }

        while (day_standard < 1) {
            month_standard--;
            if (month_standard < 1) {
                month_standard = 12;
                year_standard--;
            }
            int daysInCurrentMonth = days_in_Month[month_standard];
            if (month_standard == 2 && leap_Year(year_standard)) {
                daysInCurrentMonth++;
            }
            day_standard += daysInCurrentMonth;
        }

        while (month_standard > 12) {
            month_standard -= 12;
            year_standard++;
        }

        if (year_standard <= 0) {
            year_standard = -year_standard + 1;
            isOurEra = false;
        }

        if (year_standard > 0) {
            isOurEra = true;
        }
    }

    bool leap_Year(int year) {
        return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
    }

};

int main() {
    Date date1;
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

    return 0;
}
