#include "testlib.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

string makeName(int id) {
    const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string name;
    do {
        name.push_back(letters[id % (int)letters.size()]);
        id /= (int)letters.size();
    } while (id > 0);
    return name;
}

int motivation(int mode) {
    if (mode == 0) return rnd.next(0, 10);
    if (mode == 1) return rnd.any(vector<int>{0, 1, 2, 99999, 100000});
    if (mode == 2) return rnd.next(45, 55);
    return rnd.next(0, 100000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 18);
    int m = rnd.next(1, 45);
    int scoreMode = rnd.next(0, 3);
    int nextNameId = 0;

    vector<pair<string, int>> initial;
    vector<string> active;
    vector<string> inactive;
    map<string, int> oldScore;

    for (int i = 0; i < n; ++i) {
        string name = makeName(nextNameId++);
        int score = motivation(scoreMode);
        initial.push_back({name, score});
        active.push_back(name);
        oldScore[name] = score;
    }

    vector<string> events;
    for (int i = 0; i < m; ++i) {
        bool canRemove = !active.empty();
        bool canRejoin = !inactive.empty();
        bool doAdd = !canRemove || rnd.next(100) < (canRejoin ? 58 : 65);

        if (doAdd) {
            string name;
            if (canRejoin && rnd.next(100) < 35) {
                int pos = rnd.next((int)inactive.size());
                name = inactive[pos];
                inactive[pos] = inactive.back();
                inactive.pop_back();
            } else {
                name = makeName(nextNameId++);
            }

            int score = motivation(scoreMode);
            if (oldScore.count(name) && rnd.next(100) < 45) {
                score = oldScore[name];
            }
            oldScore[name] = score;
            active.push_back(name);
            events.push_back("+ " + name + " " + to_string(score));
        } else {
            int pos = rnd.next((int)active.size());
            string name = active[pos];
            active[pos] = active.back();
            active.pop_back();
            inactive.push_back(name);
            events.push_back("- " + name);
        }
    }

    println(n);
    for (const auto& member : initial) {
        println(member.first, member.second);
    }
    println(m);
    for (const string& event : events) {
        println(event);
    }

    return 0;
}
