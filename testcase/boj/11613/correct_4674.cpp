#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;

/*
xxxxx  ....x  xxxxx  xxxxx  x...x  xxxxx  xxxxx  xxxxx  xxxxx  xxxxx  .....
x...x  ....x  ....x  ....x  x...x  x....  x....  ....x  x...x  x...x  ..x..
x...x  ....x  ....x  ....x  x...x  x....  x....  ....x  x...x  x...x  ..x..
x...x  ....x  xxxxx  xxxxx  xxxxx  xxxxx  xxxxx  ....x  xxxxx  xxxxx  xxxxx
x...x  ....x  x....  ....x  ....x  ....x  x...x  ....x  x...x  ....x  ..x..
x...x  ....x  x....  ....x  ....x  ....x  x...x  ....x  x...x  ....x  ..x..
xxxxx  ....x  xxxxx  xxxxx  ....x  xxxxx  xxxxx  ....x  xxxxx  xxxxx  .....
*/

vector<vector<int>> asciis = {
    {31, 17, 17, 17, 17, 17, 31},
    {1, 1, 1, 1, 1, 1, 1},
    {31, 1, 1, 31, 16, 16, 31},
    {31, 1, 1, 31, 1, 1, 31},
    {17, 17, 17, 31, 1, 1, 1},
    {31, 16, 16, 31, 1, 1, 31},
    {31, 16, 16, 31, 17, 17, 31},
    {31, 1, 1, 1, 1, 1, 1},
    {31, 17, 17, 31, 17, 17, 31},
    {31, 17, 17, 31, 1, 1, 31},
    {0, 4, 4, 31, 4, 4, 0}
};

int string_to_int(string s) {
    int ret = 0;
    int add = 1;
    for(int i=4; i>=0; i--) {
        if(s[i]=='x') {
            ret += add;
        }
        add *= 2;
    }
    return ret;
}

string int_to_string(int t) {
    string ret = "";
    for(int i=0; i<5; i++) {
        int target = (1 << (4-i));
        if(t >= target) {
            ret += "x";
            t -= target;
        }
        else {
            ret += ".";
        }
    }
    return ret;
}

int main() {
    vector<vector<int>> v(7);
    for(int i=0; i<7; i++) {
        string s;
        cin >> s;
        int length = s.length();
        for(int j=0; j<length; j+=6) {
            int res = string_to_int(s.substr(j, length));
            v[i].push_back(res);
        }
    }
    string a = "";
    string b = "";
    bool plus = false;
    for(int i=0; i<v[0].size(); i++) {
        int k=0;
        for(k=0; k<11; k++) {
            bool pos = true;
            for(int j=0; j<7; j++) {
                if(v[j][i]!=asciis[k][j]) {
                    pos = false;
                }
            }
            if(pos) break;
        }
        if(k==10) {
            plus = true;
        }
        else {
            if(plus) b+=('0'+k);
            else a+=('0'+k);
        }
    }
    int ai = stoi(a), bi = stoi(b);
    string ans = to_string(ai+bi);
    string f_ans = "";
    int ans_len = ans.length();
    for(int i=0; i<7; i++) {
        for(int j=0; j<ans_len; j++) {
            f_ans += int_to_string(asciis[ans[j]-'0'][i]);
            if(j!=ans_len-1)
                f_ans+=".";
        }
        if(i!=6)
            f_ans+="\n";
    }
    cout << f_ans << endl;
}
