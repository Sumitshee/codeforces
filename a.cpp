/*/ Author: Sumit8707 /*/

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC optimize ("O3")
#include<bits/stdc++.h> 
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define endl "\n"
#define ff first
#define ss second
#define max3(a, b, c) max(max((a), (b)), (c))
#define max4(a, b, c, d) max(max((a), (b)), max((c), (d)))
#define min3(a, b, c) min(min((a), (b)), (c))
#define min4(a, b, c, d) min(min((a), (b)), min((c), (d)))
#define sz(x) ((int)(x).size())
#define pb push_back
#define all(v) (v).begin(),(v).end()
 
 
template<class T> using oset = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T> using moset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
// find_by_order(k)  returns iterator to kth element starting from 0;
// order_of_key(k) returns count of elements strictly smaller than k;
void kick_start(int t) {cout << "Case #" << t << ": ";}

/*------------------------------------------------------------------------------------------------------------*/
void wrong_submission(){
    int n; cin>>n;
    vector<int>v(n);
    moset<int>o;
    set<int>s;
    for(int i = 0; i<n; i++){
        cin>>v[i];
        o.insert(v[i]);
        s.insert(v[i]);
    }
    sort(all(v));
    if(s.size()==n)cout<<0<<endl;
    else{
        map<int,int>m;
        for (int i = 0; i < n-1; i++)
        {
            if(v[i]==v[i+1]){
                 m[v[i]]++;
            }
        }
        int ans = 0;
        for(auto &it:m){
            int key = it.ff;
            int frequency = it.ss + 1;
            // cout<<frequency<<endl;
            ans += frequency*(frequency-1)/2*o.order_of_key(key);
            ans += frequency*(frequency-1)*(frequency-2)/6;
            // cout<<it.ff<<' '; 
        }
        cout<<ans<<endl;
    }

}
/*------------------------------------------------------------------------------------------------------------*/ 
int32_t main() {
   ios_base::sync_with_stdio(0); 
   cin.tie(0); cout.tie(0);
   #ifndef ONLINE_JUDGE
   freopen("input.txt","r",stdin);
   freopen("output.txt","w",stdout);
   #endif

   auto start = std::chrono::high_resolution_clock::now();
 
     int t=1;
     cin>> t;
      for(int i = 1; i <= t; i++){
           // kick_start(i);
           wrong_submission();
      }


   auto stop = std::chrono::high_resolution_clock::now(); 
   auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

   #ifndef ONLINE_JUDGE
   cerr << "Time taken : " << ((long double)duration.count())/((long double) 1e9) <<"s "<< endl;    
   #endif
   return 0;
}