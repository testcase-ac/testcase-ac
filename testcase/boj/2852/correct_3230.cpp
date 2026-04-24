#include <bits/stdc++.h>
using namespace std;
#define int long long

string sec_to_time(int s) {
    int min = s / 60;
    int sec = s % 60;
    string min_str = to_string(min);
    string sec_str = to_string(sec);
    if (min_str.length() == 1) {
        min_str = "0" + min_str;
    }
    if (sec_str.length() == 1) {
        sec_str = "0" + sec_str;
    }
    return min_str + ":" + sec_str;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    int a_time = 0, b_time = 0, a_score = 0, b_score = 0;
    int last_sec = 0;
    for (int i = 0; i < N; i++) {
        int team;
        string time;
        cin >> team >> time;
        int sec = stoi(time.substr(0, 2)) * 60 + stoi(time.substr(3, 2));
        if (a_score > b_score) {
            a_time += sec - last_sec;
        } else if(a_score < b_score) {
            b_time += sec - last_sec;
        }
        last_sec = sec;
        if (team == 1) {
            a_score++;
        } else {
            b_score++;
        }
    }
    if (a_score > b_score) {
        a_time += 48 * 60 - last_sec;
    } else if(a_score < b_score) {
        b_time += 48 * 60 - last_sec;
    }
    cout << sec_to_time(a_time) << '\n' << sec_to_time(b_time) << '\n';
}
