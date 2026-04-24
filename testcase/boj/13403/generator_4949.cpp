#include "testlib.h"
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

string genE(int depth);
string genT(int depth);
string genF(int depth);
string genN() {
    // Number: either "0" or "1" followed by binary digits
    if (rnd.next(0, 1) == 0) {
        return "0";
    } else {
        int lenB = rnd.next(0, 2);
        string s = "1";
        for (int i = 0; i < lenB; i++)
            s += rnd.any(string("01"));
        return s;
    }
}

string genF(int depth) {
    // F ::= N | -F | (E)
    vector<int> opts;
    opts.push_back(0); // N
    if (depth > 0) {
        opts.push_back(1); // -F
        opts.push_back(2); // (E)
    }
    int choice = rnd.next(0, int(opts.size()) - 1);
    if (opts[choice] == 0) {
        return genN();
    } else if (opts[choice] == 1) {
        return "-" + genF(depth - 1);
    } else {
        return "(" + genE(depth - 1) + ")";
    }
}

string genT(int depth) {
    // T ::= F | T*F
    if (depth > 0 && rnd.next() < 0.5) {
        string left = genT(depth - 1);
        string right = genF(depth - 1);
        return left + "*" + right;
    } else {
        return genF(depth - 1);
    }
}

string genE(int depth) {
    // E ::= T | E+T | E-T
    if (depth > 0 && rnd.next() < 0.5) {
        string left = genE(depth - 1);
        string right = genT(depth - 1);
        char op = rnd.next() < 0.5 ? '+' : '-';
        return left + op + right;
    } else {
        return genT(depth - 1);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Pool of replacement letters
    string pool = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while (true) {
        // Hyper-parameters for expression shape
        int depthL = rnd.next(1, 3);
        int depthR = rnd.next(1, 3);
        string left = genE(depthL);
        string right = genE(depthR);
        string orig = left + "=" + right;
        // Hyper-parameters for mapping
        double p_map = rnd.next(0.2, 0.8);
        double p_occ = rnd.next(0.2, 0.8);
        // Build distinct character set
        set<char> distinct(orig.begin(), orig.end());
        // Available letters
        vector<char> avail(pool.begin(), pool.end());
        map<char, char> mp;
        for (char c : distinct) {
            if (!avail.empty() && rnd.next() < p_map) {
                int idx = rnd.next((int)avail.size() - 1);
                mp[c] = avail[idx];
                avail.erase(avail.begin() + idx);
            }
        }
        // Build encrypted string with partial replacements
        string enc;
        for (char c : orig) {
            auto it = mp.find(c);
            if (it != mp.end() && rnd.next() < p_occ) {
                enc += it->second;
            } else {
                enc += c;
            }
        }
        if (enc.size() <= 31) {
            println(enc);
            break;
        }
        // else retry
    }
    return 0;
}
