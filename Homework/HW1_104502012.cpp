#include<cstdlib>
#include<iostream>
using namespace std;


int n;

/*  For Step 1
    merge and just compare by value x */
void Merge_x(int left, int middle, int right, int *arr_X, int *arr_Y, int *order){

    int temp[3][right-left+1];
    // for merge easily
    int i=left,j=middle+1;
    int rear=0;
    // compare and assign value to temp
    while(i<=middle && j<=right){
        if(arr_X[i] > arr_X[j]){
            temp[0][rear] = arr_X[j];
            temp[1][rear] = arr_Y[j];
            temp[2][rear] = order[j];
            ++rear;
            ++j;
        }
        else if(arr_X[i] < arr_X[j]){
            temp[0][rear] = arr_X[i];
            temp[1][rear] = arr_Y[i];
            temp[2][rear] = order[i];
            ++rear;
            ++i;
        }
        // same value of x => compare y
        else{
            if(arr_Y[i] > arr_Y[j]){
                temp[0][rear] = arr_X[j];
                temp[1][rear] = arr_Y[j];
                temp[2][rear] = order[j];
                ++rear;
                ++j;
            }
            else{
                temp[0][rear] = arr_X[i];
                temp[1][rear] = arr_Y[i];
                temp[2][rear] = order[i];
                ++rear;
                ++i;
            }
        }
    }
    // for remaining value
    while(i<=middle){
        temp[0][rear] = arr_X[i];
        temp[1][rear] = arr_Y[i];
        temp[2][rear] = order[i];
        ++rear;
        ++i;
    }
    while(j<=right){
        temp[0][rear] = arr_X[j];
        temp[1][rear] = arr_Y[j];
        temp[2][rear] = order[j];
        ++rear;
        ++j;
    }

    for(int i=left ; i<=right ; i++){
        arr_X[i] = temp[0][i-left];
        arr_Y[i] = temp[1][i-left];
        order[i] = temp[2][i-left];
    }

}

void Merge_sort_x(int left, int right, int *arr_X, int *arr_Y, int *order){
    int middle;
    if(left < right){
        middle = (left+right)/2;
        // split the data
        Merge_sort_x(left,middle,arr_X,arr_Y,order);
        Merge_sort_x(middle+1,right,arr_X,arr_Y,order);
        // do merge
        Merge_x(left,middle,right,arr_X,arr_Y,order);
    }
}

/*  For Step 2
    merge and compare by value y and do ranking calculate */
void Merge_y(int left, int middle, int right, int *arr_X, int *arr_Y, int *order, int *r){

    int temp[3][right-left+1];
    // for merge easily
    int i=left,j=middle+1;
    int rear=0;

    // compare and assign value to temp
    while(i<=middle && j<=right){
        if(arr_Y[i] > arr_Y[j]){
            temp[0][rear] = arr_X[j];
            temp[1][rear] = arr_Y[j];
            temp[2][rear] = order[j];
            r[order[j]] += i-left;

            ++j;
        }
        else if(arr_Y[i] < arr_Y[j]){
            temp[0][rear] = arr_X[i];
            temp[1][rear] = arr_Y[i];
            temp[2][rear] = order[i];

            ++i;
        }
        // same value of y => compare x
        else{
            if(arr_X[i] > arr_X[j]){
                temp[0][rear] = arr_X[j];
                temp[1][rear] = arr_Y[j];
                temp[2][rear] = order[j];
                r[order[j]] += i-left;

                ++j;
            }
            else{
                temp[0][rear] = arr_X[i];
                temp[1][rear] = arr_Y[i];
                temp[2][rear] = order[i];

                ++i;
            }
        }

        ++rear;
    }
    // for remaining value
    while(i<=middle){
        temp[0][rear] = arr_X[i];
        temp[1][rear] = arr_Y[i];
        temp[2][rear] = order[i];

        ++rear;
        ++i;

    }
    while(j<=right){
        temp[0][rear] = arr_X[j];
        temp[1][rear] = arr_Y[j];
        temp[2][rear] = order[i];
        r[order[j]] += i-left;

        ++rear;
        ++j;
    }

    for(int i=left ; i<=right ; i++){
        arr_X[i] = temp[0][i-left];
        arr_Y[i] = temp[1][i-left];
        order[i] = temp[2][i-left];
    }

}

void Merge_sort_y(int left, int right, int *arr_X, int *arr_Y, int *order, int *r){
    int middle;
    if(left < right){
        middle = (left+right)/2;
        // split the data
        Merge_sort_y(left,middle,arr_X,arr_Y,order,r);
        Merge_sort_y(middle+1,right,arr_X,arr_Y,order,r);
        // do merge
        Merge_y(left,middle,right,arr_X,arr_Y,order,r);
    }
}

int main(){

    while(cin>>n){
        if(n<5||n>100000){
            cout<<"Warning : Value of n should between 5 and 100000"<<endl;
            continue;
        }
        int x[n],y[n],order[n],r[n];

        for(int i=0 ; i<n ; i++){
            cin>>x[i]>>y[i];
            r[i] = 0;
            order[i] = i;
        }

        /* Step1: sort by value x */
        Merge_sort_x(0,n-1,x,y,order);

        /* Step2: sort by value y and do rank calculate*/
        Merge_sort_y(0,n-1,x,y,order,r);
        cout<<"Rank: ";
        for(int i=0 ; i<n ; i++)
            cout<<r[i]<<" ";
        cout<<endl<<"======================="<<endl;

    }
    return 0;
}
