#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Length of string
    int N = rnd.next(1, 30);
    // Generation style
    int style = rnd.next(0, 3);

    string alph = "abcdefghijklmnopqrstuvwxyz";
    string target = "sogang";
    string rtarget = string(target.rbegin(), target.rend());
    string S;

    if (style == 0) {
        // Completely random string
        for (int i = 0; i < N; i++) {
            S += rnd.any(alph);
        }
    } else if (style == 1) {
        // Block style: clusters of target letters in order, then noise
        int avg = N / 6;
        for (char c : target) {
            int cnt = rnd.next(0, avg + 1);
            S.append(cnt, c);
        }
        while ((int)S.size() < N) {
            S += rnd.any(alph);
        }
        if ((int)S.size() > N) S.resize(N);
    } else if (style == 2) {
        // Repeated full target words, then noise
        int maxk = max(1, N / 6);
        int k = rnd.next(1, maxk);
        for (int i = 0; i < k; i++) {
            S += target;
        }
        while ((int)S.size() < N) {
            S += rnd.any(alph);
        }
        if ((int)S.size() > N) S.resize(N);
    } else {
        // Reversed-block style: clusters of reversed target letters, then noise
        int avg = N / 6;
        for (char c : rtarget) {
            int cnt = rnd.next(0, avg + 1);
            S.append(cnt, c);
        }
        while ((int)S.size() < N) {
            S += rnd.any(alph);
        }
        if ((int)S.size() > N) S.resize(N);
    }

    // Output
    println(N);
    println(S);

    return 0;
}
