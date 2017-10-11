#include<cstdlib>
#include<iostream>
using namespace std;


// merge and just compare by value x
void Merge_x(int left, int middle, int right, int *arr_X, int *arr_Y){

    int temp[2][right-left+1];
    // for merge easily
    int i=left,j=middle+1;
    int rear=0;
    // compare and assign value to temp
    while(i<=middle && j<=right){
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
    while(i<=middle){
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
    int middle;
    if(left < right){
        middle = (left+right)/2;
        // split the data
        Merge_sort_x(left,middle,arr_X,arr_Y);
        Merge_sort_x(middle+1,right,arr_X,arr_Y);
        // do merge
        Merge_x(left,middle,right,arr_X,arr_Y);
    }
}

// merge and compare by value y and do ranking calculate
void Merge_y(int left, int middle, int right, int *arr_X, int *arr_Y, int *x, int *y, int *r){

    int temp[2][right-left+1];
    // for merge easily
    int i=left,j=middle+1;
    int rear=0;
    // compare and assign value to temp
    while(i<=middle && j<=right){
        if(arr_Y[i] > arr_Y[j]){
            temp[0][rear] = arr_X[j];
            temp[1][rear] = arr_Y[j];
            ++rear;
            ++j;
        }
        else if(arr_Y[i] < arr_Y[j]){
            temp[0][rear] = arr_X[i];
            temp[1][rear] = arr_Y[i];
            ++rear;
            ++i;
        }
        // same value of y => compare x
        else{
            if(arr_X[i] > arr_X[j]){
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
    while(i<=middle){
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

void Merge_sort_y(int left, int right, int *arr_X, int *arr_Y, int *x, int *y, int *r){
    int middle;
    if(left < right){
        middle = (left+right)/2;
        // split the data
        Merge_sort_y(left,middle,arr_X,arr_Y,x,y,r);
        Merge_sort_y(middle+1,right,arr_X,arr_Y,x,y,r);
        // do merge
        Merge_y(left,middle,right,arr_X,arr_Y,x,y,r);
    }
}

int main(){
    int n;
    while(cin>>n){

        int x[n],y[n],tmp_x[n],tmp_y[n],used[n],r[n];

        for(int i=0 ; i<n ; i++)
            cin>>x[i]>>y[i];

        // sort by value x
        Merge_sort_x(0,n-1,x,y);

        cout<<"merge by x:"<<endl;
        for(int i=0 ; i<n ; i++)
            cout<<x[i]<<" "<<y[i]<<endl;
        // save now to temp
        for(int i=0 ; i<n ; i++){
            tmp_x[i] = x[i];
            tmp_y[i] = y[i];
        }
        // sort by value y and do rank calculate
        Merge_sort_y(0,n-1,x,y,tmp_x,tmp_y,r);
        cout<<"merge by y:"<<endl;
        for(int i=0 ; i<n ; i++)
            cout<<x[i]<<" "<<y[i]<<endl;

    }
    return 0;
}
