#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int length;
    if (mode == 0) {
        length = rnd.next(10, 14);
    } else if (mode == 1) {
        length = rnd.next(15, 30);
    } else if (mode == 2) {
        length = rnd.next(31, 60);
    } else if (mode == 3) {
        length = rnd.next(61, 100);
    } else {
        vector<int> edges = {10, 11, 99, 100};
        length = rnd.any(edges);
    }

    string plain = "CHICKENS";
    while (int(plain.size()) < length) {
        if (mode == 0) {
            plain += rnd.any(string("CHICKENS"));
        } else if (mode == 1) {
            plain += char('A' + rnd.next(0, 3));
        } else if (mode == 2) {
            plain += char('A' + rnd.next(0, 25));
        } else if (mode == 3) {
            plain += rnd.any(string("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
        } else {
            plain += rnd.any(string("AEIOUBCDFGHJKLMNPQRSTVWXYZ"));
        }
    }

    vector<int> keys;
    for (int key = 0; key < 128; ++key) {
        bool ok = true;
        for (char ch : plain) {
            int encrypted = int(ch) ^ key;
            if (encrypted < 33 || encrypted > 126) {
                ok = false;
                break;
            }
        }
        if (ok) {
            keys.push_back(key);
        }
    }

    int key = rnd.any(keys);
    string encrypted;
    for (char ch : plain) {
        encrypted += char(int(ch) ^ key);
    }

    println(encrypted);

    return 0;
}
