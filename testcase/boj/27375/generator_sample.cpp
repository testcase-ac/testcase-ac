#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

int credit(const tuple<int, int, int>& course) {
    return get<2>(course) - get<1>(course) + 1;
}

tuple<int, int, int> randomCourse(int minDay, int maxDay) {
    int w = rnd.next(minDay, maxDay);
    int s = rnd.next(1, 10);
    int e = rnd.next(s, 10);
    return {w, s, e};
}

tuple<int, int, int> randomCourseWithLength(int minDay, int maxDay, int len) {
    int w = rnd.next(minDay, maxDay);
    int s = rnd.next(1, 11 - len);
    return {w, s, s + len - 1};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<tuple<int, int, int>> courses;

    if (mode == 0) {
        int n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            courses.push_back(randomCourse(1, 4));
        }
    } else if (mode == 1) {
        int n = rnd.next(6, 16);
        int day = rnd.next(1, 4);
        int center = rnd.next(3, 8);
        for (int i = 0; i < n; ++i) {
            int s = rnd.next(max(1, center - 2), center);
            int e = rnd.next(center, min(10, center + 2));
            courses.push_back({day, s, e});
        }
    } else if (mode == 2) {
        int n = rnd.next(5, 14);
        for (int i = 0; i < n; ++i) {
            int len = rnd.any(vector<int>{1, 1, 2, 3, 5, 10});
            int minDay = (i % 3 == 0 ? 5 : 1);
            int maxDay = (i % 3 == 0 ? 5 : 5);
            courses.push_back(randomCourseWithLength(minDay, maxDay, len));
        }
    } else if (mode == 3) {
        int n = rnd.next(10, 20);
        for (int day = 1; day <= 5 && (int)courses.size() < n; ++day) {
            courses.push_back({day, 1, rnd.next(1, 4)});
            if ((int)courses.size() < n) {
                courses.push_back({day, rnd.next(4, 7), rnd.next(7, 10)});
            }
        }
        while ((int)courses.size() < n) {
            courses.push_back(randomCourse(1, 5));
        }
    } else {
        int n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            courses.push_back(randomCourse(1, 5));
        }
    }

    shuffle(courses.begin(), courses.end());

    int k;
    if (rnd.next(0, 3) == 0) {
        k = rnd.next(1, 22);
    } else {
        int total = 0;
        vector<int> indices(courses.size());
        for (int i = 0; i < (int)indices.size(); ++i) {
            indices[i] = i;
        }
        shuffle(indices.begin(), indices.end());
        for (int idx : indices) {
            if (get<0>(courses[idx]) != 5 && total + credit(courses[idx]) <= 22) {
                total += credit(courses[idx]);
            }
        }
        k = max(1, total);
    }

    println((int)courses.size(), k);
    for (auto [w, s, e] : courses) {
        println(w, s, e);
    }

    return 0;
}
