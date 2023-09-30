#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
#include <vector>

struct people {
    std::string name;
    int year;
    int month;
    int day;
};

std::vector<people> new_people;

void min_m(int* min, std::tm* tmp) {
    for (int i = 0; i < new_people.size()-1; ++i) {
        if (*min>=tmp->tm_mon) {
            if (*min>new_people[i+1].month && new_people[i+1].day>=tmp->tm_mday) {
                *min=new_people[i+1].month;
            }
        }
        else {
            *min=new_people[i+1].month;
        }
    }
}

void min_d(int* min_d, int* min_m, std::tm* tmp) {
    for (int i = 0; i < new_people.size(); ++i) {
        if (new_people[i].month == *min_m && *min_m != tmp->tm_mon+1) {
            for (int j = 0; j < new_people.size()-1; ++j) {
                if (*min_d > new_people[j + 1].day) {
                    *min_d = new_people[j + 1].day;
                }
            }
        } else {
            if (*min_m == tmp->tm_mon+1) {
                for (int j = 0; j < new_people.size()-1; ++j) {
                    if (*min_d>=tmp->tm_mday) {
                        if (*min_d > new_people[j + 1].day) {
                            *min_d = new_people[j + 1].day;
                        }
                    }
                    else {
                        *min_d=new_people[j+1].day;
                    }
                }
            }
        }
    }
}

int main() {
    std::time_t t = std::time(nullptr);
    std::tm local = *std::localtime(&t);

    std::string friend_name;
    while (friend_name != "end") {
        std::cout << "Enter friend name and date of birth in the format yyyy/mm/dd.\nTo complete, enter end." << std::endl;
        std::cin >> friend_name;
        if (friend_name == "end") {
            break;
        }
        std::cin >> std::get_time(&local, "%Y/%m/%d");
        people person;
        person.name = friend_name;
        person.year = local.tm_year;
        person.month = local.tm_mon + 1;
        person.day = local.tm_mday;
        new_people.push_back(person);
    }

    std::time_t time_start = std::time(nullptr);
    std::tm tmp = *std::localtime(&time_start);
    int min_mounth = new_people.begin()->month;
    int min_day = new_people.begin()->day;

    min_m(&min_mounth, &tmp);
    min_d(&min_day, &min_mounth, &tmp);

    for (int i = 0; i < new_people.size(); ++i) {
        if (new_people[i].month == min_mounth && new_people[i].day == min_day) {
            if (min_mounth == tmp.tm_mon + 1 && min_day == tmp.tm_mday) {
                std::cout << "BIRTHDAY TODAY!!! " << new_people[i].name << std::endl;
            } else {
                local.tm_mon = min_mounth-1;
                local.tm_mday = min_day;
                std::cout << "Next birthday - " << std::put_time(&local, "%m/%d") << " " << new_people[i].name;
            }
        }
    }
}