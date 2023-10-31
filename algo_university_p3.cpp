
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

//COPY THE BLACKBOX, there is no need to change anything in it.
//Check the main function at bottom for USAGE

//****************BLACKBOX START*****************
//START COPYING FROM HERE

typedef int ll;

class Hash {
  private:
    map<tuple<int,int,int>,int>hash_table;
  public:
    Hash () {}
    int hash(int x){
        return hash({x,0,0});
    }
    int hash(tuple<int,int>x){
        return hash({get<0>(x),get<1>(x),0});
    }
    int hash(tuple<int,int,int>x){
        if(hash_table.find(x)!=hash_table.end())
            return hash_table[x];
        int new_hash = hash_table.size();
        hash_table[x]=new_hash;
        return new_hash;
    }
};

class Graph {

    bool is_directed;

    public:
        vector<vector<pair<int,ll>>>adj;
        int n,N=5000000;
        Hash h;

        Graph(int n_, bool is_directed_ = true){
            n=n_; is_directed = is_directed_;
            adj.resize(N,vector<pair<int,ll>>());
        }

        int hash(int u, int v){
            return h.hash({u,v});
        }
        int hash(int u, int v, int k){
            return h.hash({u,v,k});
        }

        void add_edge(int uR, int vR, ll c=0){
          int u=h.hash(uR), v=h.hash(vR);
          add_edge_internal(u,v,c);
        }
        void add_edge(tuple<int,int> uR, tuple<int,int> vR, ll c=0){
          int u=h.hash(uR), v=h.hash(vR);
          add_edge_internal(u,v,c);
        }
        void add_edge(tuple<int,int,int> uR, tuple<int,int,int> vR, ll c=0){
          int u=h.hash(uR), v=h.hash(vR);
          add_edge_internal(u,v,c);
        }


    private :

      void add_edge_internal(int u, int v, ll c=0){
            add_edge_weighted_undirected(u,v,c);
            if(!is_directed)
                add_edge_weighted_undirected(v,u,c);
        }
        void add_edge_weighted_undirected(int u, int v, ll c) {
            pair<int,ll>p = make_pair(v,c);
            adj[u].push_back(p);
        }

};

class BFS {
    vector<ll>min_dist_from_source;
    vector<bool> visited;
    Graph *g;

    public:
      BFS(Graph *g_) {
          g = g_;
          clear();
      }

        void clear() {
            min_dist_from_source.clear();
            min_dist_from_source.resize(g->N,-1);
            visited.clear();
            visited.resize(g->N, false);
        }


      void run(int sourceR) {
        int source = (g->h).hash(sourceR);
        run_internal(source);
      }
      void run(tuple<int,int> sourceR) {
        int source = (g->h).hash(sourceR);
        run_internal(source);
      }
      void run(tuple<int,int,int> sourceR) {
        int source = (g->h).hash(sourceR);
        run_internal(source);
      }


      int min_dist(int targetR){
        int target = (g->h).hash(targetR);
        return min_dist_internal(target);
      }
      int min_dist(tuple<int,int> targetR){
        int target = (g->h).hash(targetR);
        return min_dist_internal(target);
      }
      int min_dist(tuple<int,int,int> targetR){
        int target = (g->h).hash(targetR);
        return min_dist_internal(target);
      }

      bool is_visited(int targetR){
        int target = (g->h).hash(targetR);
        return is_visited_internal(target);
      }
      bool is_visited(tuple<int,int> targetR){
        int target = (g->h).hash(targetR);
        return is_visited_internal(target);
      }
      bool is_visited(tuple<int,int,int> targetR){
        int target = (g->h).hash(targetR);
        return is_visited_internal(target);
      }

  private:
    void run_internal(int source) {
            queue<int> q;
            q.push(source);

            visited[source] = true;
            min_dist_from_source[source] = 0;

            while(!q.empty()) {
                int cur_node = q.front();
                for (unsigned int i = 0; i < (g->adj[cur_node]).size(); ++i) {
                    int adj_node =  (g->adj[cur_node])[i].first;
                    if (visited[adj_node] == false) {
                        visited[adj_node] = true;
                        min_dist_from_source[adj_node] = min_dist_from_source[cur_node] + 1;
                        q.push(adj_node);
                    }
                }
                q.pop();
            }

            return;
    }

    int min_dist_internal(int target){
        return min_dist_from_source[target];
    }

    bool is_visited_internal(int target){
        return visited[target];
    }

};
//END COPYING HERE
//********************BLACKBOX END******************
/*------------------------------------------------------------------------------------------------------------*/
void wrong_submission(){
    int n,m;
    cin>>n>>m;
    Graph g(n);
    for (int i = 0; i < m; i++)
    {
        int u,v; cin>>u>>v;
        g.add_edge(u,v,1);
        g.add_edge(v,u,1);
    }

    BFS bfs1(&g);
    BFS bfs2(&g);
    bfs1.run(1);
    bfs2.run(n);
    vector<int>ans;
    if(bfs1.min_dist(n)==-1){
        cout<<-1<<endl;
        return;
    }
    for (int i = 1; i <= n ; i++)
    {
        if(bfs1.min_dist(i)+bfs2.min_dist(i)==bfs1.min_dist(n))ans.push_back(i);
    }
    for (int i = 0; i < ans.size(); i++)
    {
        cout<<ans[i]<<" ";
    }
    cout<<endl;

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
     // cin>> t;
      for(int i = 1; i <= t; i++){
           // kick_start(i);
           wrong_submission();
      }


   auto stop = std::chrono::high_resolution_clock::now(); 
   auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

   // #ifndef ONLINE_JUDGE
   // cerr << "Time taken : " << ((long double)duration.count())/((long double) 1e9) <<"s "<< endl;    
   // #endif
   return 0;
}
