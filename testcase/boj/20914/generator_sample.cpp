#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

const string KEYS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const vector<string> ROWS = {"QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM"};
const vector<string> ADJ = {
    "SQ",    "WSZ",   "DE",    "FRX",   "GTVC", "HYB",   "JU",   "KI",   "LO",   "P",
    "AW",    "QSEA",  "WDR",   "ESFT",  "RDGY", "TFHU",  "YGIJ", "UHKO", "IJL",  "OKP",
    "AS",    "SXDC",  "DFV",   "FCGB",  "GHN",  "HJBM",  "KM"
};

string randomString(int len, const string& alphabet) {
    string s;
    for (int i = 0; i < len; ++i) s += rnd.any(alphabet);
    return s;
}

string adjacentWalk(int len) {
    string s(1, rnd.any(KEYS));
    while ((int)s.size() < len) {
        int current = s.back() - 'A';
        s += rnd.any(ADJ[current]);
    }
    return s;
}

string rowWalk(int len) {
    string row = rnd.any(ROWS);
    int pos = rnd.next((int)row.size());
    int dir = rnd.next(2) == 0 ? -1 : 1;
    string s;
    for (int i = 0; i < len; ++i) {
        s += row[pos];
        if (rnd.next(4) != 0) pos += dir;
        if (pos < 0 || pos >= (int)row.size()) {
            dir = -dir;
            pos += 2 * dir;
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(7);
        int len = rnd.next(2, 30);
        if (rnd.next(10) == 0) len = rnd.next(80, 100);

        string s;
        if (mode == 0) {
            s = string(len, rnd.any(KEYS));
        } else if (mode == 1) {
            s = rowWalk(len);
        } else if (mode == 2) {
            s = adjacentWalk(len);
        } else if (mode == 3) {
            string extremes = "QPAZML";
            s = randomString(len, extremes);
        } else if (mode == 4) {
            string subset = rnd.any(ROWS);
            s = randomString(len, subset);
        } else if (mode == 5) {
            string alphabet = KEYS;
            shuffle(alphabet.begin(), alphabet.end());
            s = alphabet.substr(0, len);
            while ((int)s.size() < len) s += rnd.any(KEYS);
        } else {
            s = randomString(len, KEYS);
        }

        println(s);
    }

    return 0;
}
