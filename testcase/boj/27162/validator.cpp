#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string available = inf.readToken("[YN]{12}", "available");
    inf.readEoln();

    bool has_available_category = false;
    for (char c : available) {
        has_available_category |= c == 'Y';
    }
    ensuref(has_available_category, "at least one category must be available");

    inf.readInt(1, 6, "d1");
    inf.readSpace();
    inf.readInt(1, 6, "d2");
    inf.readSpace();
    inf.readInt(1, 6, "d3");
    inf.readEoln();

    inf.readEof();
}
