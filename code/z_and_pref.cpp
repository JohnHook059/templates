#include <vector>
#include <string>
#include <algorithm>

std::vector<int> z(std::string s) {
    std::vector<int> zf(s.length());
    int left = 0, right = 0;
    for (int i = 1; i < s.length(); ++i) {
        zf[i] = std::max(0, std::min(right - i, zf[i - left]));
        while (i + zf[i] < s.length() && s[zf[i]] == s[i + zf[i]])
            zf[i]++;
        if (i + zf[i] >= right) {
            left = i;
            right = i + zf[i];
        }
    }
    return zf;
}

std::vector<int> pref(std::string s) {
    std::vector<int> pf(s.length());
    pf[0] = 0;
    int k;
    for (int i = 1; i < s.length(); ++i) {
        k = pf[i - 1];
        while (k > 0 && s[i] != s[k])
            k = pf[k - 1];
        if (s[i] == s[k])
            k++;
        pf[i] = k;
    }
    return pf;
}

// Authors = JohnHook
// z и префикс функции
// На входе строка, на выходе вектор интов
