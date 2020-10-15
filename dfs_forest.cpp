struct dfs_forest {
  const int LEVEL = 20;
  int N, timer;
  vector<vector<int>> v;
  vector<int> depth;
  vector<int> Tin;
  vector<int> Tout;
  vector<int> subtree;
  vector<int> rTin;
  vector<int> next;
  vector<vector<int>> parent;
  dfs_forest(int N): timer(0) {
    this->N = N;
    v.resize(N + 1);
    depth.resize(N + 1);
    Tin.resize(N + 1);
    Tout.resize(N + 1);
    subtree.resize(N + 1);
    rTin.resize(N + 1);
    next.resize(N + 1);
    parent.resize(N + 1, vector<int>(LEVEL, -1));
  }
  void addEdge(int x, int y) {
    v[x].push_back(y);
    v[y].push_back(x);
  }
  void dfs_init(int cur, int prev = -1) {
    Tin[cur] = ++timer;
    parent[cur][0] = prev;
    subtree[cur] = 1;
    for (auto &child : v[cur]) {
      if (child != prev) {
        depth[child] = depth[prev] + 1;
        dfs_init(child, cur);
        subtree[cur] += subtree[child];
      }
    }
    Tout[cur] = timer;
  }
  void precomputeSparseMatrix() {
    for (int i = 1; i < LEVEL; i++) {
      for (int node = 1; node <= N; node++) {
        if (parent[node][i - 1] != -1) {
          parent[node][i] = parent[parent[node][i - 1]][i - 1];
        }
      }
    }
  }
  int lca(int u, int v) {
    if (depth[v] < depth[u]) {
      swap(u, v);
    }
    int diff = depth[v] - depth[u];
    for (int i = 0; i < LEVEL; i++) {
      if ((diff >> i) & 1) {
        v = parent[v][i];
      }
    }
    if (u == v) {
      return u;
    }
    for (int i = LEVEL - 1; i >= 0; i--) {
      if (parent[u][i] != parent[v][i]) {
        u = parent[u][i];
        v = parent[v][i];
      }
    }
    return parent[u][0];
  }
  int dist(int x, int y) {
    return depth[x] + depth[y] - 2 * depth[lca(x, y)];
  }
};
