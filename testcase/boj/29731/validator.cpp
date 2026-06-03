#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string s = inf.readLine("[A-Za-z\\ ]{1,50}", "S_i");
        ensuref(s.front() != ' ', "S_%d starts with a space", i);
        ensuref(s.back() != ' ', "S_%d ends with a space", i);
    }

    inf.readEof();
    return 0;
}
