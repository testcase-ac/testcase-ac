#include "testlib.h"

#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Area {
    string name;
    string initialCode;
};

struct Rule {
    int year;
    int type;
    int area;
    string arg;
};

static string randomDigits(int length) {
    string value;
    value.reserve(length);
    for (int i = 0; i < length; ++i) {
        value.push_back(char('0' + rnd.next(0, 9)));
    }
    return value;
}

static string codeAtYear(const vector<Area>& areas, const vector<Rule>& rules, int area, int year) {
    string code = areas[area].initialCode;
    for (const Rule& rule : rules) {
        if (rule.year > year) {
            break;
        }
        if (rule.area == area && rule.type == 3) {
            code = rule.arg;
        }
    }
    return code;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Area> areas = {
        {"Alpha", "10"},
        {"Beta", "20"},
        {"Gamma", "30"},
        {"Delta", "40"},
    };
    int areaCount = rnd.next(2, (int)areas.size());
    areas.resize(areaCount);
    shuffle(areas.begin(), areas.end());

    vector<string> spareCodes = {"50", "60", "70", "80", "90", "11", "22", "33", "44", "55"};
    shuffle(spareCodes.begin(), spareCodes.end());

    int ruleCount = rnd.next(3, 8);
    vector<Rule> rules;
    set<int> years;
    for (int i = 0; i < ruleCount; ++i) {
        int year;
        do {
            year = rnd.next(1995, 2015);
        } while (!years.insert(year).second);

        int area = rnd.next(0, areaCount - 1);
        int type;
        if (!spareCodes.empty() && rnd.next(0, 3) == 0) {
            type = 3;
        } else {
            type = rnd.next(1, 2);
        }

        string arg;
        if (type == 1) {
            arg = to_string(rnd.next(1, 6));
        } else if (type == 2) {
            arg = to_string(rnd.next(1, 5));
        } else {
            arg = spareCodes.back();
            spareCodes.pop_back();
        }
        rules.push_back({year, type, area, arg});
    }
    sort(rules.begin(), rules.end(), [](const Rule& lhs, const Rule& rhs) {
        return lhs.year < rhs.year;
    });

    println(areaCount);
    for (const Area& area : areas) {
        println(area.initialCode, area.name);
    }

    println((int)rules.size());
    for (const Rule& rule : rules) {
        println(rule.year, rule.type, areas[rule.area].name, rule.arg);
    }

    int queryCount = rnd.next(4, 9);
    for (int i = 0; i < queryCount; ++i) {
        int area = rnd.next(0, areaCount - 1);
        int year1 = rnd.next(1994, 2014);
        int year2 = rnd.next(year1, 2018);
        int localLength = rnd.next(6, 10);
        string number = codeAtYear(areas, rules, area, year1) + randomDigits(localLength);
        println(year1, year2, number);
    }
    println(0, 0, 0);

    return 0;
}
