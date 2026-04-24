#include <bits/stdc++.h>
using namespace std;
#define int long long

// Function to apply an operator to two numbers
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
    }
    return 0;
}
int evaluatePostfix(const vector<string>& postfix) {
    stack<int> values;

    for (const string& token : postfix) {
        if (isdigit(token[0])) {
            values.push(stoi(token));
        } else {
            int b = values.top(); values.pop();
            int a = values.top(); values.pop();
            values.push(applyOp(a, b, token[0]));
        }
    }

    return values.top();
}


int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    string s;
    cin >> s;
    int OP = N / 2;
    int ans = INT_MIN;
    for(int bm=0; bm<(1<<OP); bm++) {
        bool ok = 1;
        for(int b=0; b<OP; b++) {
            if((bm & (1<<b)) && (bm & (1<<(b+1)))) {
                ok = 0;
                break;
            }
        }
        if(!ok) continue;
        vector<string> post = {{s[0]}};
        vector<pair<char, bool>> ops;
        for(int i=0; i<OP; i++) {
            bool prec = bm & (1<<i);
            while(ops.size() && ops.back().second >= prec) {
                post.push_back({ops.back().first});
                ops.pop_back();
            }
            ops.push_back({s[2*i+1], prec});
            post.push_back({s[2*i+2]});
        }
        while(ops.size()) {
            post.push_back({ops.back().first});
            ops.pop_back();
        }
        // evaulate postfix
        int res = evaluatePostfix(post);
        ans = max(ans, res);
    }
    cout << ans;
}
