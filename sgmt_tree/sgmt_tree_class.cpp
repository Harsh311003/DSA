#include<bits/stdc++.h>

using namespace std;

class sgTree{
    public:
    
    vector<int>sgt;
    
    //declare sgmt tree with size 4*n + 1 
    sgTree(int n){
        sgt.resize(4*n + 1);    
    }

    void build(int ind, int low, int high, int arr[]){
        if( low > high ) return;

        if( low == high) {
            sgt[ind] = arr[low];
            return;
        }

        int mid = (low + high)/2;
        build(2*ind + 1, low, mid, arr);
        build(2*ind + 2, mid + 1, high, arr);
        // some operation 
        sgt[ind] = min(sgt[2*ind + 1], sgt[2*ind + 2]);

    }

    int query(int ind, int low, int high, int ql, int qr){
        if( low > high) return INT_MAX;

        // no overlap
        if( high < ql || low > qr){
            return INT_MAX;
        }

        // full overlap
        if( ql <= low && high <= qr) return sgt[ind];

        // partial overlap
        int mid = ( low + high)/2;
        
        int left = query( 2*ind + 1, low, mid, ql, qr);
        int right = query( 2*ind + 2, mid + 1, high, ql, qr);
        return min(left, right);
    }

    void update(int ind, int low, int high, int q_ind, int val){
        if( low > high) return;

        if( low == high) {
            sgt[ind] = val;
            return;
        }

        int mid = (low + high)/2;


        if( q_ind <= mid) update(2*ind + 1, low, mid, q_ind, val);
        else update(2*ind + 2, mid + 1, high, q_ind, val);

        sgt[ind] = min(sgt[2*ind + 1], sgt[2*ind + 2]);

    }
};
