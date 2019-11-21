#include<bits/stdc++.h>

using namespace std;

const int maxn=1e5+10;

#define inf 0x3f3f3f3f

int d[maxn],n;
struct node{
    int v,w;
    node(int v,int w):v(v),w(w){}
    node(){}
};

vector<node> g[maxn];

void bfs(int u){
    for(int i=0;i<n;i++) d[i]=inf;
    queue<int> q;
    q.push(u);
    d[u]=0;
    while(!q.empty()){
        u=q.front();q.pop();
        int len=g[u].size();
        for(int i=0;i<len;i++){
            if(d[g[u][i].v]==(int)inf){
                d[g[u][i].v]=d[u]+g[u][i].w;
                q.push(g[u][i].v);
            }
        }
    }
}

void solve(){
    bfs(0);
    int mx=0,t=0;
    for(int i=0;i<n;i++){
        if(d[i]==(int)inf) continue;
        if(mx<d[i]){
            mx=d[i],t=i;
        }
    }
    bfs(t);
    mx=0;
    for(int i=0;i<n;i++){
        if(d[i]==(int)inf) continue;
        mx = max(mx,d[i]);
    }
    printf("%d\n",mx);
}

int main(){
    int u,v,w;
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        g[u].push_back(node(v,w));
        g[v].push_back(node(u,w));
    }
    solve();
    return 0;
}
