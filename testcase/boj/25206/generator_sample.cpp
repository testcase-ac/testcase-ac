#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> credits = {"1.0", "2.0", "3.0", "4.0"};
    const vector<string> allGrades = {
        "A+", "A0", "B+", "B0", "C+", "C0", "D+", "D0", "F", "P"};
    const vector<string> scoredGrades = {
        "A+", "A0", "B+", "B0", "C+", "C0", "D+", "D0", "F"};
    const vector<string> highGrades = {"A+", "A0", "B+"};
    const vector<string> lowGrades = {"D0", "F"};

    int mode = rnd.next(0, 4);
    int nonPass = rnd.next(1, 20);
    if (mode == 1) {
        nonPass = 1;
    } else if (mode == 2) {
        nonPass = 20;
    }

    vector<int> scored(20, 0);
    for (int i = 0; i < nonPass; ++i) {
        scored[i] = 1;
    }
    shuffle(scored.begin(), scored.end());

    for (int i = 0; i < 20; ++i) {
        string subject = "Course" + to_string(i + 1);
        string credit = rnd.any(credits);
        string grade;

        if (!scored[i]) {
            grade = "P";
        } else if (mode == 2) {
            grade = "F";
        } else if (mode == 3) {
            grade = rnd.any(i % 2 == 0 ? highGrades : lowGrades);
        } else if (mode == 4) {
            grade = rnd.any(scoredGrades);
        } else {
            grade = rnd.any(allGrades);
            if (grade == "P") {
                grade = rnd.any(scoredGrades);
            }
        }

        println(subject, credit, grade);
    }

    return 0;
}
