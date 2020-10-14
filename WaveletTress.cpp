struct Node {
	Node *l , *r;
	int L, R;
	vector<int> B;
};
struct WaveletTrees {
	int N;
	Node* Root;
	vector<int> v;
	WaveletTrees(const vector<int> &v) {
		this->v = v;
		this->N = (int)v.size();
		Root = new Node();
		int MX = *max_element(v.begin(), v.end());
		Build(Root, 0, N - 1, 1, MX);
	}
	void Build(Node *Root, int i, int j, int L, int R) {
		if (i >= j or L > R) {
			return;
		}
		Root->L = L;
		Root->R = R;
		Root->l = new Node();
		Root->r = new Node();
		Root->B.resize(j - i);
		int M = (L + R) / 2;
		Root->B[0] = (v[i] <= M);
		for (int start = i + 1; start < j; start++) {
			Root->B[start - i] = Root->B[start - i - 1] + (v[start] <= M);
		}
		int p = stable_partition(&v[i], &v[j], [M](int x) {
			return x <= M;
		}) - &v[i];
		Build(Root->l, i, p, L, M);
		Build(Root->r, p, j, M + 1, R);
	}
	int query(Node *Root, int ql, int qr, int k) {
		if (ql > qr) {
			return 0;
		}
		if (Root->L == Root->R) {
			return Root->L;
		}
		int left = Root->B[qr] - Root->B[ql - 1];
	}
	int query(int L, int R, int k) {
		return query(Root, L, R, k);
	}
};
