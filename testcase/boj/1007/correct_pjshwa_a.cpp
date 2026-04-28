#include <iostream>
#include <algorithm>
#include <vector>
#include <float.h>
#include <math.h>

using namespace std;

int t, n, y, x;
pair<int, int> mx;

vector<pair<int, int>> v;

double solve(pair<int, int> now, int pos, int dp)
{
	if(pos == n){
		if(dp*2 == n){
			return sqrt(pow(mx.first - (2*now.first), 2) + pow(mx.second - (2*now.second), 2));
		}
		return DBL_MAX;
	}
	
	double rt = DBL_MAX;
	rt = min(rt, solve(now, pos+1, dp));
	
	now.first += v[pos].first;
	now.second += v[pos].second;
	rt = min(rt, solve(now, pos+1, dp+1));
	
	return rt;
}

int main()
{
	cin >> t;
	while(t-- > 0){
		v.resize(0);
		mx.first = 0;
		mx.second = 0;
		cin >> n;
		
		for(int i = 0; i < n; i++){
			cin >> y >> x;
			v.push_back({y, x});
			mx.first += y;
			mx.second += x;
		}
		
		printf("%.12f\n", solve({0, 0}, 0, 0));
	}
}