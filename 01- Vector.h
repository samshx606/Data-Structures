#ifndef VECTOR_H
#define VECTOR_H
#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Vector{
private:
    T* array{};
    int size{};
    int capacity = 10;
    void extend_capacity(){
        capacity*=2;
        T *temp = new T[capacity]{};
        for (int i=0 ; i<size ; i++){
            temp[i] = array[i];
        }
        swap(array , temp);
        delete[] temp;
    }
public:
    Vector(){
        array = new T[capacity];
    }
    Vector(int size):size(size)
                    ,capacity(size){
        assert(size>=0);
        array = new T[capacity]{};
    }
    T get_idx(int idx){
        assert(idx>=0 && idx<=size);
        return array[idx];
    }
    int get_size(){
        return size;
    }
    void set(int idx , T val){
        assert(idx>=0 && idx<=size);
        array[idx] = val;
    }
    void print(){
        for(int i=0 ; i<size ; i++){
            cout<<array[i]<<" ";
        }
        cout<<"\n";
    }
    int find(T val){
        for(int i=0 ; i<size ; i++){
            if(array[i] == val)
                return i;
        }
        return -1;
    }
    int find_transposition(T val){
        int idx = find(val);
        if(idx>0){
            swap(array[idx],array[idx-1]);
            return idx-1;
        }
        return idx;
    }
    void push_front(T val){
        if(capacity == size)extend_capacity();
        for (int i=size ; i>0 ; i--){
            array[i] = array[i-1];
        }
        array[0] = val;
        size++;
    }
    void push_back(T val){
        if(capacity == size)extend_capacity();
        array[size++] = val;
    }
    void insert(int idx , T val){
        if(size == capacity)
            extend_capacity();
        for (int i=size ; i>idx ; i--){
            array[i] = array[i-1];
        }
        array[idx] = val;
        size++;
    }
    void right_rotate(){
        T last = array[size-1];
        for (int i= size-1 ; i>0 ; i--){
            array[i] = array[i-1];
        }
        array[0] = last;
    }
    void right_rotate(int times){
        times %= size;
        T *temp = new T[size];
        for(int i=0 ; i<size-times ; i++){
            temp[i+times] = array[i];
        }
        for(int i=size-times ; i<size ; i++){
            temp[i-size+times] = array[i];
        }
        swap(array,temp);
        delete[] temp;
    }
    void left_rotate(){
        T first = array[0];
        for (int i= 1 ; i<size ; i++){
            array[i-1] = array[i];
        }
        array[size-1] = first;
    }
    T pop(int idx){
        T val = array[idx];
        size--;
        for (int i= idx ; i<size ; i++){
            array[i] = array[i+1];
        }
        return val;
    }
    ~Vector(){
        delete[] array;
        array = nullptr;
    }
};
#endif //VECTOR_H
