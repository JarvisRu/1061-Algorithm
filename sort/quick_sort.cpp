#include<cstdlib>
#include<iostream>
using namespace std;

#define swap(x,temp,y) temp=x;x=y;y=temp;

int temp;


void quick_sort(int *a, int left, int right){
    if(left < right){
        int pivot = a[(left+right)/2];
        swap(a[right],temp,a[(left+right)/2]) // swap to the rightmost

        // trace by j / point to smaller by i
        int i=left,j=left;
        for( ; j < right ; ++j){
            if(a[j] < pivot){
                swap(a[i],temp,a[j]);
                ++i;
            }
        }
        if(i < right) swap(a[i],temp,a[right]);

        quick_sort(a,left,i);
        quick_sort(a,i+1,right);

    }
}

int main(){
    // define an unsorted array
    int a[10] = {1,8,6,5,4,3,2,9,10,7};

    cout<<"< Selection sort >"<<endl;
    cout<<"Unsorted: ";
    for(int i=0 ; i<10 ; i++){
        cout<<a[i]<<" ";
    }

    quick_sort(a,0,9);

    cout<<endl<<"Sorted: ";
    for(int i=0 ; i<10 ; i++){
        cout<<a[i]<<" ";
    }

    return 0;
}
