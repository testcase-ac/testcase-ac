#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    string k = inf.readToken("[01]{1,1000000}", "K");
    ensuref((int)k.size() == n, "K length must be N: N=%d, length=%d", n, (int)k.size());
    ensuref(k[0] == '1', "K must not have a leading zero");
    inf.readEoln();

    inf.readEof();
}
