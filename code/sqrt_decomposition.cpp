#include <bits/stdc++.h>
using namespace std;

const int N = 16777216, N_SQRT = 4096;
struct st {
    pair<int, int> ask(int l, int r) {
        return make_pair(l / N_SQRT + bool(l % N_SQRT), r / N_SQRT);
    }
    
    vector<unsigned int> base, pls, flag;
    st() {
        base.resize(N, 0);
        pls.resize(N_SQRT, 0);
        flag.resize(N_SQRT, 0);
    }
    
    void relax_flag(int pos) {
        if (flag[pos] == 0) return;
        for (int i = pos * N_SQRT; i < (pos + 1) * N_SQRT; i++) base[i] += flag[pos];
        flag[pos] = 0;
    }
    
    void add(int value, int l, int r) {
        l--, r--;
        pair<int, int> block = ask(l, r);
        if (block.first >= block.second) {
            for (int i = l; i <= r; i++) base[i] += value;
            pls[block.second] += (r - l + 1) * value;
            return;
        }
        for (int i = block.first; i < block.second; i++) pls[i] += value * N_SQRT, flag[i] += value;
        for (int i = l; i < block.first * N_SQRT; i++) base[i] += value, pls[i / N_SQRT] += value;
        for (int i = block.second * N_SQRT; i <= r; i++) base[i] += value, pls[i / N_SQRT] += value;
    }
    
    unsigned int get(int l, int r) {
        l--, r--;
        pair<int, int> block = ask(l, r);
        unsigned int ans = 0;
        relax_flag(block.first), relax_flag(block.second);
        if (block.first > 0) relax_flag(block.first - 1);
        if (block.second < N_SQRT) relax_flag(block.second + 1);
        if (block.first >= block.second) {
            for (int i = l; i <= r; i++) ans += base[i];
            return ans;
        }
        for (int i = block.first; i < block.second; i++) ans += pls[i];
        for (int i = l; i < block.first * N_SQRT; i++) ans += base[i];
        for (int i = block.second * N_SQRT; i <= r; i++) ans += base[i];
        return ans;
    }
};
