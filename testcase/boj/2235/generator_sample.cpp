#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomPermutation() {
    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    shuffle(letters.begin(), letters.end());
    return letters;
}

string randomDigits(int length, int mode) {
    string s;
    s.reserve(length);

    if (mode == 0) {
        for (int i = 0; i < length; ++i) {
            s.push_back(char('0' + rnd.next(0, 9)));
        }
    } else if (mode == 1) {
        while (static_cast<int>(s.size()) < length) {
            int x = rnd.next(0, 25);
            string token = x < 10 ? "0" + to_string(x) : to_string(x);
            s += token;
        }
        s.resize(length);
    } else if (mode == 2) {
        const vector<string> chunks = {"26", "27", "31", "52", "77", "99"};
        while (static_cast<int>(s.size()) < length) {
            s += rnd.any(chunks);
        }
        s.resize(length);
    } else {
        char a = char('0' + rnd.next(0, 9));
        char b = char('0' + rnd.next(0, 9));
        for (int i = 0; i < length; ++i) {
            s.push_back((i % 2 == 0) ? a : b);
        }
    }

    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int problemCount = rnd.next(1, 4);
    for (int problem = 0; problem < problemCount; ++problem) {
        println(randomPermutation());

        int sequenceCount = rnd.next(1, 5);
        for (int sequence = 0; sequence < sequenceCount; ++sequence) {
            int mode = rnd.next(0, 3);
            int length;
            if (sequence == 0 && rnd.next(0, 3) == 0) {
                length = 20;
            } else {
                length = rnd.next(3, 12);
            }
            println(randomDigits(length, mode));
        }
        println("0");
    }

    println("#");
    return 0;
}
