#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[()]{1,100000}", "S");
    inf.readEoln();

    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    int n = static_cast<int>(s.size());
    for (int q = 1; q <= m; ++q) {
        int i = inf.readInt(1, n, "i");
        inf.readSpace();
        int j = inf.readInt(i, n, "j");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
