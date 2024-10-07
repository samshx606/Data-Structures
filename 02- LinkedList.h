#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <bits/stdc++.h>
using namespace std;
template<typename T>
class LinkedList{
private:
    struct node{
        T val{};
        node* next{};
        node(T val):val(val){};
        ~node(){
            cout<<"Destroy value: "<<val<<" at address "<<this<<"\n";
        }
    };
    node* head{};
    node* tail{};
    int length{};
public:
    LinkedList() {
    }
    LinkedList(const LinkedList&) = delete;
    LinkedList &operator=(const LinkedList &another) = delete;
    void print(){
        for(node *cur = head ; cur ; cur = cur->next){
            cout<<cur->val<<" ";
        }
        cout<<"\n";
    }
    void insert_front(T val){
        node* item = new node(val);
        if(!head){
            head = tail = item;
        }else{
            item->next = head;
            head = item;
        }
        length++;
        verify_data_integrity();
    }
    void insert_end(T val){
        node* item = new node(val);;
        if(!head){
            head = tail = item;
        }else{
            tail->next = item;
            tail = item;
        }
        length++;
        verify_data_integrity();
    }
    void insert_next_node(node* Node , T val){
        assert(Node);
        node *item = new node(val);
        item->next = Node->next;
        Node->next = item;
        length++;
    }
    void insert_sorted(T val){
        if(!length || val<head->val){
            insert_front(val);
        }else if(val>=tail->val){
            insert_end(val);
        }else{
            for (node *cur=head , *prv=nullptr ; cur ; prv=cur,cur=cur->next){
                if(val <= cur->val){
                    insert_next_node(prv , val);
                    break;
                }
            }
        }
    }
    void delete_front(){
        if(!head)return;
        if(head == tail){
            delete_node(head);
            head = tail = nullptr;
        }else{
            node* item = head;
            head = head->next;
            delete_node(item);
        }
        verify_data_integrity();
    }
    void delete_end(){
        if(!head)
            return;
        if(head == tail){
            delete_front();
        }else{
            node* cur = head;
            while (cur->next->next){
                cur = cur->next;
            }
            delete_node(tail);
            cur->next = nullptr;
            tail = cur;
        }
        verify_data_integrity();
    }
    void delete_with_key(T val){
        if(!length)
            return;
        if(head->val == val){
            delete_front();
        }else{
            for (node *cur=head , *prv=nullptr; cur ; prv=cur , cur=cur->next){
                if(cur->val == val){
                    delete_next_node(prv);
                    return;
                }
            }
        }
        verify_data_integrity();
    }
    void delete_node(node* Node){
        assert(Node);
        delete Node;
        --length;
    }
    void delete_next_node(node* Node){
        assert(Node);
        node* to_delete = Node->next;
        bool is_tail = to_delete == tail;
        Node->next = to_delete->next;
        delete_node(to_delete);
        if(is_tail)
            tail = Node;
    }
    void delete_even_pos(){
        if(length<=1)
            return;
        for (node *cur=head->next , *prv=head ; cur ; prv = prv->next , cur = prv->next){
            delete_next_node(prv);
            if(!prv->next)
                break;
        }
    }
    node* get_nth(int n){ // base 0
        int cnt = 0;
        for (node *cur = head ; cur ; cur = cur->next){
            if(cnt == n)
                return cur;
            cnt++;
        }
        return nullptr;
    }
    node* get_nth_from_back(int n){ // base 1
        n = length-n;
        return get_nth(n);
    }
    int search(T val){
        int idx = 0;
        for (node *cur = head ; cur ; cur = cur->next){
            if(cur->val == val)
                return idx;
            idx++;
        }
        return -1;
    }
    int improved_search(T val){
        int idx = 0;
        for (node *cur=head , *prv=nullptr; cur ; prv=cur , cur=cur->next){
            if(cur->val == val){
                if(!prv)
                    return idx;
                swap(prv->val , cur->val);
                return idx;
            }
            idx++;
        }
        return -1;
    }
    bool is_same(const LinkedList &l){
        if(length != l.length)
            return false;
        node* other = l.head;
        for (node *cur1=head; cur1 ; cur1=cur1->next){
            if(cur1->val != other->val)
                return false;
            other = other->next;
        }
        return true;
    }
    void swap_pairs(){
        if(length<2)
            return;
        for(node* cur=head ; cur ; cur=cur->next){
            if(cur->next){
                swap(cur->val , cur->next->val);
                cur = cur->next;
            }
        }
    }
    void reverse(){
        node *cur=head , *prv=nullptr;
        while (cur){
            node *item = cur->next;
            cur->next = prv;
            prv = cur;
            cur = item;
        }
        swap(head,tail);
    }
    void verify_data_integrity(){
        if(length == 0){
            assert(head == nullptr);
            assert(tail == nullptr);
        }else{
            assert(head != nullptr);
            assert(tail != nullptr);
            assert(!tail->next);
            if(length == 1){
                assert(head == tail);
            }else{
                assert(head != tail);
            }
        }
        int len = 0;
        for (node* cur = head ; cur ; cur = cur->next , len++)
            assert(len<2e5);
        assert(len == length);
    }
    string debug_to_string(){\
        if(!head)
            return "";
        ostringstream oss;
        for (node *cur=head ; cur ; cur=cur->next){
            oss << cur->val;
            if(cur->next)
                oss << " ";
        }
        return oss.str();
    }
    ~LinkedList(){
        while (head)
            delete_front();
    }
};
#endif //LINKEDLIST_H
