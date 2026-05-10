#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 1;
    const int N_MAX = 500000;

    int n = inf.readInt(N_MIN, N_MAX, "N");
    inf.readEoln();

    string s = inf.readToken("[HO]+", "S");
    inf.readEoln();

    ensuref((int)s.size() == n,
            "Length of string S (%d) does not match given N (%d)", (int)s.size(), n);

    inf.readEof();
}
