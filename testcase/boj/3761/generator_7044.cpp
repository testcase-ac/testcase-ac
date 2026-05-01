#include "testlib.h"
#include <algorithm>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: 1 to 4
    int T = rnd.next(1, 4);
    println(T);

    for (int tc = 0; tc < T; tc++) {
        // n biased towards smaller but up to 10
        int n = rnd.wnext(10, -1) + 1;

        // Generate distinct male and female names
        vector<char> males, females;
        for (char c = 'a'; c <= 'z'; ++c) males.push_back(c);
        for (char c = 'A'; c <= 'Z'; ++c) females.push_back(c);
        shuffle(males.begin(), males.end());
        shuffle(females.begin(), females.end());
        males.resize(n);
        females.resize(n);

        // Build preference lists
        vector<string> malePref(n), femalePref(n);
        for (int i = 0; i < n; i++) {
            vector<char> tmpF = females;
            shuffle(tmpF.begin(), tmpF.end());
            malePref[i].reserve(n);
            for (char f : tmpF) malePref[i].push_back(f);
        }
        for (int i = 0; i < n; i++) {
            vector<char> tmpM = males;
            shuffle(tmpM.begin(), tmpM.end());
            femalePref[i].reserve(n);
            for (char m : tmpM) femalePref[i].push_back(m);
        }

        // Output one test case
        println(n);
        // print names: males then females
        vector<string> names;
        for (char c : males) names.push_back(string(1, c));
        for (char c : females) names.push_back(string(1, c));
        println(names);
        // print male preferences
        for (int i = 0; i < n; i++) {
            printf("%c:%s\n", males[i], malePref[i].c_str());
        }
        // print female preferences
        for (int i = 0; i < n; i++) {
            printf("%c:%s\n", females[i], femalePref[i].c_str());
        }
    }

    return 0;
}
