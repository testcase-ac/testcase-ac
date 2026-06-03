#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> grades = {"A+", "A", "B+", "B", "C+", "C", "D+", "D", "F"};
    string s;

    int mode = rnd.next(0, 5);
    int targetLen;

    if (mode == 0) {
        targetLen = rnd.next(1, 8);
    } else if (mode == 1) {
        targetLen = rnd.next(9, 30);
    } else if (mode == 2) {
        targetLen = rnd.next(31, 80);
    } else if (mode == 3) {
        targetLen = rnd.next(1, 30);
    } else if (mode == 4) {
        targetLen = rnd.next(1, 30);
    } else {
        targetLen = rnd.next(950, 1000);
    }

    while ((int)s.size() < targetLen) {
        string grade;
        if (mode == 3) {
            grade = rnd.any(vector<string>{"A+", "B+", "C+", "D+"});
        } else if (mode == 4) {
            grade = rnd.next(0, 3) == 0 ? rnd.any(grades) : string("F");
        } else {
            grade = rnd.any(grades);
        }

        if ((int)s.size() + (int)grade.size() > targetLen) {
            grade = rnd.any(vector<string>{"A", "B", "C", "D", "F"});
        }
        s += grade;
    }

    println(s);
    return 0;
}
