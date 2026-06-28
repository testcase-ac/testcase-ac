#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300000, "n");
    inf.readEoln();

    string commands = inf.readToken("[LRDU]{2,300000}", "commands");
    ensuref((int)commands.size() == n,
            "commands length must equal n: length=%d n=%d",
            (int)commands.size(), n);
    inf.readEoln();

    inf.readEof();
}
