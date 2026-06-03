#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string word = inf.readToken("[wolf]{1,50}", "word");
    ensuref(!word.empty(), "word must be nonempty");
    inf.readEoln();
    inf.readEof();
}
