#include <iostream>
using namespace std; 
int n,maxd,a[100];
 
bool dfs(int d,int maxn){
	if(a[d]==n) {
		cout<<d<<endl;
		return true;
	}
	if(d==maxd) return false;
	maxn=max(maxn, a[d]);//The previous ones have been compared, only need to compare the newly generated ones. 
	if(maxn<<(maxd-d)<n) return false;
	for(int i=d;i>=0;i--){
			 a[d+1]=a[d]+a[i];//Always use the last generated value
			if(dfs(d+1,maxn) ) return true;	
			a[d+1]=a[d]-a[i];
			if(dfs(d+1,maxn)) return true;		
	}	
	return false;
}
 
int main(int argc, char** argv) {
	a[0]=1;
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    for(maxd=0; ;maxd++)
			if(dfs(0,1)) break;
  }
}
