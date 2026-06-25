#include "testlib.h"

#include <cctype>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string n = inf.readToken("[^ \n]{3,19}", "N");
    inf.readEoln();
    inf.readEof();

    size_t dot = n.find('.');
    ensuref(dot != string::npos, "N must contain a decimal point: %s", n.c_str());
    ensuref(n.find('.', dot + 1) == string::npos,
            "N must contain exactly one decimal point: %s", n.c_str());
    ensuref(dot > 0, "N must have an integer part: %s", n.c_str());
    ensuref(dot + 2 == n.size(),
            "N must be given to exactly one decimal place: %s", n.c_str());
    ensuref(isdigit(n[dot + 1]), "N fractional digit is invalid: %s", n.c_str());

    if (dot == 1) {
        ensuref(isdigit(n[0]), "N integer part is invalid: %s", n.c_str());
    } else {
        ensuref(n[0] != '0', "N has a leading zero: %s", n.c_str());
        for (size_t i = 0; i < dot; ++i) {
            ensuref(isdigit(n[i]), "N integer part is invalid: %s", n.c_str());
        }
    }

    __int128 scaled = 0;
    for (size_t i = 0; i < dot; ++i) {
        scaled = scaled * 10 + (n[i] - '0');
    }
    scaled = scaled * 10 + (n[dot + 1] - '0');

    const __int128 upper = (__int128)10000000000000001LL * 10;
    ensuref(0 <= scaled && scaled < upper, "N is out of range: %s", n.c_str());
}
