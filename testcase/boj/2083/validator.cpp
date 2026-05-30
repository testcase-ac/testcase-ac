#include "testlib.h"
#include <climits>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int NAME_MAXLEN = 10;
    const int AGE_MIN = 1;
    const int WEIGHT_MIN = 1;

    int line_cnt = 0;
    while (true) {
        string name = inf.readToken("([A-Za-z]{1,10}|#)", "name");
        inf.readSpace();

        long long age = inf.readLong(0, LLONG_MAX, "age");
        inf.readSpace();
        long long weight = inf.readLong(0, LLONG_MAX, "weight");
        inf.readEoln();

        if (name == "#" && age == 0 && weight == 0) {
            break;
        }

        ensuref(name != "#", "Only the final sentinel may use # as the name at line %d", line_cnt + 1);
        ensuref((int)name.length() <= NAME_MAXLEN,
                "Name length must be at most %d at line %d, got '%s' (len=%d)", NAME_MAXLEN, line_cnt + 1, name.c_str(), (int)name.length());
        ensuref(age >= AGE_MIN, "Age must be at least %d at line %d, got %lld", AGE_MIN, line_cnt + 1, age);
        ensuref(weight >= WEIGHT_MIN, "Weight must be at least %d at line %d, got %lld", WEIGHT_MIN, line_cnt + 1, weight);

        ++line_cnt;
    }

    inf.readEof();
}
