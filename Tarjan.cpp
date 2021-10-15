#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<vector>
#include<set>
#include<cmath>
#include<map>
#include<stack>
using namespace std;
#define ll long long
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define inf 0x3f3f3f3f
typedef pair<int,int> PII;
template <typename T>
void in(T &x){
    x=0;
    int f=1;
    char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(!isdigit(ch));
    do{x=x*10+ch-'0';ch=getchar();}while(isdigit(ch));
     x*=f;
}
//////////////head
const int N=1E5+5;
// Tarjan
// 获得每个节点的dfn
// 获得每个节点最小的low
// 若当前点恰好为当前环的入点
//     替换环中所有的low
//     同时将当前环的大小记录在入点中
struct E{
    int to,nxt;
}e[N];
int nxt[N],ring[N],head[N],cnt,dfn[N],low[N],ans[N],num,vis[N],sum,st[N],top,import[N];
void add(int u,int v){
    e[++cnt]={v,head[u]};
    head[u]=cnt;
}
void Tarjan(int u){
    sum++;
    st[top++]=u;
    vis[u]=1;
    low[u]=dfn[u]=sum;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(vis[v]==0){
            Tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(vis[v]==1){
            low[u]=min(low[v],low[u]);
        }
    }
    if(low[u]==dfn[u]){
        num++;
        do{
            top--;
            vis[st[top]]=-1;
            import[st[top]]=num;
        }while(st[top]!=u);
    }
    return ;
}
void search(int rt,int now,int step){
    if(ans[now]!=0){
        ans[rt]=ans[now]+step;
        return;
    }
    search(rt,nxt[now],step+1);
}
int main(){
    int n;in(n);
    rep(i,1,n){
        in(nxt[i]);
        add(i,nxt[i]);
        if(i==nxt[i])ans[i]=1;
    }
    rep(i,1,n){
        if(vis[i]==0)Tarjan(i);
    }
    rep(i,1,n){
        if(import[i]!=0)ring[import[i]]++;
    }
    rep(i,1,n){
        if(import[i]!=0&& ring[import[i]]!=1)ans[i]=ring[import[i]];
    }
    rep(i,1,n){
        if(!ans[i])search(i,nxt[i],1);
    }
    rep(i,1,n)printf("%d\n",ans[i]);
    return 0;
}
