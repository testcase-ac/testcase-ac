#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

char randomChar(const string& alphabet) {
    return alphabet[rnd.next((int)alphabet.size())];
}

string randomString(int n, const string& alphabet) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += randomChar(alphabet);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string digits = "0123456789";
    const string all = letters + digits;

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        int n = rnd.next(1, 50);
        s = randomString(n, all);
    } else if (mode == 1) {
        int blocks = rnd.next(1, 12);
        for (int i = 0; i < blocks && (int)s.size() + 3 <= 50; ++i) {
            s += "PS";
            s += rnd.next(0, 1) ? '5' : '4';
            if ((int)s.size() < 50 && rnd.next(0, 2) == 0) {
                s += randomChar(letters);
            }
        }
    } else if (mode == 2) {
        s = randomString(rnd.next(0, 8), letters);
        int repeats = rnd.next(1, 12);
        for (int i = 0; i < repeats && (int)s.size() < 50; ++i) {
            s += rnd.any(vector<string>{"P", "S", "PS", "PS4", "PS5", "4", "5"});
            if ((int)s.size() > 50) {
                s.resize(50);
            }
        }
    } else if (mode == 3) {
        int prefix = rnd.next(0, 15);
        s = randomString(prefix, letters);
        s += "PS";
        int suffix = rnd.next(1, 50 - (int)s.size());
        for (int i = 0; i < suffix; ++i) {
            s += randomChar(digits);
        }
    } else if (mode == 4) {
        int n = rnd.next(1, 50);
        const string safe = "ABCDEFGHIJKLMNOQRTUVWXYZ01236789";
        s = randomString(n, safe);
    } else {
        vector<string> pieces = {"PS4", "PS5", "PSS4", "PS45", "APS4", "PSA", "4PS", "5PS"};
        while ((int)s.size() < 50) {
            string piece = rnd.any(pieces);
            if ((int)s.size() + (int)piece.size() > 50) {
                break;
            }
            s += piece;
            if (rnd.next(0, 2) == 0 && (int)s.size() < 50) {
                s += randomChar(all);
            }
        }
        if (s.empty()) {
            s = "A";
        }
    }

    println((int)s.size());
    println(s);
    return 0;
}
