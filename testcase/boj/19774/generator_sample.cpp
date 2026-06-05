#include "testlib.h"

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string codeFromParts(int ab, int cd) {
    ostringstream out;
    out << setw(2) << setfill('0') << ab << setw(2) << setfill('0') << cd;
    return out.str();
}

bool isPossible(int ab, int cd) {
    return (ab * ab + cd * cd) % 7 == 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> yesCodes;
    vector<string> noCodes;
    for (int ab = 0; ab <= 99; ++ab) {
        for (int cd = 0; cd <= 99; ++cd) {
            if (isPossible(ab, cd)) {
                yesCodes.push_back(codeFromParts(ab, cd));
            } else {
                noCodes.push_back(codeFromParts(ab, cd));
            }
        }
    }

    int mode = rnd.next(0, 5);
    int t = 0;
    if (mode == 0) {
        t = rnd.next(1, 12);
    } else if (mode == 1) {
        t = rnd.next(8, 30);
    } else if (mode == 2) {
        t = rnd.next(20, 80);
    } else if (mode == 3) {
        t = rnd.next(3, 20);
    } else {
        t = rnd.next(90, 160);
    }

    vector<string> codes;
    codes.reserve(t);
    for (int i = 0; i < t; ++i) {
        int kind = rnd.next(0, 99);
        if (mode == 0 && i < 3) {
            static const vector<string> edges = {"0000", "0001", "0100", "9999"};
            codes.push_back(edges[(i + rnd.next((int)edges.size())) % (int)edges.size()]);
        } else if (mode == 1 || kind < 25) {
            codes.push_back(rnd.any(yesCodes));
        } else if (mode == 2 || kind < 50) {
            codes.push_back(rnd.any(noCodes));
        } else if (mode == 3 || kind < 75) {
            int ab = rnd.next(0, 9);
            int cd = rnd.next(0, 99);
            if (rnd.next(0, 1) == 0) {
                codes.push_back(codeFromParts(ab, cd));
            } else {
                codes.push_back(codeFromParts(cd, ab));
            }
        } else {
            codes.push_back(codeFromParts(rnd.next(0, 99), rnd.next(0, 99)));
        }
    }

    shuffle(codes.begin(), codes.end());

    println(t);
    for (const string& code : codes) {
        println(code);
    }

    return 0;
}
