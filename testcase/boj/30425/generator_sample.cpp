#include "testlib.h"

#include <string>

using namespace std;

char randomChar(const string& alphabet) {
    return alphabet[rnd.next(static_cast<int>(alphabet.size()))];
}

string randomString(int n, const string& alphabet) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += randomChar(alphabet);
    }
    return s;
}

string periodicString(int n, int period, const string& alphabet) {
    string base = randomString(period, alphabet);
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += base[i % period];
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    string song;

    if (mode == 0) {
        n = rnd.next(1, 4);
        song = randomString(n, "ABC");
    } else if (mode == 1) {
        n = rnd.next(1, 30);
        song = string(n, rnd.next('A', 'Z'));
    } else if (mode == 2) {
        n = rnd.next(2, 40);
        int period = rnd.next(1, n);
        song = periodicString(n, period, "ABCD");
    } else if (mode == 3) {
        n = rnd.next(6, 60);
        int period = rnd.next(1, 10);
        song = periodicString(n, period, "ABC");
        int pos = rnd.next(n);
        char old = song[pos];
        do {
            song[pos] = randomChar("ABCDEF");
        } while (song[pos] == old);
    } else if (mode == 4) {
        int blockSize = rnd.next(1, 8);
        int blocks = rnd.next(2, 10);
        string block = randomString(blockSize, "ABCDE");
        song.clear();
        for (int i = 0; i < blocks; ++i) {
            song += block;
        }
        n = static_cast<int>(song.size());
    } else {
        n = rnd.next(20, 100);
        string alphabet = rnd.next(2) == 0 ? "ABCDEFGHIJKLMNOPQRSTUVWXYZ" : "ABCDE";
        song = randomString(n, alphabet);
    }

    println(n);
    println(song);

    return 0;
}
