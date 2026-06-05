#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> validCommands() {
    vector<int> commands;
    for (int i = 0; i < 8; ++i) {
        for (int j = i + 1; j < 8; ++j) {
            commands.push_back((1 << i) + (1 << j));
        }
    }
    return commands;
}

vector<int> invalidCommands(const vector<int>& valid) {
    vector<int> commands;
    for (int x = 0; x < 256; ++x) {
        if (!binary_search(valid.begin(), valid.end(), x)) {
            commands.push_back(x);
        }
    }
    return commands;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> valid = validCommands();
    sort(valid.begin(), valid.end());
    vector<int> invalid = invalidCommands(valid);
    vector<int> a;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        int n = rnd.next(1, 18);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(0, 3));
        }
    } else if (mode == 1) {
        int n = rnd.next(1, 28);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(valid));
        }
    } else if (mode == 2) {
        int n = rnd.next(1, 35);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(invalid));
        }
    } else if (mode == 3) {
        int n = rnd.next(8, 45);
        int first = rnd.any(valid);
        int second = rnd.any(valid);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                a.push_back(first);
            } else if (i % 3 == 1) {
                a.push_back(rnd.any(invalid));
            } else {
                a.push_back(second);
            }
        }
    } else if (mode == 4) {
        int n = rnd.next(10, 55);
        vector<int> special = {0, 1, 2, 3, 127, 128, 129, 254, 255};
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 35) {
                a.push_back(rnd.any(special));
            } else if (rnd.next(0, 99) < 50) {
                a.push_back(rnd.any(valid));
            } else {
                a.push_back(rnd.any(invalid));
            }
        }
    } else {
        int n = rnd.next(20, 70);
        int pivot = rnd.next(0, 7);
        vector<int> touchingPivot;
        for (int other = 0; other < 8; ++other) {
            if (other != pivot) {
                touchingPivot.push_back((1 << min(pivot, other)) + (1 << max(pivot, other)));
            }
        }
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(0, 99);
            if (pick < 60) {
                a.push_back(rnd.any(touchingPivot));
            } else if (pick < 80) {
                a.push_back(rnd.any(valid));
            } else {
                a.push_back(rnd.any(invalid));
            }
        }
    }

    if (rnd.next(0, 99) < 35) {
        shuffle(a.begin(), a.end());
    }

    println((int)a.size());
    println(a);
    println(rnd.next(0, 7));

    return 0;
}
