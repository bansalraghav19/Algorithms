struct Edmonds_Karp {
  const int INF = (int)1e9;
  int N, source, sink;
  vector<vector<int>> capacity;
  vector<vector<int>> v;
  vector<bool> seen;
  Edmonds_Karp(int N, int source, int sink) {
    this->N = N;
    this->source = source;
    this->sink = sink;
    v.resize(N + 1);
    capacity = vector(N + 1, vector(N + 1, 0LL));
    seen = vector(N + 1, false);
  }
  void addEdge(int x, int y, int cap) {
    v[x].push_back(y);
    v[y].push_back(x);
    capacity[x][y] += cap;
  }
  int dfs(int cur, int cap) {
    if (cur == this->sink) {
      return cap;
    }
    seen[cur] = true;
    for (auto &i : v[cur]) {
      if (capacity[cur][i] and !seen[i]) {
        int flow = dfs(i, min(capacity[cur][i], cap));
        if (flow) {
          capacity[cur][i] -= flow;
          capacity[i][cur] += flow;
          return flow;
        }
      }
    }
    return 0;
  }
  int max_flow() {
    int flow = 0;
    int sent = -1;
    while (sent != 0) {
      seen = vector(this->N + 1, false);
      sent = dfs(this->source, INF);
      flow += sent;
    }
    return flow;
  }
};
