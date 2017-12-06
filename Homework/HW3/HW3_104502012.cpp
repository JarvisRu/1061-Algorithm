#include<iostream>
#include <climits>
#include<vector>
using namespace std;

struct job{
    int time;
    int deadline;
};

void Merge_sort(int, int, job[]);
void Merge(int, int, int, job[]);
void insert_heap(job, job[], int &);
job pop(job[], int &);

int main(){
    int k,n;
    cin>>k;
    vector<int> ans;
    while(k>0){
        cin>>n;
        job jobs[n];

        for(int i=0 ; i<n ; ++i){
            cin>>jobs[i].time>>jobs[i].deadline;
        }
        // merge sort jobs by deadline
        Merge_sort(0,n-1,jobs);

        job heap[n+1];
        job removed_job;
        int nowNum = 0;     // heap size now
        int total_time = 0;

        for(int i=0 ; i<n ; ++i){
            // push job into heap order by time
            insert_heap(jobs[i], heap, nowNum);
            total_time += jobs[i].time;
            if(total_time > jobs[i].deadline){
                removed_job = pop(heap, nowNum);
                total_time -= removed_job.time;
            }
        }

        ans.push_back(nowNum);
        --k;
    }

    for(int i=0 ; i<ans.size() ; ++i){
        cout<<ans[i]<<endl;
    }

    return 0;
}

void Merge_sort(int left, int right, job *jobs){
    int middle;
    if(left < right){
        middle = (left+right)/2;
        // split the data
        Merge_sort(left,middle,jobs);
        Merge_sort(middle+1,right,jobs);
        // do merge
        Merge(left,middle,right,jobs);
    }
}

void Merge(int left, int middle, int right, job *jobs){

    job temp[right-left+1];
    // for merge easily
    int i=left,j=middle+1;
    int rear=0;
    // compare and assign value to temp
    while(i<=middle && j<=right){
        if(jobs[i].deadline >= jobs[j].deadline){
            temp[rear] = jobs[j];
            ++rear;
            ++j;
        }
        else if(jobs[i].deadline < jobs[j].deadline){
            temp[rear] = jobs[i];
            ++rear;
            ++i;
        }
    }
    // for remaining value
    while(i<=middle){
        temp[rear] = jobs[i];
        ++rear;
        ++i;
    }
    while(j<=right){
        temp[rear] = jobs[j];
        ++rear;
        ++j;
    }

    for(int i=left ; i<=right ; i++){
        jobs[i] = temp[i-left];
    }

}

void insert_heap(job j, job *heap, int &now){
    heap[++now] = j;
    int nowSize = now;
    // up heap
    job item = heap[now];
    heap[0].time = INT_MAX;
    while(heap[now/2].time < item.time){
        heap[now] = heap[now/2];
        now /= 2;
    }
    heap[now] = item;
    now = nowSize;
}

job pop(job *heap, int &now){
    job target = heap[1];
    heap[1] = heap[now--];
    // down heap
    int k=1,j;
    job tmp = heap[k];
    while(k <= now/2){
       j = 2*k;
       if(j<now && heap[j].time < heap[j+1].time) j++;
       if(tmp.time >= heap[j].time)   break;
       heap[k] = heap[j];
       k = j;
    }
    heap[k] = tmp;

    return target;
}
