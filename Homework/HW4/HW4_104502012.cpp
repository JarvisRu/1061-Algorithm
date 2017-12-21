#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;


struct edge{
    int v1;
    int v2;
    int w;
};

bool sortByWeight(const edge &lhs, const edge &rhs) { return lhs.w < rhs.w; }

/* check if two vertex is in the same set
    in : return false
    not in : union     */
bool check(int x, int y, int *dad){
    int i=x, a=x, j=y, b=y, tmp;
    // trace to root
    while(dad[i]>-1)    i = dad[i];
    while(dad[j]>-1)    j = dad[j];

    // path compression
    while(dad[a]>-1){
        tmp = a;
        a = dad[a];
        dad[tmp] = i;
    }
    while(dad[b]>-1){
        tmp = b;
        b = dad[b];
        dad[tmp] = b;
    }

    if(i==j)
        return false;
    else
        dad[j] = i;

    return true;
}

int main(){
    int v,e;
    vector<int> ans;

    cin>>v>>e;
    while(v!=0 && e!=0){
        vector<edge> E(e);
        int dad[e];
        int res = 0;
        int res_e = 0;

        for(int i=0 ; i<e ; ++i){
            cin>>E[i].v1>>E[i].v2>>E[i].w;
            dad[i] = -1;
        }

        // in order by increasing weight
        sort(E.begin(),E.end(),sortByWeight);

        // do Kruskal's Algorithm
        for(int i=0 ; i<e ; ++i){
            if(check(E[i].v1,E[i].v2,dad)){
                res += E[i].w;
                ++res_e;
                if(res_e == e-1)
                    break;
            }
        }
        ans.push_back(res);
        // next run
        cin>>v>>e;
    }

    for(int i=0 ; i<ans.size() ; ++i){
        cout<<ans[i]<<endl;
    }
}
