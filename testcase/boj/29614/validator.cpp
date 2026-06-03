#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readLine("[ABCDF+]{1,1000}", "S");

    for (int i = 0; i < (int)s.size();) {
        char grade = s[i];
        ensuref(grade == 'A' || grade == 'B' || grade == 'C' || grade == 'D' || grade == 'F',
                "expected grade letter at position %d, found '%c'", i + 1, grade);

        ++i;
        if (i < (int)s.size() && s[i] == '+') {
            ensuref(grade != 'F', "F+ is not a listed grade at position %d", i);
            ++i;
        }
    }

    inf.readEof();
}
