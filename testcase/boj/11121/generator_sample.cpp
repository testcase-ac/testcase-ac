#include "testlib.h"

#include <string>

using namespace std;

string randomBinaryString(int length) {
    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i) {
        s.push_back(char('0' + rnd.next(0, 1)));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 25);
    if (rnd.next(10) == 0) {
        t = rnd.next(26, 100);
    }

    println(t);
    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int length = rnd.next(1, 30);
        if (rnd.next(20) == 0) {
            length = rnd.next(31, 119);
        }

        string input = randomBinaryString(length);
        string output = input;
        int mode = rnd.next(0, 4);

        if (mode == 1) {
            int pos = rnd.next(0, length - 1);
            output[pos] = output[pos] == '0' ? '1' : '0';
        } else if (mode == 2) {
            for (char& bit : output) {
                bit = bit == '0' ? '1' : '0';
            }
        } else if (mode == 3) {
            output = randomBinaryString(length);
        } else if (mode == 4) {
            int changes = rnd.next(1, length);
            for (int i = 0; i < changes; ++i) {
                int pos = rnd.next(0, length - 1);
                output[pos] = output[pos] == '0' ? '1' : '0';
            }
        }

        println(input, output);
    }

    return 0;
}
