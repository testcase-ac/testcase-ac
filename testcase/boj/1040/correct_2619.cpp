#include <iostream>
#include <string>
using namespace std;
int K;
string chk(string s) {
    int uniq = 0, tmp[10] = {0,};
    string ret = s;
    for(int i=0; i<s.size(); i++) {
        if(s[i] == 'X') {
            if(uniq > K)
                return "";
            else if(uniq == K) {
                int d = 0;
                while(!tmp[d])
                    d++;
                for(int j=i; j<s.size(); j++) {
                    ret[j] = d+'0';
                }
                return ret;
            } else {
                int xcnt = s.size() - i, d = 0;
                if(uniq + xcnt < K)
                    return "";
                // 여기는 uniq < K다. 0 fill in을 하면 uniq가 부족할 수 있다.
                int uses = K - uniq;
                for(int j=s.size()-uses; j<s.size(); j++) {
                    while(tmp[d])
                        d++;
                    ret[j] = '0'+d;
                    d++;
                }
                for(int j=i; j<s.size()-uses; j++)
                    ret[j] = '0';
                return ret;
            }
        }
        if(!tmp[s[i]-'0'])
            uniq++;
        tmp[s[i]-'0']++;
    }
    if(uniq == K)
        return s;
    else
        return "";
}
int main() {
    string s;
    cin >> s >> K;
    string ret;
    ret = chk(s);
    if(ret.size())
        return !(cout << ret);
    for(int i=s.size()-1; i>=0; i--) {
        while(s[i] < '9') {
            s[i]++;
            ret = chk(s);
            if(ret.size())
                return !(cout << ret);
        }
        s[i] = 'X';
    }
    while(1) {
        s = '0' + s;
        while(s.front() < '9') {
            s.front()++;
            ret = chk(s);
            if(ret.size())
                return !(cout << ret);
        }
        s.front() = 'X';
    }
}
