vector<int> prefix_function(const string &s) {
  vector<int> pi((int)s.size());
  for (int i = 1; i < (int)s.size(); i++) {
    int j = pi[i - 1];
    while (j and s[i] != s[j]) {
      j = pi[j - 1];
    }
    pi[i] = j + (s[i] == s[j]);
  }
  return pi;
}
