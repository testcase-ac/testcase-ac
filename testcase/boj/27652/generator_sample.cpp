#include "testlib.h"

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Query {
    string op;
    string target;
    string value;
};

string repeatPattern(const string& pattern, int length) {
    string result;
    while ((int)result.size() < length) result += pattern;
    result.resize(length);
    return result;
}

string randomString(int minLength, int maxLength, const string& alphabet) {
    int length = rnd.next(minLength, maxLength);
    string result;
    for (int i = 0; i < length; ++i) result += rnd.any(alphabet);
    return result;
}

string makeCandidate(int mode, int maxLength) {
    if (mode == 0) {
        static const vector<string> pool = {
            "a", "b", "c", "ab", "ba", "abc", "bca", "cab",
            "aba", "bab", "abba", "baab", "abcabc", "bcabca"
        };
        string s = rnd.any(pool);
        if ((int)s.size() <= maxLength) return s;
    }

    if (mode == 1) {
        string base = rnd.any(vector<string>{"a", "ab", "ba", "abc", "bca"});
        return repeatPattern(base, rnd.next(1, maxLength));
    }

    if (mode == 2) {
        string left = repeatPattern("ab", rnd.next(1, maxLength));
        if (rnd.next(2) == 0) reverse(left.begin(), left.end());
        return left;
    }

    return randomString(1, maxLength, rnd.next(2) ? "abc" : "abcd");
}

string freshString(const set<string>& used, int mode, int maxLength) {
    for (int attempt = 0; attempt < 200; ++attempt) {
        string candidate = makeCandidate(mode, maxLength);
        if (!used.count(candidate)) return candidate;
    }

    for (int length = 1; length <= maxLength; ++length) {
        string candidate = string(length, 'a');
        candidate.back() = char('a' + (int)(used.size() + length) % 26);
        if (!used.count(candidate)) return candidate;
    }

    return randomString(1, maxLength, "abcdefghijklmnopqrstuvwxyz");
}

void addQuery(vector<Query>& queries, set<string>& selected, int mode, int maxLength,
              const string& target) {
    string value = freshString(selected, mode, maxLength);
    selected.insert(value);
    queries.push_back({"add", target, value});
}

void deleteQuery(vector<Query>& queries, set<string>& selected, const string& target) {
    int index = rnd.next((int)selected.size());
    auto it = selected.begin();
    advance(it, index);
    string value = *it;
    selected.erase(it);
    queries.push_back({"delete", target, value});
}

string findString(const vector<string>& seenA, const vector<string>& seenB, int mode, int maxLength) {
    if (!seenA.empty() && !seenB.empty() && rnd.next(100) < 75) {
        string a = rnd.any(seenA);
        string b = rnd.any(seenB);
        int leftLimit = min((int)a.size(), maxLength - 1);
        if (leftLimit >= 1) {
            int left = rnd.next(1, leftLimit);
            int right = rnd.next(1, min((int)b.size(), maxLength - left));
            return a.substr(0, left) + b.substr((int)b.size() - right);
        }
    }

    return makeCandidate(mode, maxLength);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int maxLength = (mode == 3 && rnd.next(6) == 0) ? 1000 : rnd.next(5, 24);
    int targetQ = (maxLength > 100) ? rnd.next(4, 10) : rnd.next(8, 70);

    vector<Query> queries;
    set<string> a;
    set<string> b;
    vector<string> seenA;
    vector<string> seenB;
    bool hasFind = false;

    while ((int)queries.size() < targetQ) {
        int remaining = targetQ - (int)queries.size();
        int choice = rnd.next(100);

        if (!hasFind && remaining == 1) choice = 99;

        if (choice < 45 || (a.empty() && b.empty())) {
            bool targetA = rnd.next(2) == 0;
            if (targetA) {
                addQuery(queries, a, mode, maxLength, "A");
                seenA.push_back(queries.back().value);
            } else {
                addQuery(queries, b, mode, maxLength, "B");
                seenB.push_back(queries.back().value);
            }
        } else if (choice < 70 && (!a.empty() || !b.empty())) {
            bool canDeleteA = !a.empty();
            bool canDeleteB = !b.empty();
            bool targetA = canDeleteA && (!canDeleteB || rnd.next(2) == 0);
            if (targetA) {
                deleteQuery(queries, a, "A");
            } else {
                deleteQuery(queries, b, "B");
            }
        } else {
            queries.push_back({"find", "", findString(seenA, seenB, mode, maxLength)});
            hasFind = true;
        }
    }

    println((int)queries.size());
    for (const Query& query : queries) {
        if (query.op == "find") {
            cout << "find " << query.value << '\n';
        } else {
            cout << query.op << ' ' << query.target << ' ' << query.value << '\n';
        }
    }

    return 0;
}
