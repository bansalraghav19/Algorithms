struct Node {
  int mx;
  Node(int x = 0): mx(x) {}
};
struct Segtree {
  int N;
  vector<Node> sg;
  vector<int> lazy;
  void init(int N) {
    this->N = N + 10;
    sg.resize(4 * N + 10);
    lazy.resize(4 * N + 10);
  }
  void merge(Node &res, Node L, Node R) {
    res.mx = max(L.mx, R.mx);
  }
  void propogate(int node, int L, int R) {
    if (L != R) {
      lazy[2 * node] += lazy[node];
      lazy[2 * node + 1] += lazy[node];
    }
    sg[node].mx += lazy[node];
    lazy[node] = 0;
  }
  void modify(int node, int L, int R, int ul, int ur, int value) {
    if (lazy[node]) {
      propogate(node, L, R);
    }
    if (ul < L or ur > R) {
      return;
    }
    if (ul <= L and R <= ur) {
      lazy[node] += value;
      propogate(node, L, R);
      return;
    }
    int M = (L + R) / 2;
    modify(2 * node, L, M, ul, ur, value);
    modify(2 * node + 1, M + 1, R, ul, ur, value);
    merge(sg[node], sg[2 * node], sg[2 * node + 1]);
  }
  Node Query(int node, int L, int R, int ql, int qr) {
    if (lazy[node]) {
      propogate(node, L, R);
    }
    if (ql < L or qr > R) {
      return Node();
    }
    if (ql <= L and R <= qr) {
      return sg[node];
    }
    int M = (L + R) / 2;
    Node left = Query(node * 2, L, M, ql, qr);
    Node right = Query(node * 2 + 1, M + 1, R, ql, qr);
    Node cur;
    merge(cur, left, right);
    return cur;
  }
};
