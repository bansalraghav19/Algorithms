vector<vector<int>> v(n + 1), vrev(n + 1);
	vector<int> seen(n + 1);
	vector<int> component_number(n + 1);
	int graph_number = 0;
	vector<int> st;
	function<void(int)> dfs = [&](int cur) {
		seen[cur] = 1;
		for (auto &i : v[cur]) {
			if (!seen[i]) {
				dfs(i);
			}
		}
		st.push_back(cur);
	};
	function<void(int)> Kosaraju = [&](int cur) {
		seen[cur] = 1;
		component_number[cur] = graph_number;
		for (auto &i : vrev[cur]) {
			if (!seen[i]) {
				Kosaraju(i);
			}
		}
	};
