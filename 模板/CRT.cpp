void Gcd(intl a,intl b) {
	if (!b) { x = 1LL; y = 0; return; }
	Gcd(b,a % b);
	swap(x,y); y = y - (a / b) * x;
}
intl gcd(intl a,intl b) {
	return(b ? gcd(b,a % b) : a);
}
void upt(intl &x,intl a) { x = (x % a + a) % a; }
intl C(intl a,intl b,intl Mo) {
	intl ans = 0;
	while (b) {
		if (b & 1LL) (ans += a) %= Mo;
		(a += a) %= Mo;
		b >>= 1;
	}
	return ans;}
int main() {
	while (scanf("%d",&n) != EOF) {
		for (i = 1; i <= n; i++) scanf("%lld %lld",&A[i],&R[i]);
		for (i = 2; i <= n; i++) {
			if (R[i] < R[1]) swap(R[i],R[1]), swap(A[i],A[1]);
			js = gcd(A[1],A[i]);
			if ((R[i] - R[1]) % js) break;
			Gcd(A[1] / js,A[i] / js);
			upt(x,A[i] / js); x *= (R[i] - R[1]) / js;
			a = A[1] * A[i] / js; b = (C(x,A[1],a) + R[1]) % a;
			A[1] = a; R[1] = b;
		}
		if (i <= n) printf("-1\n");
		else printf("%lld\n",(R[1] % A[1] + A[1]) % A[1]);
	}
}
return 0;
