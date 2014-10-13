/***********************************************************************/
//	Reactive
//	Sarthak Ahuja
//	IIIT-Delhi
/***********************************************************************/

#include <bits/stdc++.h>
#include<iostream>
#include<string.h>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<set>
#include<ctime>

typedef unsigned long long int ull;
typedef long long int ll;
typedef long int li;

#define MOD7 1000000007

#define FastIO ios_base::sync_with_stdio(false); cin.tie(0);

using namespace std;


int main(){
    FastIO
    int t;
    cin>>t;
    string s;
    while(t--) {
        cin>>s;
        vector<vector<pair<int,int> >graph(s.length());
        for(int i=0; i<l-1; i++)
        {
            if(i+1<l)
                graph[i].push_back(i+1);
            if(i-1>=0)
                graph[i].push_back(i-1);
        }

        vector<bool>visited(s.length(),0);
        vector<int>dist(l,INT_MAX);
        queue<int> q;
        q.push(0);
        dist[0]=0;
        int d=0;
        visited[0]=true;
        while(!q.empty()&&visited[l-1]==false)
        {
            int a=q.front();
            q.pop();
            int x=graph[a].size();
            for(int i=0; i<x; i++)
            {
                if(visited[graph[a][i]]==false)
                {
                    dist[graph[a][i]]=min(dist[graph[a][i]],dist[a]+1);
                    q.push(graph[a][i]);
                    visited[a]=1;
                }
            }
        }
    }
    return 0;
}
