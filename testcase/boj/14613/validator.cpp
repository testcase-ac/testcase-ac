#include "testlib.h"

#include <string>

using namespace std;

int readProbability(const char* name) {
    string token = inf.readToken("[0-9]|[0-9][.][0-9]{1,2}", name);

    int whole = token[0] - '0';
    int cents = whole * 100;
    if (token.size() > 1) {
        cents = whole * 100 + (token[2] - '0') * 10;
        if (token.size() == 4) {
            cents += token[3] - '0';
        }
    }

    ensuref(0 <= cents && cents <= 100, "%s must be between 0 and 1: %s", name, token.c_str());
    return cents;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int w = readProbability("W");
    inf.readSpace();
    int l = readProbability("L");
    inf.readSpace();
    int d = readProbability("D");
    inf.readEoln();

    ensuref(w + l + d == 100, "W + L + D must be 1.00, got %.2f", (w + l + d) / 100.0);

    inf.readEof();
}
