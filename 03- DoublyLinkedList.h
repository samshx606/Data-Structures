#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <bits/stdc++.h>
using namespace std;
template<typename T>
class DoublyLinkedList{
private:
    struct node{
        T val{};
        node* next{};
        node* prev{};
        node(T val):val(val){};
        ~node(){
            cout<<"Destroy value: "<<val<<" at address "<<this<<"\n";
        }
    };
    node* head{};
    node* tail{};
    int length{};
public:
    DoublyLinkedList() {
    }
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList &operator=(const DoublyLinkedList &another) = delete;
    void print(){
        for(node *cur = head ; cur ; cur = cur->next){
            cout<<cur->val<<" ";
        }
        cout<<"\n";
    }
    void link(node *first , node *second){
        if(first)
            first->next = second;
        if (second)
            second->prev = first;
    }
    void insert_front(T val){
        node* item = new node(val);
        if(!head){
            head = tail = item;
        }else{
            link(item , head);
            head = item;
        }
        length++;
    }
    void insert_end(T val){
        node *item = new node(val);
        if(!head){
            head = tail = item;
        }else{
            link(tail,item);
            tail = item;
        }
        length++;
    }
    void insert_between(node* before , node* after , T val){
        assert(before && after);
        node* item = new node(val);
        link(before,item);
        link(item,after);
        length++;
    }
    void insert_sorted(T val){
        if(!length || head->val>=val){
            insert_front(val);
        }else if(tail->val<=val){
            insert_end(val);
        }else{
            for (node* cur=head ; cur ; cur=cur->next){
                if(cur->val>=val){
                    insert_between(cur->prev,cur,val);
                    break;
                }
            }
        }
        verify_data_integrity();
    }
    void delete_node(node* Node){
        assert(Node);
        delete Node;
        length--;
    }
    void delete_front(){
        if(!head)
            return;
        if(head == tail){
            delete_node(head);
            head = tail = nullptr;
        }else{
            head = head->next;
            delete_node(head->prev);
            head->prev = nullptr;
        }
    }
    void delete_end(){
        if(!head)
            return;
        if(head == tail){
            delete_front();
        }else{
            tail = tail->prev;
            delete_node(tail->next);
            tail->next = nullptr;
        }
    }
    node* delete_and_link(node* Node){
        assert(Node);
        node* ret = Node->prev;
        link(Node->prev , Node->next);
        delete_node(Node);
        return ret;
    }
    void delete_with_key(T val){
        if(!head)
            return;
        if(head->val == val){
            delete_front();
        }else{
            for (node* cur=head ; cur ; cur=cur->next){
                if(cur->val == val){
                    cur = delete_and_link(cur);
                    if(!cur->next)
                        tail = cur;
                    break;
                }
            }
        }
    }
    void delete_all_node_with_key(T val){
        if(!head)
            return;
        while (head->val == val){
            delete_front();
            if(!head)
                return;
        }
        for (node* cur=head ; cur ; cur=cur->next){
            if(cur->val == val){
                cur = delete_and_link(cur);
                if(!cur->next){
                    tail = cur;
                }
            }
        }

    }
    void delete_even_pos(){
        if(length<=1)
            return;
        for (node* cur=head ; cur ; cur=cur->next){
            if(cur->next){
                cur = delete_and_link(cur->next);
                if(!cur->next)
                    tail = cur;
            }
        }
    }
    void delete_odd_pos(){
        delete_front();
        delete_even_pos();
    }
    bool is_palindrome(){
        int len = length/2;
        for (node *l=head , *r=tail ; len ; l=l->next , r=r->prev , len--){
            if(l->val != r->val)
                return false;
        }
        return true;
    }
    void verify_data_integrity(){
        if(length == 0){
            assert(head == nullptr);
            assert(tail == nullptr);
        }else{
            assert(head != nullptr);
            assert(tail != nullptr);
            assert(!tail->next);
            assert(!head->prev);
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
        len = 0;
        for (node* cur = tail ; cur ; cur = cur->prev , len++)
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
    ~DoublyLinkedList(){
        while (head)
            delete_front();
    }
};
#endif //DOUBLYLINKEDLIST_H
