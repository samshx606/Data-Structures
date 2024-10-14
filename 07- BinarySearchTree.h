#ifndef BST_H
#define BST_H
#include <bits/stdc++.h>
using namespace std;
template<typename T>
class BST{
private:
    T val{};
    BST* left{};
    BST* right{};
    bool find_chain(vector<BST*> &ancestors, int target) {
        ancestors.push_back(this);
        if (target == val)
            return true;
        if (target < val)
            return left && left->find_chain(ancestors, target);

        return right && right->find_chain(ancestors, target);
    }
public:
    BST(T val , BST* left=nullptr , BST* right=nullptr):
        val(val),left(left),right(right){}
    void print_inorder(){
        if (left)
            left->print_inorder();
        cout<<val<<" ";
        if (right)
            right->print_inorder();
    }
    void insert(T data){
        if(data < val){
            if(!left)
                left = new BST(data);
            else
                left->insert(data);
        }else if(data > val){
            if(!right)
                right = new BST(data);
            else
                right->insert(data);
        }
    }
    bool search(T data){
        if(data == val)
            return true;
        if(data < val)
            return left && left->search(data);
        if(data>val)
            return right && right->search(data);
    }
    bool iterative_search(T data){
        for (BST *cur = this ;cur;){
            if(data == cur->val)
                return true;
            if(data < cur->val)
                cur = cur->left;
            if(data > cur->val)
                cur = cur->right;
        }
        return false;
    }
    bool is_BST(T mn=INT_MIN , T mx=INT_MAX){
        bool status = val>mn && val<mx;
        if(!status)
            return false;
        bool left_BST = !left || left->is_BST(mn,val);
        if(!left_BST)
            return false;
        return !right || right->is_BST(val,mx);
    }
    void get_inorder(vector<int>& values) {
        if (left)
            left->get_inorder(values);
        values.push_back(val);
        if (right)
            right->get_inorder(values);
    }
    bool is_BST2() {
        vector<int> values;
        get_inorder(values);
        for (int i = 1; i < values.size(); ++i) {
            if (values[i] < values[i - 1])
                return false;
        }
        return true;
    }
    BST *build_balanced_BST(vector<int>&v , int l=0 , int r=-2){
        if(r==-2)
            r = (int)v.size()-1;
        if(r<l)
            return nullptr;
        int mid = l +(r-l)/2;
        BST *left = build_balanced_BST(v , l , mid-1);
        BST *right= build_balanced_BST(v , mid+1 , r);
        return new BST(v[mid] , left , right);
    }
    T kth_smallest(int &k){
        if(k == 0)
            return -1;
        if(left){
            int res = left->kth_smallest(k);
            if(k==0)
                return res;
        }
        k--;
        if(k==0)
            return val;
        if(right)
            return right->kth_smallest(k);
        return -1;
    }
    int lca(int x, int y) { //lowest common ancestor
        if (x < val && y < val)
            return left->lca(x, y);

        if (x > val && y > val)
            return right->lca(x, y);

        return val;
    }
    int min_val(){
        BST *cur = this;
        while (cur->left)cur = cur->left;
        return cur->val;
    }
    BST* get_next(vector<BST*> &ancestors) {
        if (ancestors.size() == 0)
            return nullptr;
        BST* node = ancestors.back();
        ancestors.pop_back();
        return node;
    }
    int successor(int target) {
        vector<BST*> ancestors;
        if (!find_chain(ancestors, target))
            return -1;
        BST* child = get_next(ancestors);

        if (child->right)
            return child->right->min_val();

        BST* parent = get_next(ancestors);

        while (parent && parent->right == child)
            child = parent, parent = get_next(ancestors);

        if (parent)
            return parent->val;
        return -1;
    }
};
#endif //BST_H
