#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char nonAChar(bool preferN) {
    if (preferN && rnd.next(100) < 35) return 'N';
    string letters = "BCDEFGHIJKLMOPQRSTUVWXYZ";
    return rnd.any(letters);
}

string randomUppercase(int n) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(char('A' + rnd.next(26)));
    }
    return s;
}

string noAString(int n) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(nonAChar(true));
    }
    return s;
}

string alternatingClusters(int n) {
    string s;
    s.reserve(n);
    while ((int)s.size() < n) {
        int block = rnd.next(1, 5);
        if (rnd.next(100) < 45) {
            s.push_back('A');
            for (int i = 1; i < block && (int)s.size() < n; ++i) {
                s.push_back(nonAChar(true));
            }
        } else {
            for (int i = 0; i < block && (int)s.size() < n; ++i) {
                s.push_back(nonAChar(true));
            }
        }
    }
    return s;
}

string anaRichString(int n) {
    vector<string> chunks;
    int remaining = n;
    while (remaining > 0) {
        if (remaining >= 3 && rnd.next(100) < 60) {
            int len = rnd.next(3, min(remaining, 12));
            string chunk(len, 'B');
            chunk.front() = 'A';
            chunk.back() = 'A';
            int npos = rnd.next(1, len - 2);
            chunk[npos] = 'N';
            for (int i = 1; i + 1 < len; ++i) {
                if (i != npos) chunk[i] = nonAChar(false);
            }
            chunks.push_back(chunk);
            remaining -= len;
        } else {
            int len = rnd.next(1, min(remaining, 6));
            string chunk = noAString(len);
            chunks.push_back(chunk);
            remaining -= len;
        }
    }

    string s;
    for (const string& chunk : chunks) s += chunk;
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    string s;

    if (mode == 0) {
        n = rnd.next(3, 8);
        s = randomUppercase(n);
    } else if (mode == 1) {
        n = rnd.next(3, 30);
        s = noAString(n);
    } else if (mode == 2) {
        n = rnd.next(3, 35);
        s = alternatingClusters(n);
    } else if (mode == 3) {
        n = rnd.next(3, 40);
        s = anaRichString(n);
    } else if (mode == 4) {
        n = rnd.next(70, 100);
        s = rnd.next(2) ? alternatingClusters(n) : anaRichString(n);
    } else {
        n = rnd.next(3, 100);
        s = randomUppercase(n);
    }

    println(n);
    println(s);
    return 0;
}
