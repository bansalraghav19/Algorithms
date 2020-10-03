struct DSU {
	vector<int> A;
	vector<int> sz;
	DSU(int n) {
		A.resize(n + 10);
		sz.resize(n + 10);
		init(n);
	};
	void init(int n) {
		for (int i = 0; i <= n; i++) {
			sz[i] = 1;
			A[i] = i;
		}
	}
	int find(int i) {
		while (A[i] != i) {
			A[i] = A[A[i]];
			i = A[i];
		}
		return i;
	}
	int _union(int xr, int yr) {
		xr = find(xr), yr = find(yr);
		if (xr == yr) {
			return -1;
		}
		if (sz[xr] < sz[yr]) {
			A[xr] = A[yr];
			sz[yr] += sz[xr];
		} else {
			A[yr] = A[xr];
			sz[xr] += sz[yr];
		}
		return 0;
	}
};
