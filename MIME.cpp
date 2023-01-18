#include<iostream>
#include<string>
#include<map>
#include<algorithm>
#include<sstream>

using namespace std;

int main() {
	int n, q;
	cin >> n >> q;
	map<string, string> type;
	for (int i = 0; i<n; ++i) {
		string a, b;
		cin >> a >> b;
		transform(begin(a), end(a), begin(a), ::toupper);
		type[a] = b;
	}

	for (int i = 0; i<q; ++i) {
		string f;
		cin >> f;
		istringstream ff(f);
		string ext;
		while (getline(ff, ext, '.'));

		if (ext == f) {
			cout << "UNKNOWN\n";
			continue;
		}

		transform(begin(ext), end(ext), begin(ext), ::toupper);

		auto res = type.find(ext);
		if (res == end(type))
			cout << "UNKNOWN\n";
		else
			cout << res->second << '\n';

	}
}