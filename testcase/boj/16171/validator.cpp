#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[a-zA-Z0-9]{1,100}", "S");
    inf.readEoln();

    string k = inf.readToken("[a-zA-Z]{1,100}", "K");
    inf.readEoln();

    ensuref(k.size() <= s.size(), "|K| must be at most |S|, got %zu > %zu",
            k.size(), s.size());

    inf.readEof();
}
