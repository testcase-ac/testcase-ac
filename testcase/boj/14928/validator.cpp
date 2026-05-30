#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string n = inf.readToken("[0-9]{1,1000001}", "N");
    ensuref(n == "0" || n[0] != '0', "N must be in canonical decimal form");
    if (n.size() == 1000001) {
        ensuref(n[0] == '1', "N must be at most 10^1000000");
        for (int i = 1; i < (int)n.size(); ++i) {
            ensuref(n[i] == '0', "N must be at most 10^1000000");
        }
    }
    inf.readEoln();
    inf.readEof();
    return 0;
}
