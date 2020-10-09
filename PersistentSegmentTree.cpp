struct Node {
  int cnt = 0;
  Node *l, *r;
  Node(): cnt(0), l(nullptr), r(nullptr) {}
  Node(Node* root): cnt(root->cnt + 1), l(nullptr), r(nullptr) {}
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
  Node* modify(Node* root, int L, int R, int pos) {
    if (L == R) {
      return new Node(root);
    }
    int M = (L + R) / 2;
    if (pos <= M) {
      return new Node(modify(root->l, L, M, pos), root->r);
    } else {
      return new Node(root->l, modify(root->r, M + 1, R, pos));
    }
  }
  int query(Node *right, Node *left, int L, int R, int k) {
    int ans = -1;
    while (L <= R) {
      int M = (L + R) / 2;
      int count = (right->l ? right->l->cnt : 0) - (left->l ? left->l->cnt : 0);
      if (L == R) {
        if (ans == -1) {
          return L;
        }
      }
      if (count >= k) {
        ans = M;
        R = M - 1;
        right = right->l;
        left = left->l;
      } else {
        L = M + 1;
        right = right->r;
        left = left->r;
        k -= count;
      }
    }
    return ans;
  }
};
