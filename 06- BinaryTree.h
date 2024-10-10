#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <bits/stdc++.h>
using namespace std;
template<typename T>
class BinaryTree{
private:
    T val{};
    BinaryTree* left{};
    BinaryTree* right{};
public:
    BinaryTree(T val):val(val){}
    BinaryTree(deque<T>&inorder , deque<T>&preorder , int l=0 , int r=-1){
        if(r==-1) r = inorder.size()-1;
        val = preorder.front();
        preorder.pop_front();
        for(int i=l ; i<=r ; i++){
            if(inorder[i] == val){
                if(l<i)left = new BinaryTree(inorder,preorder,l,i-1);
                if(i<r)right =new BinaryTree(inorder,preorder,i+1,r);
            }
        }
    }
    // full binary tree only
    BinaryTree(queue<pair<T,bool>>&preorder){
        val = preorder.front().first;
        bool is_leaf = preorder.front().second;
        preorder.pop();
        if(!is_leaf){
            left = new BinaryTree(preorder);
            right= new BinaryTree(preorder);
        }
    }
    void emplace(vector<T> values, vector<char> direction) {
        assert(values.size() == direction.size());
        BinaryTree* cur = this;
        for (int i = 0; i < values.size(); ++i) {
            if (direction[i] == 'L') {
                if (!cur->left)
                    cur->left = new BinaryTree(values[i]);
                else
                    assert(cur->left->val == values[i]);
                cur = cur->left;
            } else {
                if (!cur->right)
                    cur->right = new BinaryTree(values[i]);
                else
                    assert(cur->right->val == values[i]);
                cur = cur->right;
            }
        }
    }
    void print_inorder(){
        if(left)left->print_inorder();
        cout<<val<<" ";
        if(right)right->print_inorder();
    }
    void print_preorder(){
        cout<<val<<" ";
        if(left)left->print_inorder();
        if(right)right->print_inorder();
    }
    void print_postorder(){
        if(left)left->print_inorder();
        if(right)right->print_inorder();
        cout<<val<<" ";
    }
    T get_max(){
        T ans = val;
        if(left)ans = max(ans,left->get_max());
        if(right)ans = max(ans,right->get_max());
        return ans;
    }
    int get_height(){
        int ans = 0;
        if(left)ans = 1 + left->get_height();
        if(right)ans = max(ans,1+right->get_height());
        return ans;
    }
    int count_nodes(){
        int ans = 1;
        if(left) ans += left->count_nodes();
        if(right)ans += right->count_nodes();
        return ans;
    }
    int count_leaf(){
        int ans = !left && !right;
        if(left) ans += left->count_leaf();
        if(right)ans += right->count_leaf();
        return ans;
    }
    bool is_exist(const T &val){
        bool ans = this->val == val;
        if(left && !ans)ans=left->is_exist(val);
        if(right && !ans)ans=right->is_exist(val);
        return ans;
    }
    bool is_perfect(int h = -1) {
        if (h == -1)
            h = get_height();
        if (!left && !right)
            return h == 0;

        if (!left && right || left && !right)
            return false;
        return left->is_perfect(h - 1) && right->is_perfect(h - 1);
    }
    bool is_perfect_fomula() {
        int h = get_height();
        int n = count_nodes();
        return pow(2, h + 1) - 1 == n;
    }
    void level_order_traversal() {
        queue<BinaryTree*> nodes_queue;
        nodes_queue.push(this);
        int level = 0;
        while (!nodes_queue.empty()) {
            int sz = nodes_queue.size();
            cout<<"Level "<<level<<": ";
            while(sz--) {
                BinaryTree* cur = nodes_queue.front();
                nodes_queue.pop();

                cout << cur->val << " ";
                if (cur->left)
                    nodes_queue.push(cur->left);
                if (cur->right)
                    nodes_queue.push(cur->right);
            }
            level++;
            cout << "\n";
        }
    }
    void print_nodes_level(int lvl) {
        if (lvl){
            if(left)left->print_nodes_level(lvl-1);
            if(right)right->print_nodes_level(lvl-1);
        }else{
            cout<<val<<" ";
        }
    }
    void level_order_traversal_recursive() {	// O(n^2)
        int h = get_height();
        for (int lvl = 0; lvl <= h; lvl++){
            print_nodes_level(lvl);
            cout<<"\n";
        }
    }
    void level_order_traversal_spiral() {
        deque<BinaryTree*> nodes_queue;
        nodes_queue.push_back(this);
        int lvl = 0;
        bool triger = true;
        while (!nodes_queue.empty()) {
            int sz = nodes_queue.size();
            cout << "Level " << lvl << ": ";
            while (sz--) {
                BinaryTree*cur;
                if (triger) {
                    cur = nodes_queue.front();
                    nodes_queue.pop_front();
                    if (cur->left)nodes_queue.push_back(cur->left);
                    if (cur->right)nodes_queue.push_back(cur->right);
                } else{
                    cur = nodes_queue.back();
                    nodes_queue.pop_back();
                    if (cur->right)nodes_queue.push_front(cur->right);
                    if (cur->left)nodes_queue.push_front(cur->left);
                }
                cout << cur->val << " ";
            }
            triger = !triger;
            lvl++;
            cout << "\n";
        }
    }
    void build_preorder(queue<pair<int, bool> > &preorder_queue) {
        preorder_queue.push(make_pair(val, !left && !right));

        if (left)left->build_preorder(preorder_queue);
        if (right)right->build_preorder(preorder_queue);
    }
    string parenthesize() {
        string ans = "(" + toStr(val);

        if (left)ans += left->parenthesize();
        else ans += "()";

        if (right)ans += right->parenthesize();
        else ans += "()";

        ans += ")";
        return ans;
    }
    string parenthesize_canonical() {
        string repr = "(" + toStr(val);
        vector<string> v;

        if (left)v.push_back(left->parenthesize_canonical());
        else v.push_back("()");

        if (right)v.push_back(right->parenthesize_canonical());
        else v.push_back("()");

        sort(v.begin(), v.end());
        for (int i = 0; i < v.size(); ++i)
            repr += v[i];
        repr += ")";
        return repr;
    }
    bool is_mirror(BinaryTree *l , BinaryTree *r){
        if(!l && !r)
            return true;
        if(!l || !r || l->val != r->val)
            return false;
        return is_mirror(l->left,r->right) && is_mirror(l->right,r->left);
    }
    bool is_symmetric(){
        return is_mirror(left,right);
    }
    bool is_flip_equiv(BinaryTree *other){
        return parenthesize_canonical() == other->parenthesize_canonical();
    }
};
#endif //BINARYTREE_H
