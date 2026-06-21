#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    string s = inf.readToken("[BEF]{1,200000}", "S");
    ensuref((int)s.size() == n, "S length is %d, expected N=%d", (int)s.size(), n);
    inf.readEoln();

    inf.readEof();
}
