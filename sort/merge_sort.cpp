#include<cstdlib>
#include<iostream>
using namespace std;


void merging(int *a, int left, int middle, int right){
    int temp[right-left+1],rear=0;
    int i=left,j=middle+1;
    // compare and assign value to temp
    while(i<=middle && j<=right){
        if(a[i]>a[j]){
            temp[rear] = a[j];
            ++j;
        }
        else{
            temp[rear] = a[i];
            ++i;
        }
        ++rear;
    }
    // for remaining value
    while(i<=middle){
        temp[rear] = a[i];
        ++i;
        ++rear;
    }
    while(j<=right){
        temp[rear] = a[j];
        ++j;
        ++rear;
    }
    // assign value back to original array :a
    for(int i=left ; i<=right ; i++){
        a[i] = temp[i-left];
    }
}


void merge_sort(int *a, int left, int right){
    int middle;
    if(left < right){
        middle = (left+right)/2;
        // split the data
        merge_sort(a,left,middle);
        merge_sort(a,middle+1,right);
        // do merge
        merging(a,left,middle,right);
    }
}

int main(){
    // define an unsorted array
    int a[10] = {1,8,6,5,4,3,2,9,10,7};

    cout<<"< Merge sort >"<<endl;
    cout<<"Unsorted: ";
    for(int i=0 ; i<10 ; i++){
        cout<<a[i]<<" ";
    }

    merge_sort(a,0,9);

    cout<<endl<<"Sorted: ";
    for(int i=0 ; i<10 ; i++){
        cout<<a[i]<<" ";
    }

    return 0;
}
