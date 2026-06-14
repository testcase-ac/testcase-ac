#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int pairs = rnd.next(1, 20);
    if (mode == 5) {
        pairs = rnd.next(20, 80);
    }

    int n = 2 * pairs;
    int k = rnd.next(2, 80);
    string s(n, '2');

    const string chars = "23E";
    vector<pair<char, char>> pairTypes = {
        {'2', '2'}, {'2', '3'}, {'3', '3'},
        {'2', 'E'}, {'3', 'E'}, {'E', 'E'},
    };

    for (int i = 0; i < pairs; ++i) {
        char left = '2';
        char right = '2';

        if (mode == 0) {
            left = rnd.any(chars);
            right = rnd.any(chars);
        } else if (mode == 1) {
            if (rnd.next(0, 1) == 0) {
                left = right = '2';
            } else {
                left = '3';
                right = 'E';
            }
        } else if (mode == 2) {
            if (rnd.next(0, 1) == 0) {
                left = right = '3';
            } else {
                left = right = 'E';
            }
        } else if (mode == 3) {
            pair<char, char> p = rnd.any(pairTypes);
            left = p.first;
            right = p.second;
            if (rnd.next(0, 1) == 0) {
                swap(left, right);
            }
        } else if (mode == 4) {
            if (i % 3 == 0) {
                left = '2';
                right = '3';
            } else if (i % 3 == 1) {
                left = '2';
                right = 'E';
            } else {
                left = rnd.any(chars);
                right = rnd.any(chars);
            }
        } else {
            int roll = rnd.next(0, 99);
            if (roll < 50) {
                left = '3';
                right = 'E';
            } else if (roll < 70) {
                left = right = '2';
            } else if (roll < 85) {
                left = '2';
                right = '3';
            } else {
                left = '2';
                right = 'E';
            }
        }

        s[i] = left;
        s[n - 1 - i] = right;
    }

    if (rnd.next(0, 4) == 0) {
        k = rnd.next(2, 500000);
    }

    println(n, k);
    println(s);

    return 0;
}
