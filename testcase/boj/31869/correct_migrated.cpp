#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#define ll long long
using namespace std;

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	ll N, i, w, d, p;
	string s;
	vector <pair <pair <string, ll>, pair <ll, ll> > > v;
	map <string, ll> money;

	cin >> N;
	for (i = 1; i <= N; i++)
	{
		cin >> s >> w >> d >> p;
		v.push_back({ {s,w,},{d,p} });
	}
	for (i = 1; i <= N; i++)
	{
		cin >> s >> p;
		money[s] = p;
	}

	bool day[80] = { 0 };
	for (i = 0; i < N; i++)
	{
		if (v[i].second.second <= money[v[i].first.first]) //가지고 있는 돈보다 작거나 같다면
			day[v[i].first.second * 7 + v[i].second.first] = true;
	}

	ll cnt = 0, mx = 0;
	for (i = 0; i < 80; i++)
	{
		if (day[i]) cnt++;
		else cnt = 0;
		mx = max(mx, cnt);
	}

	cout << mx;
}
// [출처] 선배님 밥 사주세요! (백준 31869)|작성자 jihwanmoon0319 https://blog.naver.com/jihwanmoon0319/223456124229
