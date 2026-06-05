#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> grades;

    if (mode == 0) {
        n = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) grades.push_back(rnd.next(1, 5));
    } else if (mode == 1) {
        n = rnd.next(15, 20);
        int grade = rnd.next(1, 5);
        grades.assign(n, grade);
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) grades.push_back(rnd.next(0, 1) ? 5 : 1);
    } else if (mode == 3) {
        n = rnd.next(3, 20);
        int low = rnd.next(1, 3);
        int high = rnd.next(low, 5);
        for (int i = 0; i < n; ++i) grades.push_back(rnd.next(low, high));
    } else if (mode == 4) {
        n = rnd.next(5, 20);
        int dominant = rnd.next(1, 5);
        int rare = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) grades.push_back(rnd.next(0, 4) == 0 ? rare : dominant);
    } else {
        n = 20;
        for (int grade = 1; grade <= 5; ++grade) {
            int count = rnd.next(1, 5);
            while (count-- > 0 && (int)grades.size() < n) grades.push_back(grade);
        }
        while ((int)grades.size() < n) grades.push_back(rnd.next(1, 5));
    }

    if (rnd.next(0, 2) == 0) {
        sort(grades.begin(), grades.end());
    } else if (rnd.next(0, 1) == 0) {
        sort(grades.rbegin(), grades.rend());
    } else {
        shuffle(grades.begin(), grades.end());
    }

    println((int)grades.size());
    for (int grade : grades) println(grade);

    return 0;
}
