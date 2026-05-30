#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 0;
    while (true) {
        string s = inf.readLine("[01]{1,31}[eo]|#", "line");
        if (s == "#") {
            break;
        }
        tc++;
    }
    ensuref(tc >= 1, "input must contain at least one bit string before #");

    inf.readEof();
    return 0;
}
