#include "testlib.h"
#include <cctype>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int W = inf.readInt(2, 27, "W");
    inf.readEoln();

    string P = inf.readLine();
    ensuref(!P.empty(), "P must not be empty");
    ensuref(P.front() != ' ' && P.back() != ' ',
            "P must not have leading or trailing spaces");

    ensuref((int)P.size() < 70000,
            "Length of P must be less than 70000, but got %d", (int)P.size());

    for (int i = 0; i < (int)P.size(); i++) {
        unsigned char c = static_cast<unsigned char>(P[i]);
        bool ok = (c >= 'A' && c <= 'Z') || c == ' ' || ispunct(c);
        ensuref(ok,
                "Invalid character in P at position %d: '%c'", i, c);
    }

    inf.readEof();
    return 0;
}
