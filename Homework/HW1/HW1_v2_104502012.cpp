#include<cstdlib>
#include<iostream>
#include<ctime>
using namespace std;

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
        for(j=i ; j>left && target[0]<arr_Y[j-1] ; j--){
            arr_Y[j] = arr_Y[j-1];
            arr_X[j] = arr_X[j-1];
            order[j] = order[j-1];
        }
        arr_Y[j] = target[0];
        arr_X[j] = target[1];
        order[j] = target[2];
        r[order[j]] += j-left;
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
        insertion_sort(left,right,arr_X,arr_Y,order,r);
    }
}

int main(){
    srand(time(NULL));
    double all=0;
    for(int num=30000 ; num>=25000 ; num-=100){
        int x[num],y[num],order[num],r[num];
        double min_T=10.0;
        int min_t;
        clock_t start,stop;
        double duration;
        // assign random number to point
        for(int i=0 ; i<num ; i++){
            x[i] = rand()%100;
            y[i] = rand()%100;
            r[i] = 0;
            order[i] = i;
        }

        for(int thre = 500 ; thre>=0 ; thre--){
            start = clock();
            Merge_sort_x(0,num-1,x,y,order);
            Merge_sort_y(0,num-1,x,y,order,r,thre);
            stop = clock();

            duration = (double)(stop-start)/CLOCKS_PER_SEC;
            if(duration < min_T){
                min_T = duration;
                min_t = thre;
            }
        }
        cout<<"While input "<<num<<" point, threshold is "<<min_t<<", and Time is: "<<min_T<<endl;
        all += min_t;
    }
    cout<<"Average threshold :"<<all/50;
    return 0;
}
