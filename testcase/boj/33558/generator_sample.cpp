#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> methods = {"clamp-to-edge", "repeat", "mirrored-repeat"};
    string method = rnd.any(methods);

    int mode = rnd.next(0, 6);
    int n;
    int m;
    int u;
    int v;

    if (mode == 0) {
        u = v = 1;
        n = rnd.next(1, 12);
        m = rnd.next(1, 12);
    } else if (mode == 1) {
        u = rnd.next(1, 8);
        v = rnd.next(1, 8);
        n = u;
        m = v;
    } else if (mode == 2) {
        u = rnd.next(2, 8);
        v = rnd.next(2, 8);
        n = rnd.next(1, u);
        m = rnd.next(1, v);
    } else if (mode == 3) {
        u = rnd.next(1, 7);
        v = rnd.next(1, 7);
        n = rnd.next(u + 1, min(200, u * 3 + 3));
        m = rnd.next(v + 1, min(200, v * 3 + 3));
    } else if (mode == 4) {
        u = rnd.next(1, 10);
        v = rnd.next(1, 10);
        n = rnd.next(1, min(200, u * 4 + 5));
        m = rnd.next(1, min(200, v * 4 + 5));
    } else if (mode == 5) {
        u = rnd.next(1, 6);
        v = rnd.next(1, 6);
        n = rnd.next(40, 80);
        m = rnd.next(40, 80);
    } else {
        u = rnd.next(20, 80);
        v = rnd.next(20, 80);
        n = rnd.next(1, 15);
        m = rnd.next(1, 15);
    }

    string alphabet;
    int alphabetMode = rnd.next(0, 3);
    if (alphabetMode == 0) {
        alphabet = "01";
    } else if (alphabetMode == 1) {
        alphabet = "0123456789";
    } else if (alphabetMode == 2) {
        alphabet = "ABCdef123";
    } else {
        alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    }

    vector<string> texture(u, string(v, 'A'));
    int pattern = rnd.next(0, 4);
    for (int i = 0; i < u; ++i) {
        for (int j = 0; j < v; ++j) {
            if (pattern == 0) {
                texture[i][j] = alphabet[(i + j) % alphabet.size()];
            } else if (pattern == 1) {
                texture[i][j] = alphabet[(i * 17 + j * 31) % alphabet.size()];
            } else if (pattern == 2) {
                texture[i][j] = alphabet[(i == 0 || j == 0 || i == u - 1 || j == v - 1) % alphabet.size()];
            } else if (pattern == 3) {
                texture[i][j] = alphabet[(i * v + j) % alphabet.size()];
            } else {
                texture[i][j] = rnd.any(alphabet);
            }
        }
    }

    println(n, m);
    println(u, v);
    for (const string& row : texture) {
        println(row);
    }
    println(method);

    return 0;
}
