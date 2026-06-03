#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

vector<int> shuffledPeriods() {
    vector<int> periods;
    for (int i = 1; i <= 50; ++i) periods.push_back(i);
    shuffle(periods.begin(), periods.end());
    return periods;
}

vector<int> takeRandomSet(int size) {
    vector<int> periods = shuffledPeriods();
    periods.resize(size);
    sort(periods.begin(), periods.end());
    return periods;
}

vector<int> dayClusterSet(int minSize, int maxSize) {
    int size = rnd.next(minSize, maxSize);
    vector<int> pool;
    int day = rnd.next(0, 4);
    for (int t = 1; t <= 10; ++t) pool.push_back(day * 10 + t);

    if (rnd.next(2)) {
        int otherDay = rnd.next(0, 4);
        while (otherDay == day) otherDay = rnd.next(0, 4);
        int extra = rnd.next(1, 10);
        for (int t = 1; t <= extra; ++t) pool.push_back(otherDay * 10 + t);
    }

    shuffle(pool.begin(), pool.end());
    vector<int> result;
    for (int x : pool) {
        if (find(result.begin(), result.end(), x) == result.end()) {
            result.push_back(x);
            if ((int)result.size() == size) break;
        }
    }

    while ((int)result.size() < size) {
        int x = rnd.next(1, 50);
        if (find(result.begin(), result.end(), x) == result.end()) result.push_back(x);
    }
    sort(result.begin(), result.end());
    return result;
}

void printLine(const vector<int>& values) {
    printf("%d", (int)values.size());
    for (int x : values) printf(" %d", x);
    printf("\n");
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(3, mode == 3 ? 6 : 12);
    int m = rnd.next(1, mode == 3 ? 8 : 20);

    vector<vector<int>> courses;
    for (int i = 0; i < n; ++i) {
        if (mode == 1) {
            courses.push_back(dayClusterSet(4, 10));
        } else if (mode == 2 && i == 0) {
            courses.push_back(takeRandomSet(50));
        } else {
            int bias = rnd.next(-2, 2);
            int k = 4 + rnd.wnext(47, bias);
            courses.push_back(takeRandomSet(k));
        }
    }

    println(n);
    for (const auto& course : courses) printLine(course);

    println(m);
    for (int i = 0; i < m; ++i) {
        if (mode == 2 && i == 0) {
            printLine(vector<int>());
        } else if (mode == 2 && i == 1) {
            printLine(takeRandomSet(50));
        } else if (mode == 3 && i < (int)courses.size()) {
            vector<int> free = courses[i];
            int extras = rnd.next(0, 6);
            while (extras--) {
                int x = rnd.next(1, 50);
                if (find(free.begin(), free.end(), x) == free.end()) free.push_back(x);
            }
            sort(free.begin(), free.end());
            printLine(free);
        } else if (mode == 1) {
            printLine(dayClusterSet(0, 20));
        } else {
            int p = rnd.next(0, 50);
            printLine(takeRandomSet(p));
        }
    }

    return 0;
}
