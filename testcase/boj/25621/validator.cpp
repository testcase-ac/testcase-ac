#include "testlib.h"
#include <string>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K0
    int N = inf.readInt(1, 300000, "N");
    inf.readSpace();
    long long K0 = inf.readLong(0LL, 1000000000LL, "K0");
    inf.readEoln();

    // Each of the next N lines has two operations
    // Operation format: one of "+x", "-x", "*x", where 0 <= x <= 1e9
    for (int i = 1; i <= N; i++) {
        // Read first operation token
        string op1 = inf.readToken("[+*\\-][0-9]{1,10}", "op1");
        inf.readSpace();
        // Read second operation token
        string op2 = inf.readToken("[+*\\-][0-9]{1,10}", "op2");
        inf.readEoln();

        // Validate and parse op1
        char c1 = op1[0];
        // c1 is guaranteed by regex to be +, -, or *
        string s1 = op1.substr(1);
        // No leading '+' or '-' in s1, ensure it's digits only
        for (char ch : s1) {
            ensuref(ch >= '0' && ch <= '9',
                    "op1 contains non-digit in operand: \"%s\"", op1.c_str());
        }
        // Parse and check range
        long long x1 = 0;
        // stoll is safe since length <= 10
        try {
            x1 = stoll(s1);
        } catch (...) {
            ensuref(false, "Failed to parse integer in op1: \"%s\"", op1.c_str());
        }
        ensuref(0LL <= x1 && x1 <= 1000000000LL,
                "Operand out of range in op1: \"%s\"", op1.c_str());

        // Validate and parse op2
        char c2 = op2[0];
        string s2 = op2.substr(1);
        for (char ch : s2) {
            ensuref(ch >= '0' && ch <= '9',
                    "op2 contains non-digit in operand: \"%s\"", op2.c_str());
        }
        long long x2 = 0;
        try {
            x2 = stoll(s2);
        } catch (...) {
            ensuref(false, "Failed to parse integer in op2: \"%s\"", op2.c_str());
        }
        ensuref(0LL <= x2 && x2 <= 1000000000LL,
                "Operand out of range in op2: \"%s\"", op2.c_str());
    }

    inf.readEof();
    return 0;
}
