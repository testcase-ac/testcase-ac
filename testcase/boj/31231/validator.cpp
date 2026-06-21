#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 400, "N");
    inf.readEoln();

    string a = inf.readToken("[1-9]{1,400}", "a");
    ensuref((int)a.size() == n, "a length must be N: expected %d, got %d", n, (int)a.size());
    inf.readEoln();

    inf.readEof();
}
