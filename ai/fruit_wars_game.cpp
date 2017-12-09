#include<bits/stdc++.h>
#include<time.h>
using namespace std;
#define ll long long
#define pp pair<int,int>
#define fi first
#define se second


clock_t st_time;
double tim;
int n,p,row,col;
int deep;
int component;


int playmin(vector<string>,int , int, int,int );


void evaluate(vector<string>& s, char &m, vector<vector<bool>>& vis,int i,int j,int &c){
        if(vis[i][j]) return;
        vis[i][j]=true;
        if(s[i][j]!=m) return;
        c++;

        if(j<n-1){
            
            evaluate(s,m,vis,i,j+1,c);
        }
        if(j>0){
            
            evaluate(s,m,vis,i,j-1,c);
        }
        if(i<n-1){
            
            evaluate(s,m,vis,i+1,j,c);
        }
        if(i>0){
            
            evaluate(s,m,vis,i-1,j,c);
        }
        
        
}



void caliberate(vector<string> s){
    component=0;
    for(int k=0;k<p;k++){
        vector<vector<bool>> vis(n,vector<bool>(n,false));
        char m='0'+k;

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){

                if (s[i][j] == m && !vis[i][j]){
                    int c=0;
                    evaluate(s, m, vis, i, j,c);
                    component++;
                    

                }
            
            }
        }
    }
    cout<<component<<"\n";

    if(component>=300){deep=3;component=min(component,300);}
    //else if(component>=200){deep=3;component=min(component,200);}
    else if(component>=120){deep=4;component=min(component,120);}
    else if(component>=80){deep=5;component=min(component,100);}
    else if(component>=50){deep=5;component=min(component,50);}
    else if(component>=30){deep=6;component=min(component,30);}
    else if(component>=20){deep=7;}
    else deep=8;

    if(tim<240 && deep>=3)deep--;
    if(tim<50 && deep>=4)deep--;
    if(tim<15 && deep>=3)deep--;



    // if(component<50)
    // if(n<=10){
    //     if(tim > 250) deep=8;
    //     else if(tim > 50) deep = 7;
    //     else deep =6;
    // }
    // else if(n<=15){
    //     if(tim > 250) deep=7;
    //     else if(tim > 50) deep = 6;
    //     else deep =5;
    // }
    // else{
    //     if(tim > 200) deep=6;
    //     else if(tim > 50) deep = 5;
    //     else deep =4;
    // }
}









void genhollow(vector<string> &s1, char &m,int i, int j){
    
    if(s1[i][j]!=m) return;
    s1[i][j]='*';

    if(j<n-1){
            
        genhollow(s1,m,i,j+1);
    }
    if(j>0){
            
        genhollow(s1,m,i,j-1);
    }
    if(i<n-1){
            
        genhollow(s1,m,i+1,j);
    }
    if(i>0){
            
        genhollow(s1,m,i-1,j);
    }
}



vector<string> gennewstring(vector<string> s1, pair<int,pp> &t){
    int a = t.se.fi, b=t.se.se;
    char m=s1[a][b];
    genhollow(s1,m,a,b);
    
    for(int i=0;i<n;i++){
        int flag=0;
        for(int j=n-1;j>=0;j--){
            if(s1[j][i]=='*' && flag==0){
                a=j;
                flag=1;
            }
            if(s1[j][i]!='*' && flag==1){
                swap(s1[j][i],s1[a][i]);
                a--;
            }
        }
    }
    
    return s1;
}











int playmax(vector<string> s,int value,int depth, int alpha, int beta){
    //cout<<depth<<" ";
    clock_t en_time = clock();
    if((double)(en_time-st_time)/CLOCKS_PER_SEC>(tim-0.05) && depth>0) return value;
    if(depth==deep) return value;
    priority_queue<pair<int,pp>> que;
    for(int k=0;k<p;k++){
        vector<vector<bool>> vis(n,vector<bool>(n,false));
        char m='0'+k;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){

                if (s[i][j] == m && !vis[i][j]){
                    int c=0;
                    evaluate(s, m, vis, i, j,c);
                    
                    que.push({value+c*c,{i,j}});

                }
            
            }
        }
    }
    int trail=component-depth;
    int maxi = INT_MIN;
    while(!que.empty() && trail){
        pair<int,pp> t = que.top();
        que.pop();
        vector<string> s1 = gennewstring(s,t);
        int suc = playmin(s1,t.fi,depth+1,alpha,beta);
        
        if(maxi<suc){
            
            maxi=suc;
            if(depth==0){
                row=t.se.fi;
            col = t.se.se;
            }
        }
        if(maxi>=beta) return maxi;
        alpha=max(alpha,maxi);
        trail--;
        
    }
    if(maxi==INT_MIN)
        return value;
    else
        return maxi;
    
    // cout<<que.top().first<<" "<<que.top().second.first<<" "<<que.top().second.second;
    // que.pop();
    // cout<<que.top().first<<" "<<que.top().second.first<<" "<<que.top().second.second;
}







int playmin(vector<string> s,int value, int depth, int alpha, int beta){
    //cout<<depth<<" ";
    clock_t en_time = clock();
    if((double)(en_time-st_time)/CLOCKS_PER_SEC>(tim-0.05) ) return value;
    if(depth==deep) return value;
    priority_queue < pair<int,pp>, vector<pair<int,pp>>, greater<pair<int,pp>> > que;
    for(int k=0;k<p;k++){
        vector<vector<bool>> vis(n,vector<bool>(n,false));
        char m='0'+k;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){

                if (s[i][j] == m && !vis[i][j]){
                    int c=0;
                    evaluate(s, m, vis, i, j,c);
                    
                    que.push({value-c*c,{i,j}});

                }
            
            }
        }
    }
    int trail=component-depth;
    int mini = INT_MAX;
    while(!que.empty() && trail){
        pair<int,pp> t = que.top();
        que.pop();
        vector<string> s1 = gennewstring(s,t);
        int suc = playmax(s1,t.fi,depth+1,alpha,beta);
        
        if(mini>suc){
            
            mini=suc;
            
        }
        if(mini<=alpha) return mini;
        beta=min(beta,mini);
        trail--;
        
    }
    if(mini==INT_MAX)
        return value;
    else
        return mini;

    // cout<<que.top().first<<" "<<que.top().second.first<<" "<<que.top().second.second;
    // que.pop();
    // cout<<que.top().first<<" "<<que.top().second.first<<" "<<que.top().second.second;
}



int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    st_time = clock();
    
    ios::sync_with_stdio(0);
    cin>>n>>p>>tim;
    vector<string> s(n);
    for(int i=0;i<n;i++){
        cin>>s[i];
    }

    caliberate(s);

    int alpha=INT_MIN,beta=INT_MAX;
    int value= playmax(s,0,0,alpha,beta);
    //cout<<"\n"<<value<<"\n";
    char colu = 'A'+col;
    cout<<colu<<row+1<<"\n";
    pair<int,pp> t={0,{row,col}};
    vector<string> s1 = gennewstring(s,t);
    for(int i=0;i<n;i++){
        cout<<s1[i]<<"\n";
    }
    clock_t en_time = clock();
    double tiii=(double)(en_time-st_time)/CLOCKS_PER_SEC;
    cout<<"\n"<<tiii;
    return 0;
}