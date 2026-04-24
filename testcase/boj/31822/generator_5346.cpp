#include "testlib.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
using namespace std;

string genDigits(int len) {
    string s;
    for (int i = 0; i < len; i++)
        s.push_back(char('0' + rnd.next(0, 9)));
    return s;
}

string genCode(const string &pref5) {
    static const string alnum = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string s = pref5;
    // 6th digit
    s.push_back(char('0' + rnd.next(0,9)));
    // 7th char: letter or digit
    s.push_back(rnd.any(alnum));
    // 8th char: hyphen
    s.push_back('-');
    // last two digits
    s.push_back(char('0' + rnd.next(0,9)));
    s.push_back(char('0' + rnd.next(0,9)));
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters
    // Choose N
    int N = rnd.next(1, 16);
    // Target prefix and code
    string target_pref5 = genDigits(5);
    string target_code = genCode(target_pref5);
    // Determine how many matches we try to include
    int maxMatch = rnd.next(0, N);
    double pMatch = rnd.next(0.0, 1.0);
    int countMatch = 0;

    unordered_set<string> used;
    used.insert(target_code);
    vector<string> codes;
    // Generate N distinct codes
    for (int i = 0; i < N; i++) {
        bool wantMatch = false;
        if (countMatch < maxMatch && rnd.next() < pMatch) {
            wantMatch = true;
        }
        string code;
        if (wantMatch) {
            code = genCode(target_pref5);
        } else {
            // generate different prefix
            string p;
            do {
                p = genDigits(5);
            } while (p == target_pref5);
            code = genCode(p);
        }
        // ensure uniqueness
        if (used.count(code)) {
            i--;
            continue;
        }
        used.insert(code);
        if (wantMatch) countMatch++;
        codes.push_back(code);
    }
    // Shuffle output list
    shuffle(codes.begin(), codes.end());

    // Output
    println(target_code);
    println(N);
    for (auto &c : codes) println(c);

    return 0;
}
