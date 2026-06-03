#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readLine("[()1]{3}", "S");
    ensuref(count(s.begin(), s.end(), '(') == 1, "S must contain exactly one '('");
    ensuref(count(s.begin(), s.end(), '1') == 1, "S must contain exactly one '1'");
    ensuref(count(s.begin(), s.end(), ')') == 1, "S must contain exactly one ')'");

    inf.readEof();
}
