#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    string path = inf.readToken("[NESW]{1,1000}", "path");
    ensuref((int)path.size() == n, "path length must equal N: expected %d, found %d", n, (int)path.size());
    inf.readEoln();

    inf.readEof();
}
