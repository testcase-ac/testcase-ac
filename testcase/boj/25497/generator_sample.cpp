#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char randomDigit() {
    return static_cast<char>('1' + rnd.next(9));
}

void appendRandomDigits(string& s, int count) {
    for (int i = 0; i < count; ++i) {
        s += randomDigit();
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string skills;
    int mode = rnd.next(6);

    if (mode == 0) {
        int n = rnd.next(1, 40);
        appendRandomDigits(skills, n);
    } else if (mode == 1) {
        int pairs = rnd.next(1, 20);
        int pendingL = 0;
        int pendingS = 0;
        for (int i = 0; i < pairs; ++i) {
            int kind = rnd.next(4);
            if (kind == 0 || pendingL == 0) {
                skills += 'L';
                ++pendingL;
            } else {
                skills += 'R';
                --pendingL;
            }
            appendRandomDigits(skills, rnd.next(0, 2));
            if (kind == 1 || pendingS == 0) {
                skills += 'S';
                ++pendingS;
            } else {
                skills += 'K';
                --pendingS;
            }
            appendRandomDigits(skills, rnd.next(0, 3));
        }
        while (pendingL-- > 0) skills += 'R';
        while (pendingS-- > 0) skills += 'K';
    } else if (mode == 2) {
        int l = rnd.next(0, 12);
        int s = rnd.next(0, 12);
        skills.append(l, 'L');
        appendRandomDigits(skills, rnd.next(0, 8));
        skills.append(s, 'S');
        appendRandomDigits(skills, rnd.next(0, 8));
        int r = rnd.next(0, l);
        int k = rnd.next(0, s);
        vector<char> finish;
        finish.insert(finish.end(), r, 'R');
        finish.insert(finish.end(), k, 'K');
        shuffle(finish.begin(), finish.end());
        for (char c : finish) skills += c;
        if (skills.empty()) skills += randomDigit();
    } else if (mode == 3) {
        appendRandomDigits(skills, rnd.next(0, 10));
        skills += rnd.next(2) == 0 ? 'R' : 'K';
        appendRandomDigits(skills, rnd.next(0, 10));
        int tail = rnd.next(0, 12);
        for (int i = 0; i < tail; ++i) skills += rnd.any(string("123456789LRSK"));
    } else if (mode == 4) {
        int blocks = rnd.next(1, 18);
        for (int i = 0; i < blocks; ++i) {
            string block;
            int kind = rnd.next(4);
            if (kind == 0) block = "LR";
            if (kind == 1) block = "SK";
            if (kind == 2) block = "LSRK";
            if (kind == 3) block = "SLKR";
            for (char c : block) {
                skills += c;
                appendRandomDigits(skills, rnd.next(0, 2));
            }
        }
    } else {
        int n = rnd.next(20, 120);
        const string alphabet = "123456789LRSK";
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(100);
            if (pick < 55) {
                skills += randomDigit();
            } else if (pick < 70) {
                skills += 'L';
            } else if (pick < 85) {
                skills += 'S';
            } else if (pick < 93) {
                skills += 'R';
            } else {
                skills += 'K';
            }
        }
        if (rnd.next(5) == 0) skills[rnd.next(static_cast<int>(skills.size()))] = rnd.any(alphabet);
    }

    println(static_cast<int>(skills.size()));
    println(skills);

    return 0;
}
