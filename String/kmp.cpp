int app(string s, string t){ // Returns number of times s appears in t
	int n = s.length(), m = t.length();
	if (n>m) return 0;
	vector<int> f(n); f[0]=-1;
	for (int i = 1; i<n; i++){
		f[i] = f[i-1];
		while (f[i]!=-1 && s[f[i]+1]!=s[i]) f[i] = f[f[i]];
		if (s[f[i]+1]==s[i]) f[i]++;
	}
	int j = 0, re = 0;
	for (int i = 0; i<m; i++){
		if (t[i] == s[j]) j++;
		else if (j) j = f[j-1]+1, i--;
		if (j==n) re++, j = f[j-1]+1;
	}
	return re;
}
