vector<int> ans;
for (auto x : A) {
    auto it = lower_bound(ans.begin(), ans.end(), x);
    if (it == ans.end())
        ans.push_back(x);
    else
        *it = x;
}