#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide if the test case should be solvable or not (70% solvable)
    bool possible = rnd.next(0, 9) < 7;

    string S1, S2;
    if (possible) {
        // Build compatible strings
        int p_comm = rnd.next(0, 5);
        int s_comm = rnd.next(0, 5);
        int u1 = rnd.next(0, 3), u2 = rnd.next(0, 3);
        int v1 = rnd.next(0, 3), v2 = rnd.next(0, 3);
        string comm_pref, extra_u1, extra_u2, comm_suf, extra_v1, extra_v2;

        // common prefix
        for (int i = 0; i < p_comm; i++)
            comm_pref.push_back(char('A' + rnd.next(0, 25)));
        // unique prefixes
        for (int i = 0; i < u1; i++)
            extra_u1.push_back(char('A' + rnd.next(0, 25)));
        for (int i = 0; i < u2; i++)
            extra_u2.push_back(char('A' + rnd.next(0, 25)));
        // common suffix
        for (int i = 0; i < s_comm; i++)
            comm_suf.push_back(char('A' + rnd.next(0, 25)));
        // unique suffixes
        for (int i = 0; i < v1; i++)
            extra_v1.push_back(char('A' + rnd.next(0, 25)));
        for (int i = 0; i < v2; i++)
            extra_v2.push_back(char('A' + rnd.next(0, 25)));

        string pref1 = comm_pref + extra_u1;
        string pref2 = comm_pref + extra_u2;
        string suf1 = comm_suf + extra_v1;
        string suf2 = comm_suf + extra_v2;

        S1 = pref1 + "*" + suf1;
        S2 = pref2 + "*" + suf2;
    } else {
        // Build incompatible strings
        if (rnd.next(0, 1) == 0) {
            // Prefix conflict
            int p_len = rnd.next(1, 5);
            int s1len = rnd.next(0, 5), s2len = rnd.next(0, 5);
            string pref1, pref2, suf1, suf2;
            // generate pref1
            for (int i = 0; i < p_len; i++)
                pref1.push_back(char('A' + rnd.next(0, 25)));
            // copy and introduce one mismatch
            pref2 = pref1;
            int idx = rnd.next(0, p_len - 1);
            char c;
            do {
                c = char('A' + rnd.next(0, 25));
            } while (c == pref1[idx]);
            pref2[idx] = c;
            // random suffixes
            for (int i = 0; i < s1len; i++)
                suf1.push_back(char('A' + rnd.next(0, 25)));
            for (int i = 0; i < s2len; i++)
                suf2.push_back(char('A' + rnd.next(0, 25)));

            S1 = pref1 + "*" + suf1;
            S2 = pref2 + "*" + suf2;
        } else {
            // Suffix conflict
            int s_len = rnd.next(1, 5);
            int p1len = rnd.next(0, 5), p2len = rnd.next(0, 5);
            string pref1, pref2, suf1, suf2;
            // random prefixes
            for (int i = 0; i < p1len; i++)
                pref1.push_back(char('A' + rnd.next(0, 25)));
            for (int i = 0; i < p2len; i++)
                pref2.push_back(char('A' + rnd.next(0, 25)));
            // generate suf1
            for (int i = 0; i < s_len; i++)
                suf1.push_back(char('A' + rnd.next(0, 25)));
            // copy and introduce one mismatch
            suf2 = suf1;
            int idx = rnd.next(0, s_len - 1);
            char c;
            do {
                c = char('A' + rnd.next(0, 25));
            } while (c == suf1[idx]);
            suf2[idx] = c;

            S1 = pref1 + "*" + suf1;
            S2 = pref2 + "*" + suf2;
        }
    }

    // Output the two strings
    println(S1);
    println(S2);

    return 0;
}
