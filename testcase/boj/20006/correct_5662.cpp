#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
struct player {
    string name;
    int level;
};
int main() {
    int P, M;
    cin >> P >> M;
    vector<vector<player>> rooms;

    for (int i = 0; i < P; i++) {
        int L;
        string n;
        cin >> L >> n;
        player p = {n, L};
        bool found = false;
        for(auto &r: rooms) {
            if(r.size() == M) continue;
            if(abs(r.front().level - L) <= 10) {
                r.push_back(p);
                found = true;
                break;
            }
        }
        if(!found) {
            rooms.push_back({p});
        }
    }
    for(auto &r: rooms) {
        if(r.size() == M) {
            cout << "Started!\n";
        } else {
            cout << "Waiting!\n";
        }
        sort(r.begin(), r.end(), [](const player &a, const player &b) {
            return a.name < b.name;
        });
        for(auto &p: r) {
            cout << p.level << " " << p.name << '\n';
        }
    }
}
