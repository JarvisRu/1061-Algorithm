#include<cstdlib>
#include<iostream>
using namespace std;


// merge and just compare by value x
void Merge_x(int left, int midd, int right, int *arr_X, int *arr_Y){

    // final result
    int temp[2][right-left+1];

    // for merge easily
    int i=left,j=midd+1;
    int rear=0;
    // compare and assign value to temp
    while(i<=midd && j<=right){
        if(arr_X[i] > arr_X[j]){
            temp[0][rear] = arr_X[j];
            temp[1][rear] = arr_Y[j];
            ++rear;
            ++j;
        }
        else if(arr_X[i] < arr_X[j]){
            temp[0][rear] = arr_X[i];
            temp[1][rear] = arr_Y[i];
            ++rear;
            ++i;
        }
        // same value of x => compare y
        else{
            if(arr_Y[i] > arr_Y[j]){
                temp[0][rear] = arr_X[j];
                temp[1][rear] = arr_Y[j];
                ++rear;
                ++j;
            }
            else{
                temp[0][rear] = arr_X[i];
                temp[1][rear] = arr_Y[i];
                ++rear;
                ++i;
            }
        }
    }
    // for remaining value
    while(i<=midd){
        temp[0][rear] = arr_X[i];
        temp[1][rear] = arr_Y[i];
        ++rear;
        ++i;
    }
    while(j<=right){
        temp[0][rear] = arr_X[j];
        temp[1][rear] = arr_Y[j];
        ++rear;
        ++j;
    }

    for(int i=left ; i<=right ; i++){
        arr_X[i] = temp[0][i-left];
        arr_Y[i] = temp[1][i-left];
    }

}

void Merge_sort_x(int left, int right, int *arr_X, int *arr_Y){
    int midd;
    if(left < right){
        midd = (left+right)/2;
        // split the data
        Merge_sort_x(left,midd,arr_X,arr_Y);
        Merge_sort_x(midd+1,right,arr_X,arr_Y);
        // do merge
        Merge_x(left,midd,right,arr_X,arr_Y);
    }
}



int main(){
    int n;
    while(cin>>n){

        int x[n],y[n],temp[2][n],used[n],r[n];

        for(int i=0 ; i<n ; i++)
            cin>>x[i]>>y[i];

        Merge_sort_x(0,n-1,x,y);

        for(int i=0 ; i<n ; i++)
            cout<<x[i]<<" "<<y[i]<<endl;

    }
    return 0;
}
