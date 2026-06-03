#include "testlib.h"
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int t = rnd.next(1, 20);
        for (int i = 0; i < t; ++i) {
            int year = rnd.next(2000, 2100);
            int month = rnd.next(1, 12);
            cases.push_back({year, month});
        }
    } else if (mode == 1) {
        vector<int> years = {2000, 2004, 2012, 2020, 2024, 2096, 2100};
        shuffle(years.begin(), years.end());
        int t = rnd.next(4, (int)years.size());
        for (int i = 0; i < t; ++i) {
            int month = rnd.next(1, 3);
            cases.push_back({years[i], month});
        }
    } else if (mode == 2) {
        int t = rnd.next(6, 30);
        for (int i = 0; i < t; ++i) {
            int year = rnd.next(2000, 2100);
            int month = rnd.any(vector<int>{1, 2, 3, 11, 12});
            cases.push_back({year, month});
        }
    } else if (mode == 3) {
        int year = rnd.next(2000, 2100);
        for (int month = 1; month <= 12; ++month) {
            cases.push_back({year, month});
        }
        if (rnd.next(0, 1)) {
            int otherYear = rnd.any(vector<int>{2000, 2001, 2099, 2100});
            for (int month = 1; month <= 12; ++month) {
                cases.push_back({otherYear, month});
            }
        }
    } else if (mode == 4) {
        int t = rnd.next(50, 150);
        for (int i = 0; i < t; ++i) {
            int year = rnd.any(vector<int>{2000, 2001, 2004, 2096, 2099, 2100});
            int month = rnd.next(1, 12);
            cases.push_back({year, month});
        }
    } else {
        int t = rnd.next(600, 1212);
        for (int i = 0; i < t; ++i) {
            int year = rnd.next(2000, 2100);
            int month = rnd.next(1, 12);
            if (rnd.next(0, 3) == 0) month = rnd.any(vector<int>{1, 3});
            cases.push_back({year, month});
        }
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [year, month] : cases) {
        println(year, month);
    }

    return 0;
}
