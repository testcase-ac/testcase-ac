#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> sortedUnique(vector<int> values) {
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    return values;
}

vector<int> randomDay(int minSize, int maxSize) {
    vector<int> values;
    for (int x = 1; x <= 9; ++x) values.push_back(x);
    shuffle(values.begin(), values.end());
    int size = rnd.next(minSize, maxSize);
    values.resize(size);
    return sortedUnique(values);
}

void printDays(const vector<vector<int>>& days) {
    println((int)days.size());
    for (const vector<int>& day : days) {
        vector<int> line;
        line.push_back((int)day.size());
        line.insert(line.end(), day.begin(), day.end());
        println(line);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<vector<int>> days;

    if (mode == 0) {
        int n = rnd.next(1, 35);
        int current = rnd.next(1, 9);
        for (int i = 0; i < n; ++i) {
            if (i > 0 && rnd.next(0, 99) < 70) {
                int next = rnd.next(1, 8);
                if (next >= current) ++next;
                current = next;
            }
            days.push_back({current});
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 45);
        int value = rnd.next(1, 9);
        for (int i = 0; i < n; ++i) days.push_back({value});
    } else if (mode == 2) {
        int n = rnd.next(3, 60);
        int a = rnd.next(1, 9);
        int b = rnd.next(1, 8);
        if (b >= a) ++b;
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 80) {
                days.push_back(sortedUnique({a, b}));
            } else {
                days.push_back(randomDay(1, 3));
            }
        }
    } else if (mode == 3) {
        int n = rnd.next(2, 40);
        for (int i = 0; i < n; ++i) {
            int minSize = rnd.next(1, 4);
            int maxSize = rnd.next(minSize, 9);
            days.push_back(randomDay(minSize, maxSize));
        }
    } else if (mode == 4) {
        int n = rnd.next(3, 70);
        int blocked = rnd.next(1, 9);
        for (int i = 0; i < n; ++i) {
            if (i == n / 2 || i == n / 2 + 1) {
                days.push_back({blocked});
            } else if (rnd.next(0, 99) < 65) {
                days.push_back(randomDay(2, 5));
            } else {
                days.push_back(randomDay(1, 9));
            }
        }
    } else {
        int n = rnd.next(20, 90);
        for (int i = 0; i < n; ++i) {
            int missing = (i + rnd.next(0, 2)) % 9 + 1;
            vector<int> day;
            for (int x = 1; x <= 9; ++x) {
                if (x != missing && rnd.next(0, 99) < 85) day.push_back(x);
            }
            if (day.empty()) day.push_back(missing == 1 ? 2 : 1);
            days.push_back(day);
        }
    }

    printDays(days);
    return 0;
}
