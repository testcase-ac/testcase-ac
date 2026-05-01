#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 60;
    int N;

    int sizeBand = rnd.next(0, 4);
    if (sizeBand == 0) N = rnd.next(1, 5);
    else if (sizeBand == 1) N = rnd.next(6, 10);
    else if (sizeBand == 2) N = rnd.next(11, 20);
    else if (sizeBand == 3) N = rnd.next(21, 40);
    else N = rnd.next(41, maxN);

    int patternType = rnd.next(0, 8); // 0..8

    vector<string> tokens;
    tokens.reserve(N);

    switch (patternType) {
        case 0: { // all bigdata
            tokens.assign(N, "bigdata");
            break;
        }
        case 1: { // all security
            tokens.assign(N, "security");
            break;
        }
        case 2: { // alternating, start bigdata
            for (int i = 0; i < N; i++)
                tokens.push_back(i % 2 == 0 ? "bigdata" : "security");
            break;
        }
        case 3: { // alternating, start security
            for (int i = 0; i < N; i++)
                tokens.push_back(i % 2 == 0 ? "security" : "bigdata");
            break;
        }
        case 4: { // exact tie, randomized order
            if (N < 2) N = 2;
            if (N % 2 == 1) {
                if (N < maxN) N++;
                else N--;
            }
            tokens.clear();
            for (int i = 0; i < N / 2; i++) tokens.push_back("bigdata");
            for (int i = 0; i < N / 2; i++) tokens.push_back("security");
            shuffle(tokens.begin(), tokens.end());
            break;
        }
        case 5: { // bigdata slight majority
            if (N == 1) {
                tokens.push_back("bigdata");
                break;
            }
            int baseBig = N / 2 + 1;
            int extraMax = min(2, N - baseBig);
            int extra = (extraMax > 0 ? rnd.next(0, extraMax) : 0);
            int bigCount = baseBig + extra;
            int secCount = N - bigCount;
            tokens.clear();
            for (int i = 0; i < bigCount; i++) tokens.push_back("bigdata");
            for (int i = 0; i < secCount; i++) tokens.push_back("security");
            shuffle(tokens.begin(), tokens.end());
            break;
        }
        case 6: { // security slight majority
            if (N == 1) {
                tokens.push_back("security");
                break;
            }
            int baseSec = N / 2 + 1;
            int extraMax = min(2, N - baseSec);
            int extra = (extraMax > 0 ? rnd.next(0, extraMax) : 0);
            int secCount = baseSec + extra;
            int bigCount = N - secCount;
            tokens.clear();
            for (int i = 0; i < bigCount; i++) tokens.push_back("bigdata");
            for (int i = 0; i < secCount; i++) tokens.push_back("security");
            shuffle(tokens.begin(), tokens.end());
            break;
        }
        case 7: { // extremely skewed (only one minority)
            if (N == 1) {
                tokens.push_back(rnd.next(0, 1) ? "bigdata" : "security");
            } else {
                bool minorityIsBig = rnd.next(0, 1);
                int bigCount = minorityIsBig ? 1 : (N - 1);
                int secCount = N - bigCount;
                tokens.clear();
                for (int i = 0; i < bigCount; i++) tokens.push_back("bigdata");
                for (int i = 0; i < secCount; i++) tokens.push_back("security");
                shuffle(tokens.begin(), tokens.end());
            }
            break;
        }
        case 8: { // fully random answers
            for (int i = 0; i < N; i++)
                tokens.push_back(rnd.next(0, 1) ? "bigdata" : "security");
            break;
        }
    }

    ensure((int)tokens.size() == N);

    string concat;
    concat.reserve(N * 8);
    for (const string &t : tokens) concat += t;

    println(N);
    println(concat);

    return 0;
}
