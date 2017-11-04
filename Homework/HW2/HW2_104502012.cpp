#include<cstdlib>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
//1
//lRk3W1I9WxwL8u3l2GA4 3In9qxKcLuN963Yxlvq4
//3I9xLu3l4
//1
//bdcaba abcbdab
//bcab
//1
//ABACABAC CABCBAAB
//ABAAB


int* getScore(int mode, string a, string b, int m, int n){
    if(mode==2){
        reverse(a.begin(),a.end());
        reverse(b.begin(),b.end());
    }

    int *prev = new int[n];
    int *now = new int[n];

    for(int i=0 ; i<m ; ++i){
        for(int j=0 ; j<n ; ++j){
            // for first row
            if(i==0){
                if(a[i]==b[j])
                    now[j] = 1;
                else if(now[j-1]==1)
                    now[j] = 1;
                else
                    now[j] = 0;
            }
            // for others
            else{
                if(j==0){
                    if(a[i]==b[j])
                        now[j] = 1;
                    else
                        now[j] = prev[j];
                }
                else{
                    if(a[i]==b[j])
                        now[j] = prev[j-1] + 1;
                    else
                        now[j] = max(prev[j],now[j-1]);
                }

            }
        }
        // copy now_row to previous_row
        for(int k=0 ; k<n ; ++k){
            prev[k] = now[k];
        }
    }
    delete [] prev;
    // cout<<"x: "<<a<<" / y: "<<b<<endl;
    return now;

}

string lcs(string x, string y){
    int m,n;
    m = x.length();
    n = y.length();

    int *score_l,*score_r;
    string res;
    if(m==1 || n==1){
        if(m==1 && y.find(x[0])!=string::npos){
            // cout<<"hit: "<<x[0]<<endl;
            return res+=x[0];
        }
        else if(n==1 && x.find(y[0])!=string::npos){
            // cout<<"hit: "<<y[0]<<endl;
            return res+=y[0];
        }
        else return "";
    }
    else{
        int max_sum = -1;
        int k;

        score_l = getScore(1,x.substr(0,m/2), y, m/2, n);
        score_r = getScore(2,x.substr(m/2,m-m/2), y, m-m/2, n);

//        cout<<"Score_l: ";
//        for(int i=0 ; i<n ; ++i){
//            cout<<*(score_l+i)<<" ";
//        }
//        cout<<endl<<"Score_r: ";
//        for(int i=0 ; i<n ; ++i){
//            cout<<*(score_r+i)<<" ";
//        }

        for(int i=0 ; i<n ; ++i){
            if(*(score_l+i)+ *(score_r+n-i-2) > max_sum && i!=n-1){
                max_sum = *(score_l+i)+*(score_r+n-i-2);
                k = i;
            }
            if(i==n-1 && *(score_l+i) > max_sum){
                return res+=y[n-1];
            }
        }
        if(max_sum==0) return "";

//        cout<<"max: "<<max_sum<<" "<<"k: "<<k<<endl;
//        cout<<m<<" "<<n<<endl;
//        cout<<x<<" "<<y<<endl;
//        cout<<x.substr(0,m/2)<<" , "<<y.substr(0,k+1)<<endl;
//        cout<<x.substr(m/2,m-m/2)<<" , "<<y.substr(k+1,n-k+1)<<endl;
//        cout<<"============================"<<endl;
        return lcs(x.substr(0,m/2),y.substr(0,k+1)) + lcs(x.substr(m/2,m-m/2),y.substr(k+1,n-k+1));
    }
}




int main(){
    int t;
    cin>>t;
    // if(t<2||t>20) return 0;
    while(t>0){
        --t;
        string x,y;
        cin>>x>>y;

        // if(m<5||m>1000||n<5||n>1000) break;
        cout<<lcs(x,y);
        cout<<endl;

    }
    return 0;
}



