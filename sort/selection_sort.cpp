#include<cstdlib>
#include<iostream>
using namespace std;

#define swap(x,temp,y) temp=x;x=y;y=temp;

int temp;

// find the min in unsorted part and put it to the left as sorted part
void selection_sort(int *a, int n){
    for(int i=0 ; i<n ; ++i){
        int min_index = i;
        for(int j=i+1 ; j<n ; ++j){
            if(a[min_index] > a[j]){
                min_index = j;
            }
        }
        swap(a[i],temp,a[min_index]);
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

    selection_sort(a,10);

    cout<<endl<<"Sorted: ";
    for(int i=0 ; i<10 ; i++){
        cout<<a[i]<<" ";
    }

    return 0;
}
