#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 15);
    int mode = rnd.next(0, 4);
    int gap = rnd.next(1, 5);
    int k1 = mode == 4 ? 1000000000 : rnd.next(1, 20);
    int k2 = mode == 4 ? 1000000000 : rnd.next(1, 20);
    int start = mode == 4 ? 1000000000 - gap * (n - 1) : rnd.next(1, 20);
    vector<pair<int, int>> students;

    for (int i = 0; i < n; ++i) {
        int school;
        if (mode == 0)
            school = 1;
        else if (mode == 1)
            school = i % 2 + 1;
        else if (mode == 2)
            school = i + 1;
        else
            school = rnd.next(1, min(n, 4));
        students.emplace_back(start + gap * i, school);
    }

    shuffle(students.begin(), students.end());
    println(n, k1, k2);
    for (auto [x, school] : students) println(x, school);
}
