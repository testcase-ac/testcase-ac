#include "testlib.h"

#include <string>

using namespace std;

bool hasRecursiveRepresentation(const string& t) {
    string pattern;
    while (pattern.size() < t.size()) {
        char next_char = t[pattern.size()];
        string unit = pattern + next_char;

        int repetitions = 0;
        while ((repetitions + 1) * unit.size() <= t.size() &&
               t.compare(repetitions * unit.size(), unit.size(), unit) == 0) {
            ++repetitions;
        }
        if (repetitions == 0) {
            return false;
        }

        string next_pattern;
        next_pattern.reserve(repetitions * unit.size() + pattern.size());
        for (int i = 0; i < repetitions; ++i) {
            next_pattern += unit;
        }
        next_pattern += pattern;
        pattern = next_pattern;
    }

    return pattern == t;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string t = inf.readToken("[a-z]{1,1048575}", "T");
    inf.readEoln();
    inf.readEof();

    ensuref(hasRecursiveRepresentation(t), "T has no recursive representation");
}
