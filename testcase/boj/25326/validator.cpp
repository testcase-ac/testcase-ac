#include "testlib.h"
#include <string>
using namespace std;

bool isSubject(const string& token) {
    return token == "kor" || token == "eng" || token == "math";
}

bool isFruit(const string& token) {
    return token == "apple" || token == "pear" || token == "orange";
}

bool isColor(const string& token) {
    return token == "red" || token == "blue" || token == "green";
}

bool isQuerySubject(const string& token) {
    return token == "-" || isSubject(token);
}

bool isQueryFruit(const string& token) {
    return token == "-" || isFruit(token);
}

bool isQueryColor(const string& token) {
    return token == "-" || isColor(token);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string subject = inf.readToken("[a-z]+", "student_subject");
        ensuref(isSubject(subject), "invalid student subject at row %d: %s", i + 1, subject.c_str());
        inf.readSpace();
        string fruit = inf.readToken("[a-z]+", "student_fruit");
        ensuref(isFruit(fruit), "invalid student fruit at row %d: %s", i + 1, fruit.c_str());
        inf.readSpace();
        string color = inf.readToken("[a-z]+", "student_color");
        ensuref(isColor(color), "invalid student color at row %d: %s", i + 1, color.c_str());
        inf.readEoln();
    }

    for (int i = 0; i < m; ++i) {
        string subject = inf.readToken("[a-z-]+", "query_subject");
        ensuref(isQuerySubject(subject), "invalid query subject at row %d: %s", i + 1, subject.c_str());
        inf.readSpace();
        string fruit = inf.readToken("[a-z-]+", "query_fruit");
        ensuref(isQueryFruit(fruit), "invalid query fruit at row %d: %s", i + 1, fruit.c_str());
        inf.readSpace();
        string color = inf.readToken("[a-z-]+", "query_color");
        ensuref(isQueryColor(color), "invalid query color at row %d: %s", i + 1, color.c_str());
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
