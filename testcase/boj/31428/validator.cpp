#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        string track = inf.readToken("[CSIA]", "friend_track");
    }
    inf.readEoln();

    string target = inf.readToken("[CSIA]", "target_track");
    inf.readEoln();

    inf.readEof();
}
