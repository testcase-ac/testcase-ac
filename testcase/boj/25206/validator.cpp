#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const set<string> credits = {"1.0", "2.0", "3.0", "4.0"};
    const set<string> grades = {
        "A+", "A0", "B+", "B0", "C+", "C0", "D+", "D0", "F", "P"};

    set<string> subjects;
    bool hasNonPass = false;

    for (int i = 1; i <= 20; ++i) {
        string subject = inf.readToken("[A-Za-z0-9]{1,50}", "subject");
        inf.readSpace();
        string credit = inf.readToken("[1-4][.]0", "credit");
        inf.readSpace();
        string grade = inf.readToken("[A-DF][+0]|F|P", "grade");
        inf.readEoln();

        ensuref(credits.count(credit), "invalid credit at line %d: %s",
                i, credit.c_str());
        ensuref(grades.count(grade), "invalid grade at line %d: %s",
                i, grade.c_str());
        ensuref(subjects.insert(subject).second,
                "duplicate subject at line %d: %s", i, subject.c_str());

        if (grade != "P") {
            hasNonPass = true;
        }
    }

    ensuref(hasNonPass, "at least one grade must not be P");
    inf.readEof();
}
