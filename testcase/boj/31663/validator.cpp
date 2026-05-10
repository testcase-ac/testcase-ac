#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of words
    int N = inf.readInt(2, 1000, "N");
    inf.readEoln();

    // Read each word: must be 1 to 45 lowercase letters
    for (int i = 0; i < N; i++) {
        inf.readLine("[a-z]{1,45}", "word");
    }

    inf.readEof();
    return 0;
}
