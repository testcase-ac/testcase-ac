#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> students;

    if (mode == 0) {
        n = 4;
        students = {1, 2, 3, 4};
    } else if (mode == 1) {
        n = rnd.next(5, 20);
        int start = rnd.next(1, n - 3);
        students = {start, start + 1, start + 2, start + 3};
    } else if (mode == 2) {
        n = rnd.next(6, 40);
        students = {1, 2, n - 1, n};
    } else if (mode == 3) {
        n = rnd.next(8, 80);
        students = {1, n, rnd.next(2, n / 2), rnd.next(n / 2 + 1, n - 1)};
    } else if (mode == 4) {
        n = rnd.next(30, 200);
        students = {rnd.next(1, n / 4), rnd.next(n / 4 + 1, n / 2),
                    rnd.next(n / 2 + 1, 3 * n / 4), rnd.next(3 * n / 4 + 1, n)};
    } else {
        n = rnd.next(1000, 5000);
        students = {1, rnd.next(2, n - 2), n - 1, n};
    }

    sort(students.begin(), students.end());
    students.erase(unique(students.begin(), students.end()), students.end());
    while ((int)students.size() < 4) {
        int student = rnd.next(1, n);
        if (find(students.begin(), students.end(), student) == students.end()) {
            students.push_back(student);
        }
    }

    shuffle(students.begin(), students.end());

    println(n);
    println(students);

    return 0;
}
