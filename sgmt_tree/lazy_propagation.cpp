
/*
 
lazy segment tree propagation

    update the node when u visit it 

    once you update, propagate the update downwards 

Traverse in seg tree, 

    update prev remaining updates
    
    check if the node completely overlaps with (L-R)
        update the node 
        lazy prop
    
    check if the node partially overlaps
         left, right, node = left + right

    no overlap 
        return 




*/


#include<bits/stdc++.h>

using namespace std;

class sgTree{
    vector<int>sgt,lazy;
    public:
    
    
    //declare sgmt tree with size 4*n + 1 
    sgTree(int n){
        sgt.resize(4*n + 1);    
        lazy.resize(4*n + 1);
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
        sgt[ind] = sgt[2*ind + 1] + sgt[2*ind + 2];

    }

    int query(int ind, int low, int high, int ql, int qr){
    
       //update the prev propagation   
       if( lazy[ind] != 0){
        sgt[ind] += (high - low + 1)*lazy[ind];

        if( left != right) {
            lazy[2*ind + 1] += lazy[ind];
            lazy[2*ind + 2] += lazy[ind];
        }

        lazy[ind] = 0;
       }

        // no overlap
        if( high < ql || low > qr){
            return 0;
        }

        // full overlap
        if( ql <= low && high <= qr) return sgt[ind];

        // partial overlap
        int mid = ( low + high)/2;
        
        int left = query( 2*ind + 1, low, mid, ql, qr);
        int right = query( 2*ind + 2, mid + 1, high, ql, qr);
        return left + right;
    }

    void update(int ind, int low, int high, int update_low, int update_high, int val){

        //update the prev propagation   
       if( lazy[ind] != 0){
        sgt[ind] += (high - low + 1)*lazy[ind];

        if( left != right) {
            lazy[2*ind + 1] += lazy[ind];
            lazy[2*ind + 2] += lazy[ind];
        }

        lazy[ind] = 0;
       }

        if(high < update_low || low > update_high) return;

        if( update_low <= low && high <= update_high){
            sgt[ind] += (high - low + 1)*val;
            if( low != high){
                lazy[2*ind + 1] += val;
                lazy[2*ind + 2] += val;
            }
            return;
        }
        
        int mid = (low + high)/2;

        update(2*ind + 1, low, mid, update_low, update_high, val);
        update(2*ind + 2, mid + 1, high, update_low, update_high, val);
        sgt[ind] = sgt[2*ind + 1] + sgt[2*ind + 2];
    }
};

int main(){
    int arr[6]  = {1,2,3,4,5,6};
    sgTree sg(6);
    sg.build(0, 0, 5, arr);
    sg.update(0, 0, 5, 0, 2, 1);
    
    cout<<sg.query(0,0, 5, 0,1);
    
}
