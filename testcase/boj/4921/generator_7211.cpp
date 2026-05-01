#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

string make_valid_short() {
    // 1-4-2
    return "142";
}

string make_valid_loop() {
    // 1-5-(8-7)*k-8-6-2
    int k = rnd.next(0, 5);
    string s = "15";
    for (int i = 0; i < k; i++) {
        s += '8';
        s += '7';
    }
    s += '8';
    s += '6';
    s += '2';
    return s;
}

string make_valid() {
    if (rnd.next(0, 1) == 0)
        return make_valid_short();
    else
        return make_valid_loop();
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(5, 9);
    vector<string> tests;
    for (int i = 0; i < T; i++) {
        bool good = rnd.next(0, 1);
        if (good) {
            tests.push_back(make_valid());
        } else {
            int err = rnd.next(1, 4);
            if (err == 1) {
                // start error: replace first char of a valid with non-'1'
                string s = make_valid();
                vector<char> bads;
                for (char c = '2'; c <= '8'; c++) if (c != '1') bads.push_back(c);
                s[0] = rnd.any(bads);
                tests.push_back(s);
            } else if (err == 2) {
                // end error: replace last char of valid with non-'2'
                string s = make_valid();
                vector<char> bads;
                for (char c = '1'; c <= '8'; c++) if (c != '2') bads.push_back(c);
                s[s.size()-1] = rnd.any(bads);
                tests.push_back(s);
            } else if (err == 3) {
                // adjacency error: 1 -> mid (not 4/5) -> 2
                vector<char> mids;
                for (char c = '1'; c <= '8'; c++) {
                    if (c != '4' && c != '5') mids.push_back(c);
                }
                char m = rnd.any(mids);
                string s;
                s += '1';
                s += m;
                s += '2';
                tests.push_back(s);
            } else {
                // pairing error: missing a '6' for a '5'
                // take a loop valid and drop the '6'
                string s = make_valid_loop();
                // remove one '6' if exists, else append an extra '5'
                auto pos = s.find('6');
                if (pos != string::npos) {
                    s.erase(pos, 1);
                } else {
                    // ensure there's a 5 without 6
                    s = "15" + s + "2";
                }
                tests.push_back(s);
            }
        }
    }
    for (auto &s : tests) {
        println(s);
    }
    println("0");
    return 0;
}
