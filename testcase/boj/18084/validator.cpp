#include "testlib.h"

#include <cctype>
#include <string>

using namespace std;

int readTimeCents(const char* name) {
    string s = inf.readToken("[0-9]{1,2}\\.[0-9]{2}", name);

    ensuref(s[0] != '0' || s[1] == '.',
            "%s has a leading zero in the integer part: %s", name, s.c_str());

    int dot = s.find('.');
    int whole = 0;
    for (int i = 0; i < dot; ++i) {
        ensuref(isdigit(static_cast<unsigned char>(s[i])),
                "%s has a non-digit in the integer part: %s", name, s.c_str());
        whole = whole * 10 + (s[i] - '0');
    }

    int cents = whole * 100 + (s[dot + 1] - '0') * 10 + (s[dot + 2] - '0');
    ensuref(100 <= cents && cents <= 2000,
            "%s must be between 1.00 and 20.00 inclusive: %s", name, s.c_str());
    return cents;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    readTimeCents("t_1");
    inf.readSpace();
    readTimeCents("t_2");
    inf.readSpace();
    readTimeCents("t_3");
    inf.readSpace();
    readTimeCents("t_4");
    inf.readEoln();

    readTimeCents("t");
    inf.readEoln();

    inf.readEof();
}
