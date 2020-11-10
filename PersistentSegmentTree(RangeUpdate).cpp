struct Node {
  Node *left, *right;
  int mx, lazy;
  Node(): left(nullptr), right(nullptr), mx(0), lazy(0) {}
  Node(Node* l, Node *r): left(l), right(r) {}
};
struct Segtree {
  Node* Build(int L, int R) {
    if (L == R) {
      return new Node();
    }
    int M = (L + R) / 2;
    return new Node(Build(L, M), Build(M + 1, R));
  }
  Node *lazyKid(Node* root, int value) {
    Node *kid = new Node(root->left, root->right);
    kid->lazy = root->lazy;
    kid->lazy += value;
    kid->mx = root->mx + value;
    return kid;
  }
  Node *NewParent(Node *left, Node *right) {
    Node *NewNode = new Node(left, right);
    NewNode->mx = max(left->mx, right->mx);
    return NewNode;
  }
  void Propogate(Node* root, int L, int R) {
    if (root->lazy) {
      if (L != R) {
        root->left = lazyKid(root->left, root->lazy);
        root->right = lazyKid(root->right, root->lazy);
      }
      root->lazy = 0;
    }
  }
  Node* Modify(Node *root, int L, int R, int ql, int qr, int value) {
    if (ql > R or qr < L) {
      return root;
    }
    if (L >= ql and qr >= R) {
      return lazyKid(root, value);
    }
    Propogate(root, L, R);
    int M = (L + R) / 2;
    return NewParent(Modify(root->left, L, M, ql, qr, value), Modify(root->right, M + 1, R, ql, qr, value));
  }
  int Query(Node *root, int L, int R, int ql, int qr) {
    if (R < ql or qr < L) {
      return 0;
    }
    if (L >= ql and qr >= R) {
      return root->mx;
    }
    Propogate(root, L, R);
    int M = (L + R) / 2;
    return max(Query(root->left, L, M, ql, qr), Query(root->right, M + 1, R, ql, qr));
  }
};
