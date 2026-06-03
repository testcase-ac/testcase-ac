#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

string randomFromAlphabet(int length, const string& alphabet) {
    string s;
    for (int i = 0; i < length; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

string randomPrintable(int length) {
    string s;
    for (int i = 0; i < length; ++i) {
        s += char(rnd.next(32, 126));
    }
    return s;
}

string makeLine(int mode) {
    static const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const string alnum = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static const string punctuation = ".,!?;:'\"-()[]{}";

    if (mode == 0) {
        int words = rnd.next(1, 6);
        string s;
        for (int i = 0; i < words; ++i) {
            if (i > 0) {
                s += string(rnd.next(1, 3), ' ');
            }
            s += randomFromAlphabet(rnd.next(1, 10), alnum);
            if (rnd.next(0, 2) == 0) {
                s += rnd.any(punctuation);
            }
        }
        return s;
    }

    if (mode == 1) {
        int innerLength = rnd.next(1, 40);
        return string(rnd.next(1, 5), ' ') + randomFromAlphabet(innerLength, alnum + punctuation + " ") +
               string(rnd.next(1, 5), ' ');
    }

    if (mode == 2) {
        string half = randomFromAlphabet(rnd.next(1, 20), letters + " ");
        string s = half;
        if (rnd.next(0, 1) == 1) {
            s += rnd.any(letters);
        }
        for (int i = int(half.size()) - 1; i >= 0; --i) {
            s += half[i];
        }
        return s;
    }

    if (mode == 3) {
        return randomPrintable(rnd.next(60, 80));
    }

    return string(1, char(rnd.next(32, 126)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int lineCount = rnd.next(1, 12);
    for (int i = 0; i < lineCount; ++i) {
        string line;
        do {
            line = makeLine(rnd.next(0, 4));
        } while (line == "***" || line.empty() || int(line.size()) > 80);
        println(line);
    }
    println("***");

    return 0;
}
