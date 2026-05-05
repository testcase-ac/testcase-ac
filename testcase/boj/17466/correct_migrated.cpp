#include<iostream>
#define int long
using namespace std;


int fast_frac_mod(int minN,int maxN,int P){
  if(minN==maxN)return minN;
  return fast_frac_mod(minN,minN+(maxN-minN)/2,P)%P * fast_frac_mod(minN+(maxN-minN)/2+1,maxN,P)%P;
}
int32_t main(){
  int N,P;
  cin>>N>>P;
  cout<<fast_frac_mod(1,N,P);
}
