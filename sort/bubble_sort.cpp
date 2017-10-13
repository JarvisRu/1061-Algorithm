#include<cstdlib>
#include<iostream>
using namespace std;

#define swap(x,temp,y) temp=x;x=y;y=temp;

int temp;

void bubble_sort(int *a, int n){
    for(int i=0 ; i<n-1 ; ++i){
        for(int j=0 ; j<n-i-1 ; ++j){
            if(a[j] > a[j+1]){
                swap(a[j],temp,a[j+1]);
            }
        }
    }
}

void optimal_bubble_sort(int *a, int n){
    for(int i=0 ; i<n-1 ; ++i){
        bool sorted = true;
        for(int j=0 ; j<n-i-1 ; ++j){
            if(a[j]>a[j+1]){
               swap(a[j],temp,a[j+1]);
               sorted = false;
            }
        }
        if(sorted)  break;
    }

}


int main(){
    // define an unsorted array
    int a[10] = {1,8,6,5,4,3,2,9,10,7};

    cout<<"< Bubble sort >"<<endl;
    cout<<"Unsorted: ";
    for(int i=0 ; i<10 ; i++){
        cout<<a[i]<<" ";
    }

    bubble_sort(a,10);

    cout<<endl<<"Sorted: ";
    for(int i=0 ; i<10 ; i++){
        cout<<a[i]<<" ";
    }

    return 0;
}
