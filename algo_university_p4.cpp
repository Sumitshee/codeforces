#include <bits/stdc++.h>
  using namespace std;

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

  int main() {

    int n,m;
    cin>>n>>m;
    string cmd;
    cin>>cmd;
    vector<pair<int,int>>leaves(n);
    for(int i=0;i<n;i++){
      int u,v;
      cin>>u>>v;
      leaves[i]={u,v};
    }
    map<int,set<pair<int,int>>> mp1,mp2;
    for(int i=0;i<n;i++){
      mp1[leaves[i].second-leaves[i].first].insert(leaves[i]);//a,d
      mp2[leaves[i].second+leaves[i].first].insert(leaves[i]);
    }
    int sx = leaves[0].first, sy = leaves[0].second;
    set<pair<int,int>>vis;
    mp1[sy-sx].erase(leaves[0]);
    mp2[sy+sx].erase(leaves[0]);
    vis.insert(leaves[0]);
    for(int i=0;i<m;i++){
      if(cmd[i]=='A'){
          auto next = mp1[sy-sx].upper_bound({sx,sy});
          if(next==mp1[sy-sx].end()||vis.count(*next))continue;
          sx= (*next).first,sy=(*next).second;
          mp1[sy-sx].erase(*next);
          mp2[sy+sx].erase(*next);
          
          vis.insert(*next);
      }else if(cmd[i]=='C'){
          auto next = mp2[sy+sx].lower_bound({sx,sy});
          if(next==mp2[sy+sx].begin())continue;
          --next;
          if(next==mp2[sy+sx].end()||vis.count(*next))continue;
          sx= next->first,sy=next->second;
          mp1[sy-sx].erase(*next);
          mp2[sy+sx].erase(*next);
          vis.insert(*next);
          
      }else if(cmd[i]=='B'){
          auto next = mp2[sy+sx].upper_bound({sx,sy});
          if(next==mp2[sy+sx].end()||vis.count(*next))continue;
          sx= next->first,sy=next->second;
          mp1[sy-sx].erase(*next);
          mp2[sy+sx].erase(*next);
          vis.insert(*next);
          
      }else if(cmd[i]=='D'){
          auto next = mp1[sy-sx].lower_bound({sx,sy});
          if(next==mp1[sy-sx].begin())continue;
          --next;
          if(next==mp1[sy-sx].end()||vis.count(*next))continue;
          sx= next->first,sy=next->second;
          mp1[sy-sx].erase(*next);
          mp2[sy+sx].erase(*next);
          vis.insert(*next);
      }
    }
      cout<<sx<<" "<<sy<<endl;
    
    return 0;

  }
/*
Apaar is relaxing beside a large pond, while his pet frog Freddy is enjoying in the pond. The pond has N floating leaves, each defined by a x-coordinate and a y-coordinate as viewed from the sky.

From leaf located at (a, b) frog Freddy can jump:-

1) to (a + Z, b + Z) where Z is natural number. Call this direction A.

2) to (a + Z, b - Z) where Z is natural number. Call this direction B.

3) to (a - Z, b + Z) where Z is natural number. Call this direction C.

4) to (a - Z, b - Z) where Z is natural number. Call this direction D.

Apaar shouts one of the direction and Freddy jumps to the first leaf in chosen direction. If there is no leaf in that direction then Freddy doesn't moves. After Freddy jumps, the leaf Freddy jumps from collapses and sinks forever.

Freddy starts from first leaf and we also know all the M commands that Apaar shouted in sequence. We want to find out which leaf does Freddy ends up on at the end?

Constraints

1 <= N,M <= 100000.

X & Y will be in the range of int

 

 

Input
 

 

First line contains two integer N & M representing number of leafs in the pond and number of different commands Apaar shouts.
Second line contains a string of M characters describing all commands Apaar shouts.
Next N line contains two integers representing x-coordinate and y-coordinate of ith leaf. Freddy starts from first leaf.
 

 

Output
 

Print final x-coordinate and y-coordinate of Freddy the Frog.

 

 

Example
 

 

Input
7 5
ACDBB
5 6
8 9
4 13
1 10
7 4
10 9
3 7
Output
7 4
 */
