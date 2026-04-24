#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

string revStr(int n) {
    string s = to_string(n);
    reverse(s.begin(), s.end());
    return s;
}

bool isPalNum(int n) {
    string s = to_string(n), r = s;
    reverse(r.begin(), r.end());
    return s == r;
}

bool sumPal(int n) {
    string rs = revStr(n);
    int rn = stoi(rs);
    return isPalNum(n + rn);
}

int sampleFromHyper() {
    int t = rnd.next(1, 4);
    if (t == 1) {
        // uniform
        return rnd.next(10, 100000);
    } else if (t == 2) {
        // trailing zero
        int x = rnd.next(1, 9999);
        return x * 10;
    } else if (t == 3) {
        // generate a palindromic N of length 2 to 5
        int len = rnd.next(2, 5);
        int half = (len + 1) / 2;
        string a;
        for (int i = 0; i < half; i++) {
            if (i == 0) a += char('1' + rnd.next(0, 8));
            else        a += char('0' + rnd.next(0, 9));
        }
        string b = a;
        if (len % 2 == 1) b.pop_back();
        reverse(b.begin(), b.end());
        a += b;
        int val = stoi(a);
        if (val < 10) val = 11;
        if (val > 100000) val = 100000;
        return val;
    } else {
        // near max
        return rnd.next(90000, 100000);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(2, 10);
    vector<int> Ns;
    // ensure at least one YES
    while (true) {
        int x = sampleFromHyper();
        if (sumPal(x)) { Ns.push_back(x); break; }
    }
    // ensure at least one NO
    while (true) {
        int x = sampleFromHyper();
        if (!sumPal(x)) { Ns.push_back(x); break; }
    }
    // fill the rest
    for (int i = 2; i < T; i++) {
        Ns.push_back(sampleFromHyper());
    }
    shuffle(Ns.begin(), Ns.end());
    println(T);
    for (int x : Ns) println(x);
    return 0;
}
