#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the four integers
    int h_p = inf.readInt(1, 2000, "h_p");
    inf.readSpace();
    int w_p = inf.readInt(1, 2000, "w_p");
    inf.readSpace();
    int h_m = inf.readInt(h_p, 2000, "h_m");
    inf.readSpace();
    int w_m = inf.readInt(w_p, 2000, "w_m");
    inf.readEoln();

    // Read h_p lines for the pattern
    for (int i = 0; i < h_p; ++i) {
        string s = inf.readLine("[xo]{"+to_string(w_p)+"}", "pattern line");
        ensuref((int)s.size() == w_p, "Pattern line %d has incorrect length: %d (expected %d)", i+1, (int)s.size(), w_p);
    }

    // Read h_m lines for the masterpiece
    for (int i = 0; i < h_m; ++i) {
        string s = inf.readLine("[xo]{"+to_string(w_m)+"}", "masterpiece line");
        ensuref((int)s.size() == w_m, "Masterpiece line %d has incorrect length: %d (expected %d)", i+1, (int)s.size(), w_m);
    }

    inf.readEof();
}
