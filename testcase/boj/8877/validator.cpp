#include "testlib.h"

#include <string>

using namespace std;

bool isConnectorLabel(const string& s, int pos) {
    if (s[pos] == '0' && s[pos + 1] == '0') {
        return true;
    }
    return 'A' <= s[pos] && s[pos] <= 'Z' &&
           (s[pos + 1] == '+' || s[pos + 1] == '-');
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 40000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        string molecule = inf.readToken("[0-9A-Z+-]{8}", "molecule");
        for (int pos = 0; pos < 8; pos += 2) {
            ensuref(isConnectorLabel(molecule, pos),
                    "invalid connector label at molecule %d position %d: %c%c",
                    i + 1, pos / 2 + 1, molecule[pos], molecule[pos + 1]);
        }
    }
    inf.readEoln();
    inf.readEof();
}
