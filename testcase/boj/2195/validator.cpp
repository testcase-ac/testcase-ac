#include "testlib.h"

#include <array>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[A-Za-z0-9]{1,1000}", "S");
    inf.readEoln();
    string p = inf.readToken("[A-Za-z0-9]{1,1000}", "P");
    inf.readEoln();

    array<bool, 256> inS{};
    for (unsigned char ch : s) {
        inS[ch] = true;
    }

    for (int i = 0; i < int(p.size()); ++i) {
        ensuref(inS[static_cast<unsigned char>(p[i])],
                "P[%d] is not present in S: %c", i + 1, p[i]);
    }

    inf.readEof();
}
