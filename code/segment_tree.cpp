#include <vector>

template <typename T>
struct tree {
    std::vector<T> base;
    T (*comp)(const T &, const T &);
    T neutral;
    tree(const std::vector<T> &v, T (*comp)(const T &, const T &), T neutral) : comp(comp), neutral(neutral) {
        int st = 1;
        while (st < v.size())
            st <<= 1;
        base.resize(st << 1);
        for (int i = st; i < st + v.size(); ++i)
            base[i] = v[i - st];
        for (int i = st + int(v.size()); i < st << 1; ++i)
            base[i] = neutral;
        for (int i = st - 1; i > 0; --i)
            base[i] = comp(base[i << 1], base[(i << 1) + 1]);
    }
    void update(int pos, T new_value) {
        pos += base.size() >> 1;
        base[pos] = new_value;
        while (pos > 1) {
            pos >>= 1;
            base[pos] = comp(base[pos << 1], base[(pos << 1) + 1]);
        }
    }
    T get(int l, int r) {
        T ans = neutral;
        l += base.size() >> 1;
        r += base.size() >> 1;
        while (l < r) {
            if (l % 2) ans = comp(ans, base[l++]);
            l /= 2;
            if (r % 2) ans = comp(ans, base[--r]);
            r /= 2;
        }
        return ans;
    }
};

// Authors = JohnHook
// Дерево полуинтервалов.
// В конструктор подается:
//     1. Вектор элементов того же типа, что и дерево.
//     2. Функция по которой строится дерево.
//     3. Нейтральный элемент.
// Например: tree<int> t(array, sum, 0);
// Изменение элемента: update(позиция изменяемого элемента, новое значение)
// Запрос: get(левая граница, правая граница(не включительно))
