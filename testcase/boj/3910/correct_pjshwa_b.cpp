#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
#define inf 1e9

using namespace std;

int ans[1010];
queue<pair<int,vector<int>>> q;

int main(){
	int t,n;
	for(int i=2;i<1001;++i)ans[i]=inf;
	q.push({1,vector<int>()});
	while(q.size()){
		pair<int,vector<int>> p=q.front();
		vector<int> v=p.second;
		v.push_back(p.first);
		q.pop();
		for(auto i:p.second){
			if(p.first+i<1001&&ans[p.first+i]>=ans[p.first]+1){
				ans[p.first+i]=ans[p.first]+1;
				q.push({p.first+i,v});
			}
			if(p.first-i>0&&ans[p.first-i]>=ans[p.first]+1){
				ans[p.first-i]=ans[p.first]+1;
				q.push({p.first-i,v});
			}
		}
		if(p.first*2<1001&&ans[p.first*2]>=ans[p.first]+1){
			ans[p.first*2]=ans[p.first]+1;
			q.push({p.first*2,v});
		}
	}
	for(scanf("%d",&t);t--;){
		scanf("%d",&n);
		printf("%d\n",ans[n]);
	}
}
