#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    string m = inf.readLine("[01]+", "m");
    ensuref((int)m.size() == n, "m length must be n: expected %d, found %d", n, (int)m.size());

    inf.readInt(0, 1000000, "k");
    inf.readEoln();
    inf.readEof();
}
