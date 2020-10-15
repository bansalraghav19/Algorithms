struct dfs_forest {
  int N;
  vector<vector<int>> v;
  vector<int> height;
  vector<int> Tin;
  vector<int> Tout;
  vector<int> subtree;
  vector<vector<int>> parent;
  dfs_forest(int N) {
    this->N = N;
    v.resize(N + 1);
    height.resize(N + 1);
  }
  void addEdge(int x, int y) {
    v[x].push_back(y);
    v[y].push_back(x);
  }
};
