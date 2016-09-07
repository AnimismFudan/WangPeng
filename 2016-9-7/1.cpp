#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#define maxn 210
#define INF (1 << 30)
using namespace std;

queue <int> que;

struct str { int v,nex,cap,cost; } edge[101000];

int e,n,m,s,t;
int f[maxn],vis[maxn],fst[maxn],h[maxn],dis[maxn],mark[maxn];
int ans,flow;

void make_edge(int a,int b,int cap,int cost) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b; edge[e].cap = cap; edge[e].cost =  cost;
	edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a; edge[e].cap = 0;   edge[e].cost = -cost;
}

bool bfs() {
	for (int i = 1; i <= t; i++) dis[i] = 1 << 29;
	dis[s] = 0;
	for (int i = 1; i <= t; i++) mark[i] = 0;
	que.push(s); mark[s] = 1;

	while (!que.empty()) {
		int u = que.front();
		que.pop(); mark[u] = 0;
		for (int i = fst[u]; i; i = edge[i].nex) {
			int v = edge[i].v;
			if (!edge[i].cap) continue;
			if (dis[v] > dis[u] + edge[i].cost) {
				dis[v] = dis[u] + edge[i].cost;
				if (!mark[v]) {
					mark[v] = 1;
					que.push(v);
				}
			}
		}
	}

	return (dis[t] != (1 << 29));
}

int dfs(int u,int ma) {
	if (vis[u]) return 0;	
	if (u == t || !ma) return ma;
	vis[u] = 1;
	int f,flow = 0;
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		if (dis[v] == dis[u] + edge[i].cost && (f = dfs(v, min(edge[i].cap,ma)))) {
			flow += f; ma -= f;
			edge[i].cap -= f; edge[i ^ 1].cap += f;
			//ans += edge[i].cost * f;
			if (!ma) {
				vis[u] = 0;
				return flow;
			}
		}
	}
	vis[u] = 0;
	dis[u] = INF;
	return flow;
}

void solve() {	
	while(bfs()) {
		int flow = dfs(s,INF);
		ans += flow * dis[t];
	}
}

int main() {
	freopen("D.in","r",stdin);
	freopen("D.out","w",stdout);
	scanf("%d %d",&n,&m);
	s = n + 1; t = s + 1; e = 1;
	for (int i = 1; i <= m; i++) {
		int a, b, c, d;
		scanf("%d %d %d %d",&a,&b,&c,&d);
		f[b] += d; f[a] -= d;
		if (c > d) {
			make_edge(a, b, c - d, 1);
			make_edge(a, b, INF, 2);
			make_edge(b, a, d, 1);
		} else {
			make_edge(a, b, INF, 2);
			make_edge(b, a, d - c, 0);
			make_edge(b, a, c, 1);
			ans += d - c;
		}
	}

	for (int i = 2; i <= n - 1; i++) {
		if (f[i] > 0) make_edge(s, i,  f[i], 0);
		if (f[i] < 0) make_edge(i, t, -f[i], 0);
	}

	make_edge(1, n, INF, 0);

	make_edge(n, 1, INF, 0);

	if (f[1] + f[n] > 0) make_edge(s, 1, f[1] + f[n], 0);
	if (f[1] + f[n] < 0) make_edge(1, t,-(f[1] + f[n]), 0);
	
	solve();
		  
	printf("%d\n",ans);
	return 0;
}
