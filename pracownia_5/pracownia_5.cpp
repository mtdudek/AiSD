#include <cstdio>
#include <vector>

std::vector<std::vector<int>> G;
std::vector<std::pair<int,int>> ans;

void dfs(int v,int p){
    if(v!=p&&G[v].size()==1){
        ans[v].first=1;
        ans[v].second=0;
        return;
    }
    for (int i=0;i<G[v].size();i++)
        if(G[v][i]!=p)
            dfs(G[v][i],v);
    int best1,best2,sum=0;
    best2=best1=0x7FFFFFFF;
    for (int i=0;i<G[v].size();i++){
        int o=G[v][i];
        if(o!=p){
            sum+=ans[o].first;
            int a=ans[o].second-ans[o].first;
            if (a<best1){
                best2=best1;
                best1=a;
            } else if (a <best2){
                best2=a;
            }
        }
    }
    ans[v].first=sum;
    if(best1!=0x7FFFFFFF)
        ans[v].first=std::min(ans[v].first,sum+best1);
    if(best2!=0x7FFFFFFF)
        ans[v].first=std::min(ans[v].first,sum+best1+best2);
    ans[v].first++;
    ans[v].second=std::min(sum+best1,sum);
}

int main(){
    int n;
    scanf("%d",&n);
    G.resize(n);
    ans.resize(n);
    for (int i=0;i<n-1;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        G[a-1].push_back(b-1);
        G[b-1].push_back(a-1);
    }
    dfs(0,0);
    printf("%d\n",ans[0].first);
    return 0;
}
