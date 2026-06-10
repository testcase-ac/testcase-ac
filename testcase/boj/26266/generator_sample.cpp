#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char enc(char plain, char key) {
    int p = plain - 'A';
    int k = key - 'A';
    return char('A' + (p + k + 1) % 26);
}

string randomString(int n, int alphabetSize) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(char('A' + rnd.next(0, alphabetSize - 1)));
    }
    return s;
}

bool hasSmallerPeriod(const string& s) {
    int n = static_cast<int>(s.size());
    for (int p = 1; p < n; ++p) {
        if (n % p != 0) continue;
        bool ok = true;
        for (int i = p; i < n; ++i) {
            if (s[i] != s[i % p]) {
                ok = false;
                break;
            }
        }
        if (ok) return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> lengths = {1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 18, 20, 24, 30, 36, 48, 60, 72, 90, 120};
    int n = rnd.any(lengths);

    vector<int> divisors;
    for (int d = 1; d <= n; ++d) {
        if (n % d == 0) divisors.push_back(d);
    }

    int mode = rnd.next(0, 4);
    int keyLen;
    if (mode == 0) {
        keyLen = 1;
    } else if (mode == 1) {
        keyLen = n;
    } else if (mode == 2) {
        vector<int> middle;
        for (int d : divisors) {
            if (d > 1 && d < n) middle.push_back(d);
        }
        keyLen = middle.empty() ? n : rnd.any(middle);
    } else {
        keyLen = rnd.any(divisors);
    }

    int keyAlphabet = keyLen == 1 ? rnd.next(1, 26) : rnd.next(2, 26);
    string key;
    int attempts = 0;
    do {
        key = randomString(keyLen, keyAlphabet);
        ++attempts;
    } while (keyLen > 1 && hasSmallerPeriod(key) && attempts < 100);

    string plaintext;
    int textMode = rnd.next(0, 4);
    if (textMode == 0) {
        plaintext = string(n, char('A' + rnd.next(0, 25)));
    } else if (textMode == 1) {
        plaintext = randomString(n, rnd.next(1, 3));
    } else if (textMode == 2) {
        plaintext = randomString(n, 26);
    } else if (textMode == 3) {
        string block = randomString(rnd.next(1, min(6, n)), rnd.next(2, 26));
        for (int i = 0; i < n; ++i) {
            plaintext.push_back(block[i % static_cast<int>(block.size())]);
        }
    } else {
        plaintext.reserve(n);
        for (int i = 0; i < n; ++i) {
            plaintext.push_back(char('A' + (i + rnd.next(0, 25)) % 26));
        }
    }

    string ciphertext;
    ciphertext.reserve(n);
    for (int i = 0; i < n; ++i) {
        ciphertext.push_back(enc(plaintext[i], key[i % keyLen]));
    }

    println(plaintext);
    println(ciphertext);

    return 0;
}
