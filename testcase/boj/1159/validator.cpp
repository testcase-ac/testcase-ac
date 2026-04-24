#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of players
    int N = inf.readInt(1, 150, "N");
    inf.readEoln();

    // Read each surname: lowercase letters only, length 1 to 30
    for (int i = 0; i < N; i++) {
        inf.readLine("[a-z]{1,30}", "surname");
    }

    // No extra data
    inf.readEof();
    return 0;
}
