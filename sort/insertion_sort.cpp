#include<cstdlib>
#include<iostream>
using namespace std;

#define swap(x,temp,y) temp=x;x=y;y=temp;

int temp;

void insertion_sort(int *a, int n){
    for(int i=1 ; i<n ; ++i){
        int target = a[i];
        int j;
        for(j=i ; j>0 && target<a[j-1] ; --j){
            a[j] = a[j-1]; //move to right
        }
        a[j] = target;
    }
}

int main(){
    // define an unsorted array
    int a[10] = {1,8,6,5,4,3,2,9,10,7};

    cout<<"< Insertion sort >"<<endl;
    cout<<"Unsorted: ";
    for(int i=0 ; i<10 ; i++){
        cout<<a[i]<<" ";
    }

    insertion_sort(a,10);

    cout<<endl<<"Sorted: ";
    for(int i=0 ; i<10 ; i++){
        cout<<a[i]<<" ";
    }

    return 0;
}
