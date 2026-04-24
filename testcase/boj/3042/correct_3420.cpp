#include <bits/stdc++.h>
using namespace std;

int ans;
pair<int, int> pos[26];
pair<int, int> no = {-1,-1};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	memset(pos, -1, sizeof pos);
	for(int i=0; i<n; i++) {
		string s;
		cin >> s;
		for(int j=0; j<n; j++) {
			if(isalpha(s[j]))
				pos[s[j]-'A'] = {i,j};
		}
	}
	for(int i=0; i<26; i++) {
		for(int j=i+1; j<26; j++) {
			for(int k=j+1; k<26; k++) {
				if(pos[i] == no || pos[j] == no || pos[k] == no) continue;
				pair<int, int> a[3] = {pos[i], pos[j], pos[k]};
				sort(a, a+3);
				if((a[2].first-a[1].first)*(a[1].second-a[0].second) == (a[2].second-a[1].second)*(a[1].first-a[0].first))
					ans++;
			}
		}
	}
	cout << ans;
}
