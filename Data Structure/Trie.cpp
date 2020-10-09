struct Node {
	unordered_map<char, Node*> next;
	bool isEnd;
	Node(): isEnd(false) {}
};
struct Trie {
	Node* root;
	Trie() {
		root = new Node();
	}
	void modify(const string &s) {
		Node* rt = root;
		for (auto &i : s) {
			if (!rt->next.count(i)) {
				rt->next[i] = new Node();
			}
			rt = rt->next[i];
		}
		rt->isEnd = true;
	}
	bool query(const string &s) {
		Node *rt = root;
		for (auto &i : s) {
			if (!rt->next.count(i)) {
				return false;
			}
			rt = rt->next[i];
		}
		return rt->isEnd;
	}
};
