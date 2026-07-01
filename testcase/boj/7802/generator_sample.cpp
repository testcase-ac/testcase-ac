#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

string randomCodewordMessage(int letters) {
    const vector<string> codes = {".--", "-.", "---", "..", "--..", "--.-", ".-."};
    string message;
    for (int i = 0; i < letters; ++i) {
        message += rnd.any(codes);
    }
    return message;
}

string randomSignal(int length) {
    string signal;
    for (int i = 0; i < length; ++i) {
        signal += rnd.next(2) == 0 ? '.' : '-';
    }
    return signal;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int lineCount = rnd.next(1, 18);
    for (int line = 0; line < lineCount; ++line) {
        int mode = rnd.next(0, 5);
        string signal;

        if (mode == 0) {
            signal = randomCodewordMessage(rnd.next(1, 10));
        } else if (mode == 1) {
            signal = randomSignal(rnd.next(1, 28));
        } else if (mode == 2) {
            signal = randomCodewordMessage(rnd.next(1, 6));
            signal += randomSignal(rnd.next(1, 5));
        } else if (mode == 3) {
            signal = randomSignal(rnd.next(1, 4));
            signal += randomCodewordMessage(rnd.next(1, 6));
        } else if (mode == 4) {
            string block = rnd.any(vector<string>{".", "-", "..", "---", ".-"});
            int repeats = rnd.next(1, 14);
            for (int i = 0; i < repeats; ++i) {
                signal += block;
            }
        } else {
            signal = randomCodewordMessage(rnd.next(1, 4));
            signal += randomSignal(rnd.next(1, 4));
            signal += randomCodewordMessage(rnd.next(1, 4));
        }

        println(signal);
    }

    return 0;
}
