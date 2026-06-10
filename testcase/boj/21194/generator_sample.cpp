#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int k;
    vector<int> grades;

    if (mode == 0) {
        n = 1;
        k = 1;
        grades = {rnd.next(0, 10000)};
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        k = 1;
        grades.resize(n);
        for (int& grade : grades) grade = rnd.next(0, 10000);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        k = n;
        grades.resize(n);
        for (int& grade : grades) grade = rnd.next(0, 10000);
    } else if (mode == 3) {
        n = rnd.next(5, 25);
        k = rnd.next(1, n);
        vector<int> pool = {0, 1, rnd.next(2, 50), rnd.next(9950, 10000), 10000};
        grades.resize(n);
        for (int& grade : grades) grade = rnd.any(pool);
    } else if (mode == 4) {
        n = rnd.next(6, 30);
        k = rnd.next(max(1, n / 3), n);
        int base = rnd.next(0, 9800);
        grades.resize(n);
        for (int i = 0; i < n; ++i) grades[i] = min(10000, base + rnd.next(0, 200));
    } else if (mode == 5) {
        n = rnd.next(8, 40);
        k = rnd.next(1, n);
        grades.resize(n);
        for (int i = 0; i < n; ++i) grades[i] = (i * rnd.next(3, 41) + rnd.next(0, 17)) % 10001;
        if (rnd.next(0, 1)) sort(grades.begin(), grades.end());
        else sort(grades.rbegin(), grades.rend());
    } else {
        n = rnd.next(40, 120);
        k = rnd.next(1, n);
        grades.resize(n);
        for (int& grade : grades) {
            if (rnd.next(0, 4) == 0) grade = rnd.any(vector<int>{0, 10000});
            else grade = rnd.next(0, 10000);
        }
    }

    if (mode != 5 || rnd.next(0, 1)) shuffle(grades.begin(), grades.end());

    println(n, k);
    for (int grade : grades) println(grade);

    return 0;
}
