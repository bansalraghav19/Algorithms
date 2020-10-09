struct Node {
	int cnt = 0;
	Node *l, *r;
	Node(): cnt(0), l(nullptr), r(nullptr) {}
	Node(Node* root, int value): cnt(root->cnt + value), l(nullptr), r(nullptr) {}
	Node(Node* L, Node* R): cnt(0), l(L), r(R) {
		if (l) { cnt += l->cnt; }
		if (r) { cnt += r->cnt; }
	}
};
struct Segtree {
	Node* Build(int L, int R) {
		if (L == R) {
			return new Node();
		}
		int M = (L + R) / 2;
		return new Node(Build(L, M), Build(M + 1, R));
	}
	Node* modify(Node* root, int L, int R, int pos, int value) {
		if (L == R) {
			return new Node(root, value);
		}
		int M = (L + R) / 2;
		if (pos <= M) {
			return new Node(modify(root->l, L, M, pos, value), root->r);
		} else {
			return new Node(root->l, modify(root->r, M + 1, R, pos, value));
		}
	}
	int query(Node *root, int L, int R, int ql, int qr) {
		if (L > qr or R < ql) {
			return 0;
		}
		if (L >= ql and R <= qr) {
			return root->cnt;
		}
		int M = (L + R) / 2;
		return query(root->l, L, M, ql, qr) + query(root->r, M + 1, R, ql, qr);
	}
};
