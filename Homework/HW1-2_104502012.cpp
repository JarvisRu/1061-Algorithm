#include<cstdlib>
#include<iostream>
#include<ctime>
using namespace std;

int n;
int t; // threshold

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

void insertion_sort(int left, int right, int *arr_X, int *arr_Y, int *order, int *r){
    for(int i=left+1 ; i<right+1 ; i++){
        int target[3] = {arr_Y[i],arr_X[i],order[i]};
        int j;
        // cout<<target[0]<<endl;
        for(j=i ; j>left && target[0]<arr_Y[j-1] ; j--){
            arr_Y[j] = arr_Y[j-1];
            arr_X[j] = arr_X[j-1];
            order[j] = order[j-1];
        }
        // cout<<"j: "<<j<<endl;
        arr_Y[j] = target[0];
        arr_X[j] = target[1];
        order[j] = target[2];
        r[order[j]] += j-left;
        // cout<<"R["<<order[j]<<"]: "<<r[order[j]]<<endl;
    }
}

void Merge_sort_y(int left, int right, int *arr_X, int *arr_Y, int *order, int *r, int t){
    int middle;
    if(right-left>t){
        middle = (left+right)/2;
        // split the data
        Merge_sort_y(left,middle,arr_X,arr_Y,order,r,t);
        Merge_sort_y(middle+1,right,arr_X,arr_Y,order,r,t);
        // do merge
        Merge_y(left,middle,right,arr_X,arr_Y,order,r);
    }
    else{
        // cout<<"IN : "<<left<<" "<<right<<endl;
        insertion_sort(left,right,arr_X,arr_Y,order,r);
    }
}

int main(){

    cout<<"Please input a number as n, then it will create n point with random value: ";
    while(cin>>n){
        if(n<=0) break;
        else if(n<5||n>100000){
            cout<<"Value of n should between 5 and 100000"<<endl;
            cout<<"Please input a number as n, then it will create n point with random value: ";
            continue;
        }
        int x[n],y[n],order[n],r[n];
        srand(time(NULL));
        clock_t start,stop;
        long double duration;
        // assign random number to point
        for(int i=0 ; i<n ; i++){
            x[i] = rand()%100;
            y[i] = rand()%100;
            r[i] = 0;
            order[i] = i;
        }
        cout<<"Please input your testing threshold(27-30 will be best): ";
        while(cin>>t){
            if(t<=0) break;
            start = clock();
            Merge_sort_x(0,n-1,x,y,order);
            Merge_sort_y(0,n-1,x,y,order,r,t);
            stop = clock();
            duration = (long double)(stop-start)/CLOCKS_PER_SEC;
//        cout<<"Rank: ";
//        for(int i=0 ; i<n ; i++)
//            cout<<r[i]<<" ";
            cout<<"Time: "<<duration<<endl;
            cout<<"======================="<<endl;
            cout<<"Please input your testing threshold(27-30 will be best): ";
        }
        cout<<"======================="<<endl;
        cout<<"Please input a number as n, then it will create n point with random value: ";
    }
    return 0;
}
