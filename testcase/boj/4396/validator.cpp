#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "n");
    inf.readEoln();

    vector<string> mine(n);
    for (int i = 0; i < n; ++i) {
        mine[i] = inf.readLine("[.*]{" + to_string(n) + "}", "mine_row");
    }

    for (int i = 0; i < n; ++i) {
        inf.readLine("[.x]{" + to_string(n) + "}", "opened_row");
    }

    inf.readEof();
}
