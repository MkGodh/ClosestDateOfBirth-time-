#include <iostream>
#include <ctime>
#include <limits>
#include <vector>

struct friendsBD {
    std::string name;
    int date;
    int month;
    int year;
};

std::tm convert(const friendsBD& friendBd) {
    std::tm birthday = {};
    birthday.tm_year = friendBd.year - 1900; 
    birthday.tm_mon = friendBd.month - 1;    
    birthday.tm_mday = friendBd.date;
    return birthday;
}

int main() {
    std::vector<friendsBD> group;
    std::string command;
    std::cout << "Hello. Please input your friends' Birth Dates: " << std::endl;

    while (command != "end") {
        friendsBD currentFriend;
        std::cout << "Input your friend name: " << std::endl;
        std::cin >> currentFriend.name;
        std::cout << "Input date of birth: " << std::endl;
        std::cin >> currentFriend.date;
        std::cout << "Input month of birth: " << std::endl;
        std::cin >> currentFriend.month;
        std::cout << "Input year of birth: " << std::endl;
        std::cin >> currentFriend.year;
        group.push_back(currentFriend);

        std::cout << "Enter 'end' to finish input or any other input to continue: ";
        std::cin >> command;
    }

    std::time_t now = std::time(nullptr);
    std::tm currentDate;
    localtime_s(&currentDate, &now);

    friendsBD* nearestFriend = nullptr;
    std::time_t nearestBirthdayTime = std::numeric_limits<std::time_t>::max();

    for (auto& friendBD : group) {
        std::tm birthdayThisYear = convert(friendBD);
        birthdayThisYear.tm_year = currentDate.tm_year;

        std::time_t birthdayTime = std::mktime(&birthdayThisYear);

        if (birthdayThisYear.tm_mon == currentDate.tm_mon && birthdayThisYear.tm_mday == currentDate.tm_mday) {
            std::cout << "Today is " << friendBD.name << "'s birthday!\n";
        }

        if (birthdayTime < now) {
            continue;
        }

        if (birthdayTime < nearestBirthdayTime) {
            nearestBirthdayTime = birthdayTime;
            nearestFriend = &friendBD;
        }
    }

    if (nearestFriend) {
        std::tm nearestTm;
        localtime_s(&nearestTm, &nearestBirthdayTime);
        std::cout << "The nearest birthday is " << nearestFriend->name << " on "
            << nearestTm.tm_mday << "/" << (nearestTm.tm_mon + 1) << "/"
            << (nearestTm.tm_year + 1900) << std::endl; 
    }
    else {
        std::cout << "No upcoming birthdays.\n";
    }

    return 0;
}
