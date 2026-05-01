#include "testlib.h"
using namespace std;

string genBigDecimal(int minLen, int maxLen) {
    int len = rnd.next(minLen, maxLen);
    string s;
    s.reserve(len);
    s += char('1' + rnd.next(0, 8)); // first digit 1-9
    for (int i = 1; i < len; i++) {
        s += char('0' + rnd.next(0, 9));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> consonants = {"ㄱ","ㄴ","ㄹ","ㅁ","ㅂ","ㅅ","ㅇ","ㅈ","ㅊ","ㅍ","ㅎ"};
    vector<string> vowels = {"ㅏ","ㅐ","ㅑ","ㅓ","ㅕ","ㅗ","ㅜ","ㅠ","ㅡ","ㅣ"};
    vector<string> all = consonants;
    all.insert(all.end(), vowels.begin(), vowels.end());

    int T = rnd.next(1, 4);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        // Choose N pattern
        int pattern = rnd.next(0, 5);
        string N;

        if (pattern == 0) {
            // Very small N
            long long n = rnd.next(1LL, 20LL);
            N = to_string(n);
        } else if (pattern == 1) {
            // Small/medium N
            long long n = rnd.next(1LL, 1000000LL);
            N = to_string(n);
        } else if (pattern == 2) {
            // Up to 1e12
            long long n = rnd.next(1LL, 1000000000000LL);
            N = to_string(n);
        } else if (pattern == 3) {
            // Up to 1e18
            long long n = rnd.next(1LL, 1000000000000000000LL);
            N = to_string(n);
        } else if (pattern == 4) {
            // Big, 20-30 digits
            N = genBigDecimal(20, 30);
        } else { // pattern == 5
            // Very big, 45-52 digits, but <= 10^52 - 1
            N = genBigDecimal(45, 52);
        }

        // Choose missing jamo pattern
        int missingType = rnd.next(0, 4);
        vector<string> missing;

        if (missingType == 0) {
            // Single important jamo
            vector<string> important = {"ㅇ","ㅣ","ㅏ","ㄹ","ㄱ"};
            missing.push_back(rnd.any(important));
        } else if (missingType == 1) {
            // Only vowels
            int k = rnd.next(1, (int)vowels.size()); // 1..10
            vector<int> idx(vowels.size());
            for (int i = 0; i < (int)vowels.size(); ++i) idx[i] = i;
            shuffle(idx.begin(), idx.end());
            for (int i = 0; i < k; ++i)
                missing.push_back(vowels[idx[i]]);
        } else if (missingType == 2) {
            // Only consonants
            int k = rnd.next(1, (int)consonants.size()); // 1..11
            vector<int> idx(consonants.size());
            for (int i = 0; i < (int)consonants.size(); ++i) idx[i] = i;
            shuffle(idx.begin(), idx.end());
            for (int i = 0; i < k; ++i)
                missing.push_back(consonants[idx[i]]);
        } else if (missingType == 3) {
            // Mixed random small/medium
            int k = rnd.next(1, (int)all.size()); // 1..21
            vector<int> idx(all.size());
            for (int i = 0; i < (int)all.size(); ++i) idx[i] = i;
            shuffle(idx.begin(), idx.end());
            for (int i = 0; i < k; ++i)
                missing.push_back(all[idx[i]]);
        } else { // missingType == 4
            // Many jamos missing
            int k = rnd.next(15, (int)all.size()); // 15..21
            vector<int> idx(all.size());
            for (int i = 0; i < (int)all.size(); ++i) idx[i] = i;
            shuffle(idx.begin(), idx.end());
            for (int i = 0; i < k; ++i)
                missing.push_back(all[idx[i]]);
        }

        int M = (int)missing.size();

        // First line: N and M
        printf("%s %d\n", N.c_str(), M);
        // Second line: missing jamos
        println(missing);
    }

    return 0;
}
