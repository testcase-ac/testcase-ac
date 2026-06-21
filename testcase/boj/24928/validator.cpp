#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[AB]{1,30}", "S");
    inf.readSpace();
    int d = inf.readInt(0, 1073741823, "D");
    inf.readEoln();

    long long value = 0;
    long long bit = 1;
    for (char c : s) {
        if (c == 'B') {
            value += bit;
        }
        bit <<= 1;
    }

    ensuref(value + d < (1LL << s.size()),
            "rightmost rune changes from B to A within D days: value=%lld D=%d length=%d",
            value, d, static_cast<int>(s.size()));

    inf.readEof();
}
