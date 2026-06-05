#include "testlib.h"
#include <array>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

using Preference = tuple<string, string, string>;

const array<string, 3> SUBJECTS = {"kor", "eng", "math"};
const array<string, 3> FRUITS = {"apple", "pear", "orange"};
const array<string, 3> COLORS = {"red", "blue", "green"};

string maybeWildcard(const string& value, int wildcardPercent) {
    return rnd.next(1, 100) <= wildcardPercent ? "-" : value;
}

Preference randomPreference() {
    return {rnd.any(SUBJECTS), rnd.any(FRUITS), rnd.any(COLORS)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(1, mode == 3 ? 120 : 30);
    int m = rnd.next(1, mode == 3 ? 120 : 40);

    vector<Preference> students;
    vector<Preference> pool;

    if (mode == 0) {
        for (int i = 0; i < n; ++i) students.push_back(randomPreference());
    } else if (mode == 1) {
        int poolSize = rnd.next(1, 5);
        for (int i = 0; i < poolSize; ++i) pool.push_back(randomPreference());
        for (int i = 0; i < n; ++i) students.push_back(rnd.any(pool));
    } else if (mode == 2) {
        string fixedSubject = rnd.any(SUBJECTS);
        string fixedFruit = rnd.any(FRUITS);
        for (int i = 0; i < n; ++i) {
            students.push_back({fixedSubject, fixedFruit, rnd.any(COLORS)});
        }
    } else {
        for (const string& subject : SUBJECTS) {
            for (const string& fruit : FRUITS) {
                for (const string& color : COLORS) {
                    pool.push_back({subject, fruit, color});
                }
            }
        }
        shuffle(pool.begin(), pool.end());
        for (int i = 0; i < n; ++i) students.push_back(pool[i % (int)pool.size()]);
        shuffle(students.begin(), students.end());
    }

    println(n, m);
    for (const auto& [subject, fruit, color] : students) {
        cout << subject << ' ' << fruit << ' ' << color << '\n';
    }

    int wildcardPercent = rnd.next(0, 75);
    for (int i = 0; i < m; ++i) {
        Preference base = rnd.next(0, 1) ? rnd.any(students) : randomPreference();
        auto [subject, fruit, color] = base;
        cout << maybeWildcard(subject, wildcardPercent) << ' '
             << maybeWildcard(fruit, wildcardPercent) << ' '
             << maybeWildcard(color, wildcardPercent) << '\n';
    }

    return 0;
}
