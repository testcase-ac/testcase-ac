#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();
    // Read N hex tokens, each must be 1 or 2 hex digits, value in [0,127]
    for (int i = 0; i < N; i++) {
        // Accept uppercase or lowercase hex digits
        string tok = inf.readToken("[0-9a-fA-F]{1,2}", "cipher_i");
        // parse hex
        int val = 0;
        for (char c : tok) {
            val *= 16;
            if (c >= '0' && c <= '9') {
                val += c - '0';
            } else if (c >= 'A' && c <= 'F') {
                val += c - 'A' + 10;
            } else { // 'a' - 'f'
                val += c - 'a' + 10;
            }
        }
        ensuref(val >= 0 && val <= 127,
                "cipher_%d parsed value %d not in [0,127]", i, val);
        if (i + 1 < N)
            inf.readSpace();
    }
    inf.readEoln();
    inf.readEof();
    return 0;
}
