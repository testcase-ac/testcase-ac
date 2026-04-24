#include "testlib.h"
#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the course code for the course to be retaken
    // Format: 10 characters: positions 1-6 digits, 7th uppercase letter or digit, 8th hyphen, 9-10 digits
    string retake = inf.readToken("[0-9]{6,6}[A-Z0-9]-[0-9]{2,2}", "retake_code");
    inf.readEoln();

    // Read N: number of available courses
    int N = inf.readInt(1, 16, "N");
    inf.readEoln();

    // Read the N course codes, ensure they follow the same format and are distinct
    set<string> seen;
    for (int i = 0; i < N; i++) {
        string code = inf.readToken("[0-9]{6,6}[A-Z0-9]-[0-9]{2,2}", "code_i");
        inf.readEoln();
        ensuref(!seen.count(code),
                "Duplicate course code at index %d: %s", i, code.c_str());
        seen.insert(code);
    }

    inf.readEof();
    return 0;
}
