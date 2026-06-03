#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

struct Person {
    string name;
    int day;
    int month;
    int year;
};

static bool isLeapYear(int year) {
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

static int daysInMonth(int month, int year) {
    static const int days[] = {
        0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
    };
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return days[month];
}

static string makeName(int index, int style) {
    if (style == 0) {
        return string(1, char('A' + index));
    }

    static const vector<string> prefixes = {
        "Ada", "Ben", "Cleo", "Dora", "Evan", "Faye", "Gus", "Hana",
        "Ian", "Judy", "Kira", "Liam", "Mina", "Nora", "Owen", "Pia",
    };

    string name = prefixes[index % prefixes.size()] + char('A' + index / prefixes.size());
    if (style == 2) {
        while ((int)name.size() < 15) {
            name += char('a' + rnd.next(26));
        }
    }
    return name.substr(0, 15);
}

static Person randomPerson(int index, int style, set<tuple<int, int, int>>& usedDates) {
    int year;
    int month;
    int day;
    do {
        year = rnd.next(1990, 2010);
        month = rnd.next(1, 12);
        day = rnd.next(1, daysInMonth(month, year));
    } while (!usedDates.insert({year, month, day}).second);

    return {makeName(index, style), day, month, year};
}

static void addDate(vector<Person>& people, set<tuple<int, int, int>>& usedDates,
                    int index, int style, int day, int month, int year) {
    if (usedDates.insert({year, month, day}).second) {
        people.push_back({makeName(index, style), day, month, year});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int style = rnd.next(0, 2);
    vector<Person> people;
    set<tuple<int, int, int>> usedDates;

    if (mode == 0) {
        people.push_back(randomPerson(0, style, usedDates));
    } else if (mode == 1) {
        addDate(people, usedDates, 0, style, 1, 1, 1990);
        addDate(people, usedDates, 1, style, 31, 12, 2010);
        int n = rnd.next(3, 8);
        while ((int)people.size() < n) {
            people.push_back(randomPerson((int)people.size(), style, usedDates));
        }
    } else if (mode == 2) {
        vector<tuple<int, int, int>> candidates = {
            {29, 2, 1992}, {29, 2, 1996}, {29, 2, 2000}, {29, 2, 2004}, {29, 2, 2008},
            {28, 2, 1991}, {30, 4, 1995}, {31, 7, 2003}, {31, 12, 2010},
        };
        shuffle(candidates.begin(), candidates.end());
        int n = rnd.next(2, (int)candidates.size());
        for (int i = 0; i < n; ++i) {
            int day, month, year;
            tie(day, month, year) = candidates[i];
            addDate(people, usedDates, i, style, day, month, year);
        }
    } else {
        int n = rnd.next(6, 20);
        while ((int)people.size() < n) {
            people.push_back(randomPerson((int)people.size(), style, usedDates));
        }
    }

    shuffle(people.begin(), people.end());

    println((int)people.size());
    for (const Person& person : people) {
        println(person.name, person.day, person.month, person.year);
    }

    return 0;
}
