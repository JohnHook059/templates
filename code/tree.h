struct tree {
    int value;
    vector<tree*> base;
    tree* father;

    tree(int value = 0) : value(value) {}
    void add(tree &other) {
        other.father = this;
        base.push_back(&other);
    }
    void add(int value) {
        base.push_back(new tree(value));
        base.back()->father = this;
    }
};
