#include<cstdlib>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int* getScore(const string &, const string &, int, int);
string lcs(const string &, const string &);

string re_x,re_y;

int main(){
    int t;
    cin>>t;
    if(t<2||t>20) return 0;
    while(t>0){
        --t;
        string x,y;
        cin>>x>>y;

        int m,n;
        m = x.length();
        n = y.length();
        if(m<5||m>1000||n<5||n>1000) break;

        cout<<lcs(x,y)<<endl;
    }
    return 0;
}

string lcs(const string &x, const string &y){
    int m,n;
    m = x.length();
    n = y.length();

    int *score_l,*score_r;
    string res;

    if(m==0 || n==0)
        return "";
    else if(m==1 || n==1){
        if(m==1 && y.find(x[0])!=string::npos){
            return res+=x[0];
        }
        else if(n==1 && x.find(y[0])!=string::npos){
            return res+=y[0];
        }
        else return "";
    }
    else{
        int max_sum = -1;
        int k;

        score_l = getScore(x.substr(0,m/2), y, m/2, n);

        re_x = x.substr(m/2,m-m/2);
        re_y = y;
        reverse(re_x.begin(),re_x.end());
        reverse(re_y.begin(),re_y.end());
        score_r = getScore(re_x, re_y, m-m/2, n);


        // find max as k
        for(int i=0 ; i<=n ; ++i){
            if(*(score_l+i)+ *(score_r+n-i) > max_sum){
                max_sum = *(score_l+i)+*(score_r+n-i);
                k = i;
            }
        }
        if(max_sum==0) return "";

        delete [] score_l;
        delete [] score_r;

        return lcs(x.substr(0,m/2),y.substr(0,k)) + lcs(x.substr(m/2,m-m/2),y.substr(k,n-k));
    }
}

int* getScore(const string &a,const string &b, int m, int n){

    int *prev = new int[n+1];
    int *now = new int[n+1];

    for(int i=0 ; i<m+1 ; ++i){
        for(int j=0 ; j<n+1 ; ++j){
            if(i==0 || j==0){
                now[j] = 0;
            }
            else{
                now[j] = (a[i-1]==b[j-1])? prev[j-1]+1 : max(prev[j],now[j-1]) ;
            }
        }
        // copy now_row to previous_row
        for(int k=0 ; k<=n ; ++k){
            prev[k] = now[k];
        }
    }
    delete [] prev;

    return now;
}





