#include "testlib.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Level size
    int lv = rnd.next(6, 11);

    // Possible base directions
    vector<string> dirCodes = {"W","A","S","D","LU","LD","RU","RD"};
    // Opposite mapping for reverse keys
    map<string,string> opp = {
        {"W","S"}, {"S","W"}, {"A","D"}, {"D","A"},
        {"LU","RD"}, {"RD","LU"}, {"LD","RU"}, {"RU","LD"}
    };
    // Map actual direction to possible user input keys
    map<string, vector<char>> keyMap = {
        {"W", {'W','8'}}, {"S", {'S','2'}},
        {"A", {'A','4'}}, {"D", {'D','6'}},
        {"LU", {'7'}},    {"LD", {'1'}},
        {"RU", {'9'}},    {"RD", {'3'}}
    };
    // All possible input keys for junk
    vector<char> allKeys = {'W','8','A','4','S','2','D','6','7','1','9','3'};

    // Generate note tokens with optional reverse
    vector<string> noteTokens;
    for (int i = 0; i < lv; i++) {
        string d = rnd.any(dirCodes);
        bool rev = rnd.next(1, 10) <= 3; // ~30% reversed
        noteTokens.push_back(rev ? d + "!" : d);
    }
    // Compute the actual directions after considering reverse
    vector<string> actualDirs(lv);
    for (int i = 0; i < lv; i++) {
        string tok = noteTokens[i];
        if (tok.back() == '!') {
            string base = tok.substr(0, tok.size() - 1);
            actualDirs[i] = opp[base];
        } else {
            actualDirs[i] = tok;
        }
    }

    // Decide whether to make this a success (Yes) or failure (No) case
    bool wantSuccess = rnd.next(0, 1) == 1;

    // Build user input sequence
    string inp;
    if (wantSuccess) {
        // Optional random junk before match
        int pre = rnd.next(0, lv);
        for (int i = 0; i < pre; i++)
            inp.push_back(rnd.any(allKeys));
        // Exact matching sequence to reach full match at end
        for (auto &d : actualDirs)
            inp.push_back(rnd.any(keyMap[d]));
    } else {
        int failType = rnd.next(0, 1);
        if (failType == 0) {
            // Never reach full match: random junk then partial match
            int pre = rnd.next(0, lv);
            for (int i = 0; i < pre; i++)
                inp.push_back(rnd.any(allKeys));
            int part = rnd.next(0, lv - 1); // end with part < lv
            for (int i = 0; i < part; i++)
                inp.push_back(rnd.any(keyMap[actualDirs[i]]));
        } else {
            // Reach full match, then one extra key to reset
            int pre = rnd.next(0, lv);
            for (int i = 0; i < pre; i++)
                inp.push_back(rnd.any(allKeys));
            for (auto &d : actualDirs)
                inp.push_back(rnd.any(keyMap[d]));
            // extra key resets match
            inp.push_back(rnd.any(allKeys));
        }
    }

    // Output
    // First line: concatenated note tokens
    for (auto &s : noteTokens) printf("%s", s.c_str());
    printf("\n");
    // Second line: user input keys
    println(inp);

    return 0;
}
