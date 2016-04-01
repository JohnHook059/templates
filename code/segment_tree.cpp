template <typename T>
class tree {
private:
    vector<T> base, flag, pub;
    T (*comp)(const T &, const T &);
    T neutral;
    
    void relax_flag(int v) {
        if (v * 2 < flag.size()) flag[v * 2] = comp(flag[v * 2], flag[v]);
        if (v * 2 + 1 < flag.size()) flag[v * 2 + 1] = comp(flag[v * 2 + 1], flag[v]);
        flag[v] = neutral;
    }
    void _public_update(int left, int right, T new_value, int v, int l, int r) {
        if (right <= l || left >= r) return;
        if (left <= l && right >= r) {
            flag[v] = comp(flag[v], new_value);
            return;
        }
        relax_flag(v);
        _public_update(left, right, new_value, v * 2, l, (l + r) / 2);
        _public_update(left, right, new_value, v * 2 + 1, (l + r) / 2, r);
        pub[v] = comp(comp(pub[v * 2], flag[v * 2] * (r - l) / 2), comp(pub[v * 2 + 1], flag[v * 2 + 1] * (r - l) / 2)); // TODO * -> T public_comp()
    }
    T _public_get(int left, int right, int v, int l, int r) {
        if (right <= l || left >= r) return neutral;
        if (left <= l && right >= r)
            return comp(pub[v], flag[v] * (r - l)); // TODO * -> T public_comp()
        relax_flag(v);
        return comp(_public_get(left, right, v * 2, l, (l + r) / 2), _public_get(left, right, v * 2 + 1, (l + r) / 2, r));
    }
public:
    tree(const vector<T> &v, T (*comp)(const T &, const T &), T neutral) : comp(comp), neutral(neutral) {
        int st = 1;
        while (st < v.size())
            st <<= 1;
        base.resize(st << 1);
        flag.resize(st << 1);
        pub.resize(st << 1);
        for (int i = st; i < st + v.size(); ++i)
            base[i] = v[i - st];
        for (int i = st + int(v.size()); i < st << 1; ++i)
            base[i] = neutral;
        for (int i = st - 1; i > 0; --i)
            base[i] = comp(base[i << 1], base[(i << 1) + 1]);
    }
    void single_update(int pos, T new_value) {
        pos += base.size() >> 1;
        base[pos] = new_value;
        while (pos > 1) {
            pos >>= 1;
            base[pos] = comp(base[pos << 1], base[(pos << 1) + 1]);
        }
    }
    void public_update(int left, int right, T new_value) {
        _public_update(left, right, new_value, 1, 0, int(base.size()) / 2);
    }
    T single_get(int left, int right) {
        T ans = neutral;
        left += base.size() >> 1;
        right += base.size() >> 1;
        while (left < right) {
            if (left % 2) ans = comp(ans, base[left++]);
            left >>= 1;
            if (right % 2) ans = comp(ans, base[--right]);
            right >>= 1;
        }
        return ans;
    }
    T public_get(int left, int right) {
        return _public_get(left, right, 1, 0, int(base.size()) / 2);
    }
    T get(int left, int right) {
        return comp(single_get(left, right), public_get(left, right));
    }
};


// Дерево полуинтервалов.
// В конструктор подается:
//     1. Вектор элементов того же типа, что и дерево.
//     2. Функция по которой строится дерево.
//     3. Нейтральный элемент.
// Например:
// unsigned int sum(const unsigned int &a, const unsigned int &b) { return a + b; }
// tree<unsigned int> t(*new vector<unsigned int>(N, 0), sum, 0);
// Изменение элемента: single_update(позиция изменяемого элемента, новое значение)
// Массовая операция изменения элементов: public_update(left, right, value)
// Запрос: get(левая граница, правая граница(не включительно))
