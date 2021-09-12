// 将正数n分为k份，求划分方法的种数，顺序不同的k份数视为一种方法
#include<bits/stdc++.h>
using namespace std;

int n,k,ans=0;

void dfs(int lf_num,int num,int lf_cnt){
    if(!lf_cnt){
        if(!lf_num) ans++;
        return;
    }
    // 为了避免重复后一次选的数要比前一次大
    for(int i=num;i<=lf_num;i++){
        dfs(lf_num-i,i,lf_cnt-1);
    }
}

int main(){
    scanf("%d%d",&n,&k);
    dfs(n,1,k);
    cout<<ans<<endl;
    return 0;
}