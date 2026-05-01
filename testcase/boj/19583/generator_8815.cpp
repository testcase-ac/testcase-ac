#include "testlib.h"
using namespace std;

enum Role { FULL, BONLY, AONLY, MONLY, NOISY };

string formatTime(int t) {
    int h = t / 60;
    int m = t % 60;
    char buf[6];
    sprintf(buf, "%02d:%02d", h, m);
    return string(buf);
}

string genName(set<string>& used) {
    string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._-";
    while (true) {
        int len = rnd.next(3, 8);
        string s;
        for (int i = 0; i < len; ++i)
            s += chars[rnd.next((int)chars.size())];
        if (!used.count(s)) {
            used.insert(s);
            return s;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int dayEnd = 23 * 60 + 59;

    int S, E, Q;

    // Sometimes generate very tight S, E, Q; otherwise general random.
    bool tightCase = rnd.next(0, 1);
    if (tightCase) {
        S = rnd.next(0, 1437); // so S+2 <= 1439
        E = S + 1;
        Q = E + 1;
    } else {
        S = rnd.next(0, 23 * 60 - 2);       // up to 22:58
        E = rnd.next(S + 1, 23 * 60 - 1);   // up to 22:59
        Q = rnd.next(E + 1, dayEnd);        // up to 23:59
    }

    bool hasDuring = (E >= S + 2);
    bool hasAfter = (Q <= dayEnd - 1);

    // Number of distinct members
    int N = rnd.next(4, 9);

    // Assign roles
    vector<Role> roles(N);
    int F = min(rnd.next(1, 3), N); // at least 1 FULL, up to 3 or N
    for (int i = 0; i < F; ++i) roles[i] = FULL;
    for (int i = F; i < N; ++i) {
        vector<Role> cand;
        cand.push_back(BONLY);
        cand.push_back(AONLY);
        if (hasDuring) cand.push_back(MONLY);
        cand.push_back(NOISY);
        roles[i] = rnd.any(cand);
    }

    // Generate unique nicknames
    set<string> usedNames;
    vector<string> names(N);
    for (int i = 0; i < N; ++i)
        names[i] = genName(usedNames);

    vector<pair<int, string>> logs;

    for (int i = 0; i < N; ++i) {
        string name = names[i];
        Role r = roles[i];
        vector<int> times;

        switch (r) {
            case FULL: {
                // Entry time: <= S (before or exactly at)
                if (S > 0 && rnd.next(0, 1) == 0) {
                    times.push_back(rnd.next(0, S - 1));
                } else {
                    times.push_back(S);
                }
                // Exit time: in [E, Q], sometimes exactly E or Q
                int t;
                int choice = rnd.next(0, 2);
                if (choice == 0) t = E;
                else if (choice == 1) t = Q;
                else t = rnd.next(E, Q);
                times.push_back(t);
                // Optional extra log anywhere
                int extra = rnd.next(0, 1);
                while (extra--) {
                    int te = rnd.next(0, dayEnd);
                    times.push_back(te);
                }
                break;
            }
            case BONLY: {
                // At least one pre-start message
                times.push_back(rnd.next(0, S));
                // Optional second message not in [E, Q]
                if (rnd.next(0, 1) == 1) {
                    vector<int> segs; // 0: pre, 1: during, 2: after
                    segs.push_back(0);
                    if (hasDuring) segs.push_back(1);
                    if (hasAfter) segs.push_back(2);
                    int sg = rnd.any(segs);
                    int t;
                    if (sg == 0) t = rnd.next(0, S);
                    else if (sg == 1) t = rnd.next(S + 1, E - 1);
                    else t = rnd.next(Q + 1, dayEnd);
                    times.push_back(t);
                }
                break;
            }
            case AONLY: {
                // At least one exit-segment message
                times.push_back(rnd.next(E, Q));
                // Optional extra without creating pre-start presence
                if (rnd.next(0, 1) == 1) {
                    vector<int> segs; // 0: exit, 1: during, 2: after
                    segs.push_back(0);
                    if (hasDuring) segs.push_back(1);
                    if (hasAfter) segs.push_back(2);
                    int sg = rnd.any(segs);
                    int t;
                    if (sg == 0) t = rnd.next(E, Q);
                    else if (sg == 1) t = rnd.next(S + 1, E - 1);
                    else t = rnd.next(Q + 1, dayEnd);
                    times.push_back(t);
                }
                break;
            }
            case MONLY: {
                // Messages only during the meeting
                if (hasDuring) {
                    times.push_back(rnd.next(S + 1, E - 1));
                    if (rnd.next(0, 1) == 1)
                        times.push_back(rnd.next(S + 1, E - 1));
                } else {
                    // Fallback: behave like NOISY pre-start only
                    int cnt = rnd.next(1, 3);
                    for (int k = 0; k < cnt; ++k)
                        times.push_back(rnd.next(0, S));
                }
                break;
            }
            case NOISY: {
                // All logs for this user stay in a single segment
                vector<int> segs; // 0: pre, 1: during, 2: exit, 3: after
                segs.push_back(0);
                if (hasDuring) segs.push_back(1);
                segs.push_back(2);
                if (hasAfter) segs.push_back(3);
                int sg = rnd.any(segs);
                int cnt = rnd.next(1, 3);
                for (int k = 0; k < cnt; ++k) {
                    int t;
                    if (sg == 0) t = rnd.next(0, S);
                    else if (sg == 1) t = rnd.next(S + 1, E - 1);
                    else if (sg == 2) t = rnd.next(E, Q);
                    else t = rnd.next(Q + 1, dayEnd);
                    times.push_back(t);
                }
                break;
            }
        }

        for (int t : times)
            logs.emplace_back(t, name);
    }

    // Sort logs chronologically; tie-broken by name for determinism
    sort(logs.begin(), logs.end(), [](const pair<int,string>& a, const pair<int,string>& b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    });

    // Output
    string sS = formatTime(S);
    string sE = formatTime(E);
    string sQ = formatTime(Q);
    println(sS, sE, sQ);

    for (auto &p : logs) {
        println(formatTime(p.first), p.second);
    }

    return 0;
}
