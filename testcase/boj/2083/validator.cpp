#include "testlib.h"
#include <cctype>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int NAME_MAXLEN = 10;
    const int AGE_MIN = 1;
    const int AGE_MAX = 200; // reasonable upper bound for age
    const int WEIGHT_MIN = 1;
    const int WEIGHT_MAX = 300; // reasonable upper bound for weight

    int line_cnt = 0;
    while (true) {
        // Read name as a generic token, because the end marker is "#"
        string name = inf.readToken("[^ ]{1,10}", "name"); // up to 10 non-space chars
        inf.readSpace();

        // Read age and weight as integers (could be zero for end marker)
        int age = inf.readInt(0, AGE_MAX, "age");
        inf.readSpace();
        int weight = inf.readInt(0, WEIGHT_MAX, "weight");
        inf.readEoln();

        // Check for end marker
        if (name == "#" && age == 0 && weight == 0) {
            break;
        }

        // Name: must be alphabetic only, 1~10 chars, not "#"
        ensuref((int)name.length() >= 1 && (int)name.length() <= NAME_MAXLEN,
                "Name length must be 1..10 at line %d, got '%s' (len=%d)", line_cnt + 1, name.c_str(), (int)name.length());
        for (char c : name) {
            ensuref(isalpha(c), "Name contains non-alphabet character at line %d: '%s'", line_cnt + 1, name.c_str());
        }

        // Age and weight: must be positive (natural numbers)
        ensuref(age >= AGE_MIN, "Age must be at least %d at line %d, got %d", AGE_MIN, line_cnt + 1, age);
        ensuref(weight >= WEIGHT_MIN, "Weight must be at least %d at line %d, got %d", WEIGHT_MIN, line_cnt + 1, weight);

        ++line_cnt;
    }

    inf.readEof();
}
