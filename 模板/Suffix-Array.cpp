void get_suffix() {
	int i,j;
	for (i = 1; i <= top; i++) rank[i] = s[i] - 'a' + 1;
	for (i = 1; i <= top; i++) wp[rank[i]]++;
	for (i = 1; i <= 30; i++) wp[i] += wp[i - 1];
	for (i = top; i; i--) SA[wp[rank[i]]--] = i;
	int u,q;
	for (q = 1; q < top; q <<= 1) {
		memset(wp,0,sizeof(wp));
		memcpy(SA_,SA,sizeof(SA));
		for (i = 1; i <= top; i++) wp[rank[i]]++;
		for (i = 1; i <= top; i++) wp[i] += wp[i - 1];
		for (i = top; i; i--)
			if (SA_[i] > q) SA[wp[rank[SA_[i] - q]]--] = SA_[i] - q;
		for (i = top - q + 1; i <= top; i++) SA[wp[rank[i]]--] = i;
		memcpy(rank_,rank,sizeof(rank));
		rank[SA[1]] = u = 1;
		for (i = 2; i <= top; i++) {
			if (judge(rank_,SA[i],SA[i - 1],q)) rank[SA[i]] = u;
			else rank[SA[i]] = ++u;
		}
	}
}
void get_height() {
	for (i = 1; i <= top; i++) {
		if (rank[i] == 1) { H[rank[i]] = 0; continue; }
		H[rank[i]] = max(H[rank[i - 1]] - 1,0);
		while (s[i + H[rank[i]]] == s[SA[rank[i] - 1] + H[rank[i]]]) H[rank[i]]++;
	}
}
