#include "testlib.h"
using namespace std;

string makePure(int m) {
    vector<char> v;
    v.reserve(3 * m);
    for (int i = 0; i < m; i++) {
        int L = (int)v.size();
        // insert first H
        int posH1 = rnd.next(0, L);
        v.insert(v.begin() + posH1, 'H');
        L++;
        // insert O after that H
        int posO = rnd.next(posH1 + 1, L);
        v.insert(v.begin() + posO, 'O');
        L++;
        // insert second H after that O
        int posH2 = rnd.next(posO + 1, L);
        v.insert(v.begin() + posH2, 'H');
    }
    return string(v.begin(), v.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 6); // 0..6
    string S;

    if (scenario == 0) {
        // Very small random strings
        int N = rnd.next(1, 5);
        S.reserve(N);
        for (int i = 0; i < N; i++)
            S.push_back(rnd.next(0, 1) ? 'H' : 'O');
    } else if (scenario == 1) {
        // Random pure string built from molecules
        int m = rnd.next(1, 8); // 3..24 length
        S = makePure(m);
    } else if (scenario == 2) {
        // Medium random strings
        int N = rnd.next(10, 40);
        S.reserve(N);
        for (int i = 0; i < N; i++)
            S.push_back(rnd.next(0, 1) ? 'H' : 'O');
    } else if (scenario == 3) {
        // Balanced counts but guaranteed "bad" prefix (O's lead)
        int m = rnd.next(1, 10); // length up to 30
        int H = 2 * m;
        int O = m;
        vector<char> v;
        v.reserve(3 * m);

        int prefixO = min(2, O); // put 1 or 2 O's first
        for (int i = 0; i < prefixO; i++) {
            v.push_back('O');
            O--;
        }
        // remaining letters, shuffled
        vector<char> rest;
        rest.reserve(H + O);
        for (int i = 0; i < H; i++) rest.push_back('H');
        for (int i = 0; i < O; i++) rest.push_back('O');
        shuffle(rest.begin(), rest.end());
        for (char c : rest) v.push_back(c);

        S = string(v.begin(), v.end());
    } else if (scenario == 4) {
        // "Almost pure": start from pure, then perturb
        int m = rnd.next(1, 8);
        S = makePure(m);
        int choice = rnd.next(0, 2);
        if (choice == 0) {
            // Flip one character
            int pos = rnd.next(0, (int)S.size() - 1);
            S[pos] = (S[pos] == 'H' ? 'O' : 'H');
        } else if (choice == 1) {
            // Swap two positions
            if ((int)S.size() >= 2) {
                int i = rnd.next(0, (int)S.size() - 1);
                int j = rnd.next(0, (int)S.size() - 1);
                if (i != j) swap(S[i], S[j]);
            }
        } else {
            // Insert an extra random character
            char c = rnd.next(0, 1) ? 'H' : 'O';
            int pos = rnd.next(0, (int)S.size());
            S.insert(S.begin() + pos, c);
        }
    } else if (scenario == 5) {
        // Highly structured patterns
        int type = rnd.next(0, 3);
        if (type == 0) {
            // All H
            int N = rnd.next(1, 40);
            S.assign(N, 'H');
        } else if (type == 1) {
            // All O
            int N = rnd.next(1, 40);
            S.assign(N, 'O');
        } else if (type == 2) {
            // Repeating "HO"
            int reps = rnd.next(1, 20);
            S.clear();
            for (int i = 0; i < reps; i++) S += "HO";
        } else {
            // Repeating "OH"
            int reps = rnd.next(1, 20);
            S.clear();
            for (int i = 0; i < reps; i++) S += "OH";
        }
    } else {
        // scenario == 6: special hand-crafted interesting cases
        vector<string> special = {
            "H", "O",
            "HOH",
            "OHH",
            "HHOH",
            "HHHOOH",
            "HHOOHH",
            "HOHOHH",
            "HHOHOH",
            "HOHHOH",
            "OOOHHH",
            "HOHOH",
            "HOOHHH",
            "HHOOOHH"
        };
        S = rnd.any(special);
    }

    int N = (int)S.size();
    println(N);
    println(S);

    return 0;
}
