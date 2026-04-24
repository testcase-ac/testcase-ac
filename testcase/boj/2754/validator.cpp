#include "testlib.h"
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the grade token
    string grade = inf.readToken("[^]+", "grade");
    inf.readEoln();

    // Allowed grades
    static const set<string> allowed = {
        "A+", "A0", "A-",
        "B+", "B0", "B-",
        "C+", "C0", "C-",
        "D+", "D0", "D-",
        "F"
    };

    // Validate membership
    ensuref(allowed.count(grade),
            "Invalid grade '%s'. Must be one of A+, A0, A-, B+, B0, B-, C+, C0, C-, D+, D0, D-, F",
            grade.c_str());

    inf.readEof();
    return 0;
}
