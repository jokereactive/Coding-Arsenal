/***********************************************************************/
//	Reactive
//	Sarthak Ahuja
//	IIIT-Delhi
/***********************************************************************/


//header files
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

//typedefs
typedef unsigned long long int ull;
typedef long long int ll;
typedef long int li;

#define MOD 1000000007

#define FastIO ios_base::sync_with_stdio(false); cin.tie(0);

using namespace std;

/*Power by exponentiation*/
ll modular_pow(ll base, ll exponent, int modulus)
{
    ll result = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

/*Matrix Exponentiation*/
typedef vector<vector<ll> > matrix;
const int K=2;
matrix mul(matrix A, matrix B)
{
    matrix C(K+1,vector<ll>(K+1));
    for(int i=1;i<=K;++i)
    for(int j=1;j<=K;++j)
    for(int k=1;k<=K;++k)
    C[i][j]=(C[i][j]+A[i][k]*B[k][j])%MOD;
    return C;
}

/*Matrix Power*/
matrix mat_pow(matrix A, int p)
{
    if(p==1)
    return A;
    if(p&1)
    return mul(A,mat_pow(A,p-1));
    matrix tmp=mat_pow(A,p/2);
    return mul(tmp, tmp);
}


ll solve(ll n, ll ar[2])
{
matrix ans(K+1,vector<ll>(K+1));
ans[1][1]=0, ans[1][2]=1;
ans[2][1]=2, ans[2][2]=1;
if(n==1)
return ar[0];
ans=mat_pow(ans,n-1);
ll res=0;
for(int i=1;i<=K;++i)
res=(res+ans[1][i]*ar[i-1])%MOD;
return res;
}

/*Minimum Spanning Tree*/
struct node
{
    int src,dest;
    ll wght;
};
int par[100005],rnk[100005];
int Find(int nd)
{
    if(par[nd]!=nd)
    par[nd]=Find(par[nd]);
    return par[nd];
}
void Union(int nd1, int nd2)
{
    int x=Find(nd1);
    int y=Find(nd2);
    if(rnk[x]<rnk[y])
        par[x]=y;
    else if(rnk[x]>rnk[y])
        par[y]=x;
    else
    {
        par[y]=x;
        rnk[x]++;
    }
}

bool compare(node n1, node n2)
{
    return n1.wght<n2.wght;
}

vector<node> mst;

void kruskal(vector<node> g, int n)
{
    for(int i=0;i<n;++i)
    {
        par[i]=i;
        rnk[i]=0;
    }
    sort(g.begin(),g.end(),compare);
    int cnt=0,cnt1=0;
    while(cnt!=n-1)
    {
        node ne=g[cnt1++];
        int x=Find(ne.src);
        int y=Find(ne.dest);
        if(x!=y)
        {
            mst.push_back(ne);
            Union(x,y);
            cnt++;
        }
    }
}

/*Distance on tree using BFS or DFS*/
ll ans[1005][1005],wt[1005][1005];
vector<int> adj[1005];
bool visited[1005];

/*Using DFS*/
void dfs(int nd, int src)
{
    visited[nd]=true;
    for(int i=0;i<adj[nd].size();++i)
    {
        if(!visited[adj[nd][i]])
        {
            if(src==adj[nd][i])
                ans[src][adj[nd][i]]=0;
            else
                ans[src][adj[nd][i]]=(ans[src][nd]+wt[nd][adj[nd][i]]);
            dfs(adj[nd][i],src);
        }
    }
}

/*Using BFS*/
void bfs(int nd, int src)
{
    queue<int> q;
    q.push(nd);
    while(!q.empty())
    {
        int id=q.front();
        q.pop();
        if(visited[id])
        continue;
        visited[id]=true;
        for(int i=0;i<adj[id].size();++i)
        {
            if(!visited[adj[id][i]])
            {
                if(src==adj[id][i])
                    ans[src][adj[id][i]]=0;
                else
                    ans[src][adj[id][i]]=(ans[src][id]+wt[id][adj[id][i]]);
                q.push(adj[id][i]);
            }
        }
    }
}

/*Shortest Path using Dijkstra*/
vector<vector<pair<int,int> > >G(1005);
vector<int> Dijkstra(int s)
{
    vector<int> D(1005,INT_MAX);
    set<pair<int,int> > Q;
    D[s] = 0;
    Q.insert(make_pair(0,s));
    while(!Q.empty())
    {
        pair<int,int> top = *Q.begin();
        Q.erase(Q.begin());
        int v = top.second;
        int d = top.first;

        for (vector<pair<int,int> >::const_iterator it = G[v].begin(); it != G[v].end(); it++)
        {
            int v2 = it->first;
            int cost = it->second;
            if (D[v2] > D[v] + cost)
            {
                if (D[v2] != INT_MAX)
                {
                    Q.erase(Q.find(make_pair(D[v2], v2)));
                }
                D[v2] = D[v] + cost;
                Q.insert(make_pair(D[v2], v2));
            }
        }
    }
    return D;
}
/*Shortest path using bellman ford*/
void bellman(int n)
{
    ll dist[n][n];
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            dist[i][j]=INT_MAX;

    //take input here
    for(int i=1;i<=n;++i)
        dist[i][i]=0;
    for(int k=1;k<=n;++k)
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
}

//calculates a^x mod p in logarithmic time.
long modPow(long a, long x, long p) {
    long res = 1;
    while(x > 0) {
        if( x % 2 != 0) {
            res = (res * a) % p;
        }
        a = (a * a) % p;
        x /= 2;
    }
    return res;
}

//calculates the modular multiplicative of a mod m.
//(assuming p is prime).
long modInverse(long a, long p) {
    return modPow(a, p-2, p);
}

// Calculate nCk%p
long modBinomial(long n, long k, long p) {
    long numerator = 1;
    for (int i=0; i<k; i++) {
        numerator = (numerator * (n-i) ) % p;
    }
    long denominator = 1;
    for (int i=1; i<=k; i++) {
        denominator = (denominator * i) % p;
    }
    return ( numerator* modInverse(denominator,p) ) % p;
}

ull gcd(ull num , ull den){
	if(num == 0) return 1;
	while(num != den){
		if(num > den) num = num - den;
		else den = den - num;
	}
	return num;
}


void primeFactors(int n)
{
    while (n%2 == 0)
    {
        printf("%d ", 2);
        n = n/2;
    }
    for (int i = 3; i <= sqrt(n); i = i+2)
    {
        while (n%i == 0)
        {
            printf("%d ", i);
            n = n/i;
        }
    }
    if (n > 2)
        printf ("%d ", n);
}

//Calculate nCk
ull nCk( ull n, ull k )
{
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    int result = n;
    for( int i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

/*
Get All Divisors of a number
def getDivisors(n):
    divisors = []
    d = 1
    while d*d < n:
        if n % d == 0:
            divisors.append(d)
            divisors.append(n / d);
        d += 1
    if d*d == n:
        divisors.append(d)
    return divisors
*/

int main(){
    FastIO
    int foo[] = { 10, 20, 30 };

	cin>>s;
	string f , c , res ;
    cin>>f;
    getline(cin,c);
    getline(cin,c);
	int len = s.length();
	vector < pair < int , char > > keys(27);
    for( int i = 1 ; i <= 26 ; i++){
    keys[i].first = i*-1;
    keys[i].second = i+96;
    }
    string s;
    vector < char > cuniq;
    long int clen = c.length();
    for(int i = 0 ; i < clen ; i++){
    if(c[i] >= 65 && c[i] <= 90){
    cuniq.push_back(c[i]+22);
    sort(keys.begin()+1,keys.end(),compare);
	cout<<res<<endl;
	scanf("%d %d %d",&n,&m,&k);
    for(int i = 0 ; i < n ; i++) scanf("%d",&a[i]);
    int points[n][m];
    int cost[n][m];

    for(int i = 0 ; i < n ; i++){
    for(int j = 0; j < m ;j++){
    scanf("%d",&points[i][j]);
    }
    }
    std::string s = "aba";
    std::sort(s.begin(), s.end());
    do {
        std::cout << s << '\n';
    } while(std::next_permutation(s.begin(), s.end()));
	return 0;
	std::stringstream ss;
    std::string input = "a b c 4 e";
    ss << input;
    int found;
    std::string temp;

    while(std::getline(ss, temp,' ')) {
        if(std::stringstream(temp)>>found)
        {
            std::cout<<found<<std::endl;
        }
    }

    cout << "Please enter a valid number: ";
   getline(cin, input);

   // This code converts from string to number safely.
   stringstream myStream(input);
   if (myStream >> myNumber)
     break;
   cout << "Invalid number, please try again" << endl;
 }
 int x; // the number you want to factor
Map<int to int> primeFactor; // this is a map that will map each prime that appears in the prime factorization to the number of times it appears.

while(x > 1) {
  for each prime p <= x {
     if x % p == 0 {
       x = x / p;
       primeFactor(p) = primeFactor(p) +1;
     }
  }
}
int result = 1;
for each value v in primeFactors {
  result*= (v+1);
}
}
