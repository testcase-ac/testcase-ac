#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[KCP]{4,1000000}", "S");
    inf.readEoln();

    int countK = 0;
    int countC = 0;
    int countP = 0;
    for (char ch : s) {
        if (ch == 'K') {
            ++countK;
        } else if (ch == 'C') {
            ++countC;
        } else {
            ++countP;
        }
    }

    ensuref(countK >= 1, "S must contain at least one K");
    ensuref(countC >= 2, "S must contain at least two Cs");
    ensuref(countP >= 1, "S must contain at least one P");

    inf.readEof();
}
