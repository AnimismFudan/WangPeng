#define Pair pair<int,int>

int build(int L,int R) {
	if (L == R) { f[L] = 0; g[L] = 0; size[L] = 1; return L; }
	int u = 0;
	for (int i = L; i <= R; i++)
		if (dot[i].key > dot[u].key) u = i;
	if (u > L) ls[u] = build(L, u - 1);
	if (u < R) rs[u] = build(u + 1, R);
	update(u);
	return u;
}

int merge(int a,int b) {
	if (!a || !b) return a | b;
	if (dot[a].kay > dot[b].key) {
		rs[a] = merge(rs[a],b);
		update(a); return a;
	}
	else {
		ls[b] = merge(a,ls[b]);
		update(b); return b;
	}
}

Pair split(int a,int k) {
	if (!k) return make_pair(0,a);
	if (k == size[a]) return make_pair(a,0);
	if (k == size[ls[a]]) {
		int b = ls[a]; ls[a] = 0;
		update(a); update(b);
		return make_pair(b,a);
	} else if (k < size[ls[a]]) {
		Pair p = split(ls[a],k);
		ls[a] = p.second;
		update(a);
		p.second = a;
		return p;
	} else if (k == size[ls[a]] + 1) {
		int b = rs[a]; rs[a] = 0;
		update(a);
		return make_pair(a,b);
	} else {
		Pair p = split(rs[a],k - size[ls[a]] - 1);
		rs[a] = p.first;
		update(a);
		p.first = a;
		return p;
	}
}
