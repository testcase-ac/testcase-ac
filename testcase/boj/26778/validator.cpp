#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string word = inf.readToken("[a-z]+", "word");
    ensuref(word.size() <= 1000000, "word length must not exceed 1000000");
    inf.readEoln();
    inf.readEof();
}
