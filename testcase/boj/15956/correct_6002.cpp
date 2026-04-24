#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;
map<string, int> mp;
vector<string> v;
vector<int> parent, shortest, setnum;
vector<pair<int, int>> noteqs;

inline void fail() {cout << "0!=0"; exit(0);}
inline void ok() {cout << "0==0"; exit(0);}
int find(int i) {return parent[i] == i ? i : parent[i] = find(parent[i]);}
void joinroot(int i, int j) {
	if(i != j) {
		if(setnum[i] != MOD && setnum[j] != MOD && setnum[i] != setnum[j])
			fail();
		parent[i] = j;
		if(setnum[i] != MOD) setnum[j] = setnum[i];
		if(sz(v[shortest[i]]) < sz(v[shortest[j]]))
			shortest[j] = shortest[i];
	}
}
inline bool isnum(const string &s) {return isdigit(s.back());}

int nextind = 0;
int strind(const string &s) {
	auto it = mp.find(s);
	if(it == mp.end()) {
		mp[s] = nextind;
		v.push_back(s);
		parent.push_back(nextind);
		shortest.push_back(nextind);
		setnum.push_back(isnum(s) ? stoi(s) : MOD);
		nextind++;
		return nextind-1;
	} else {
		return it->second;
	}
}
bool firstprint = true;
inline void print(int s1, bool eq, int s2) {
	if(!firstprint) cout << "&&";
	cout << v[s1] << (eq ? "==" : "!=") << v[s2];
	firstprint = false;
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	string cond;
	cin >> cond;
	string id[2];
	bool equal = true, which = 0;
	for(int i=0; i<sz(cond); i++) {
		char c = cond[i];
		if(isalpha(c) || isdigit(c) || c == '-')
			id[which].push_back(c);
		else {
			i++;
			if(c == '!') {
				equal = false;
				which = 1;
			} else if(c == '=') {
				equal = true;
				which = 1;
			} else if(c == '&') {
				int s1 = find(strind(id[0])), s2 = find(strind(id[1]));
				if(equal)
					joinroot(s1, s2);
				else
					noteqs.emplace_back(s1, s2);
				which = 0;
				id[0] = string();
				id[1] = string();
			}
		}
	}
	int s1 = find(strind(id[0])), s2 = find(strind(id[1]));
	if(equal)
		joinroot(s1, s2);
	else
		noteqs.emplace_back(s1, s2);
	for(auto &pr: noteqs) {
		if(find(pr.first) == find(pr.second))
			fail();
	}
	for(int i=0; i<sz(parent); i++) {
		if(i == shortest[find(i)]) continue;
		print(shortest[find(i)], true, i);
	}
	set<pair<int, int>> marked_uneq;
	for(auto &pr: noteqs) {
		int ia = find(pr.first), ib = find(pr.second);
		int a = setnum[ia], b = setnum[ib];
		if(a != MOD && b != MOD && a != b) continue;
		if(ia > ib) swap(ia, ib);
		pair<int, int> p = {ia, ib};
		if(marked_uneq.find(p) != marked_uneq.end()) continue;
		marked_uneq.emplace(ia, ib);
		print(shortest[ia], false, shortest[ib]);
	}
	if(firstprint)
		ok();
}
