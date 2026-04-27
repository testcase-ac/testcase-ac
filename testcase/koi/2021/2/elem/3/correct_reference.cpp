#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> cal(string s, int ma){
	vector<int> v(ma + 1);
	
	int t = 0;
	for(int i = 0; i < s.length(); i++){
		if(i + 1 < s.length() && s[i] == '(' && s[i + 1] == ')') v[t]++, i++;
		else if(s[i] == '(') t++;
		else t--;
	}
	for(int i = 0; i < ma; i++){
		v[i + 1] += v[i] / 2;
		v[i] %= 2;
	}
	reverse(v.begin(), v.end());
	return v;
}

void solve(){
	string s1, s2;
	cin >> s1 >> s2;
	int ma = max(s1.length(), s2.length());
	auto v1 = cal(s1, ma), v2 = cal(s2, ma);
	if(v1 == v2) cout << '=' << endl;
	else cout << (v1 < v2 ? '<' : '>') << endl;
}

int main(){
	int tc;
	cin >> tc;
	while(tc--) solve();
	return 0;
}