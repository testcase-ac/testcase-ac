#include <stdio.h>
#include <algorithm>
using namespace std;
int n,a[1005],b[1005];
int rst,r;
int main(){
	scanf("%d",&n);
	int i,k,j;
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	for(i=1;i<=n;i++)scanf("%d",&b[i]);
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	for(i=1;i<=n;i++){
		r=0;
		for(j=i,k=1;j<=n;j++,k++){
			if(a[j]==b[k])r++;
			else if(a[j]>b[k])r+=2;
		}
		rst=max(rst,r);
	}printf("%d",rst);
}
