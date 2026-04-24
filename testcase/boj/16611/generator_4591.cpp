#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: length of known suffix / key prefix
    int n = rnd.next(1, 5);
    // Total message length
    int m = rnd.next(n + 1, min(n + 10, 100));

    // Hyper-parameter: alphabet size diversity
    vector<int> alphaSizes = {2, 3, 5, 26};
    int K = rnd.any(alphaSizes);

    // Build plaintext a[0..m-1]
    vector<int> a(m);
    bool periodic = (rnd.next(0, 4) == 0);
    if (periodic) {
        int period = rnd.next(1, min(3, m));
        for (int i = 0; i < period; i++)
            a[i] = rnd.next(0, K - 1);
        for (int i = period; i < m; i++)
            a[i] = a[i % period];
    } else {
        for (int i = 0; i < m; i++)
            a[i] = rnd.next(0, K - 1);
    }

    // Hyper-parameter: key distribution for the secret prefix
    bool key_full = rnd.next(0, 1) == 1;
    vector<int> key(m);

    // Initial key[0..n-1]
    for (int i = 0; i < n; i++) {
        if (key_full)
            key[i] = rnd.next(0, 25);
        else
            key[i] = rnd.next(0, K - 1);
    }
    // Autokey extension: key[i] = a[i-n]
    for (int i = n; i < m; i++)
        key[i] = a[i - n];

    // Compute ciphertext b and the known suffix of plaintext
    string suffix, cipher;
    suffix.reserve(n);
    cipher.reserve(m);
    for (int i = 0; i < m; i++) {
        int bi = (a[i] + key[i]) % 26;
        cipher.push_back(char('a' + bi));
    }
    for (int i = m - n; i < m; i++)
        suffix.push_back(char('a' + a[i]));

    // Output
    println(n, m);
    println(suffix);
    println(cipher);

    return 0;
}
