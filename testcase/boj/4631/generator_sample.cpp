#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeName(int length, int caseIndex, int nameIndex, int style) {
    const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_";
    string s;
    s.reserve(length);

    if (style == 0) {
        char c = char('A' + (caseIndex + nameIndex) % 26);
        s.assign(length, c);
    } else if (style == 1) {
        for (int i = 0; i < length; ++i) {
            s.push_back(alphabet[(caseIndex * 17 + nameIndex * 7 + i) % (int)alphabet.size()]);
        }
    } else {
        s = "N";
        while ((int)s.size() < length) {
            s.push_back(alphabet[rnd.next((int)alphabet.size())]);
        }
    }

    return s;
}

vector<int> chooseLengths(int n, int mode) {
    vector<int> lengths(n);

    if (mode == 0) {
        int len = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) lengths[i] = len;
    } else if (mode == 1) {
        int start = rnd.next(1, 25 - n + 1);
        for (int i = 0; i < n; ++i) lengths[i] = start + i;
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) lengths[i] = rnd.next(1, 25);
        sort(lengths.begin(), lengths.end());
    } else {
        for (int i = 0; i < n; ++i) {
            if (i < n / 3) lengths[i] = rnd.next(1, 3);
            else if (i < 2 * n / 3) lengths[i] = rnd.next(4, 12);
            else lengths[i] = rnd.next(13, 25);
        }
        sort(lengths.begin(), lengths.end());
    }

    return lengths;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sets = rnd.next(1, 6);
    for (int tc = 1; tc <= sets; ++tc) {
        int n;
        int shape = rnd.next(0, 5);
        if (shape == 0) n = 1;
        else if (shape == 1) n = 2;
        else if (shape == 2) n = 15;
        else if (shape == 3) n = rnd.next(3, 7);
        else n = rnd.next(8, 14);

        int mode = rnd.next(0, 3);
        vector<int> lengths = chooseLengths(n, mode);

        println(n);
        int style = rnd.next(0, 2);
        for (int i = 0; i < n; ++i) {
            println(makeName(lengths[i], tc, i, style));
        }
    }

    println(0);
    return 0;
}
