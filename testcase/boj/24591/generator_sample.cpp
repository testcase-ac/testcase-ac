#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomString(const string& alphabet, int length) {
    string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result += alphabet[rnd.next((int)alphabet.size())];
    }
    return result;
}

int shortestMissingLength(const string& v, const string& s) {
    vector<bool> seen(26, false);
    int completeBlocks = 0;

    for (char c : s) {
        seen[c - 'a'] = true;

        bool complete = true;
        for (char allowed : v) {
            if (!seen[allowed - 'a']) {
                complete = false;
                break;
            }
        }

        if (complete) {
            ++completeBlocks;
            fill(seen.begin(), seen.end(), false);
        }
    }

    return completeBlocks + 1;
}

string makeMissingQuery(const string& v, const string& s) {
    string query;
    size_t pos = 0;

    while (true) {
        for (char c : v) {
            size_t next = s.find(c, pos);
            if (next == string::npos) {
                query += c;
                return query;
            }
        }

        char chosen = v[rnd.next((int)v.size())];
        query += chosen;
        pos = s.find(chosen, pos) + 1;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int alphabetSize;
    int mode = rnd.next(5);
    if (mode == 0) {
        alphabetSize = 1;
    } else if (mode == 1) {
        alphabetSize = 2;
    } else {
        alphabetSize = rnd.next(3, 8);
    }

    string letters = "abcdefghijklmnopqrstuvwxyz";
    shuffle(letters.begin(), letters.end());
    letters.resize(alphabetSize);
    sort(letters.begin(), letters.end());
    string v = letters;

    int sLength = rnd.next(1, 28);
    string s;
    if (mode == 0) {
        s = string(sLength, v[0]);
    } else if (mode == 2) {
        for (int i = 0; i < sLength; ++i) {
            s += v[i % alphabetSize];
        }
    } else if (mode == 3) {
        for (int i = 0; i < sLength; ++i) {
            s += v[(i / 2) % alphabetSize];
        }
    } else {
        s = randomString(v, sLength);
    }

    int missingLength = shortestMissingLength(v, s);
    vector<string> queries;
    int queryCount = rnd.next(4, 12);

    queries.push_back(makeMissingQuery(v, s));
    queries.push_back(randomString(v, max(1, missingLength - 1)));
    queries.push_back(randomString(v, missingLength));
    queries.push_back(randomString(v, missingLength + rnd.next(1, 3)));

    while ((int)queries.size() < queryCount) {
        int queryMode = rnd.next(4);
        if (queryMode == 0) {
            queries.push_back(makeMissingQuery(v, s));
        } else if (queryMode == 1) {
            queries.push_back(randomString(v, max(1, missingLength - 1)));
        } else if (queryMode == 2) {
            queries.push_back(randomString(v, missingLength));
        } else {
            queries.push_back(randomString(v, rnd.next(1, 12)));
        }
    }

    shuffle(queries.begin(), queries.end());

    println(v);
    println(s);
    println((int)queries.size());
    for (const string& query : queries) {
        println(query);
    }

    return 0;
}
