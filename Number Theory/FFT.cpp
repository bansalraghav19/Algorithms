using cd = complex<double>;
double PI = acos(-1);
void fft(vector<cd> &v, bool inverse) {
  const int n = (int)v.size();
  for (int i = 1, j = 0; i < n; i++) {
    int bit = (n >> 1);
    while (bit & j) {
      j ^= bit;
      bit >>= 1;
    }
    j ^= bit;
    if (i < j) {
      swap(v[i], v[j]);
    }
  }
  for (int len = 2; len <= n; len <<= 1) {
    double ang = 2 * PI / len * (inverse ? -1 : 1);
    cd wd(cos(ang), sin(ang));
    for (int s = 0; s < n; s += len) {
      cd w(1);
      for (int i = 0; i < len / 2; i++) {
        cd x = v[s + i], y = v[s + i + len / 2] * w;
        v[s + i] = x + y;
        v[s + i + len / 2] = x - y;
        w *= wd;
      }
    }
  }
  if (inverse) {
    for (auto &i : v) {
      i /= n;
    }
  }
}
vector<int> multiply(vector<int> &a, vector<int> &b) {
  vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1;
  while ((int)a.size() + (int)b.size() > n) {
    n <<= 1;
  }
  fa.resize(n); fb.resize(n);
  fft(fa, false);
  fft(fb, false);
  for (int i = 0; i < n; i++) {
    fa[i] *= fb[i];
  }
  fft(fa, true);
  vector<int> ans(n);
  for (int i = 0; i < n; i++) {
    ans[i] = round(fa[i].real());
  }
  return ans;
}
