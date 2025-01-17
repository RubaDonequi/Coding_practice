// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends



class Solution
{
    public:
    //Function to return Breadth First Traversal of given graph.
    map<int, bool> visited;
	vector<int>bfsOfGraph(int V, vector<int> adj[])
	{
	    // Code here
	    queue<int> q;
	    vector<int> ans;

	    for(int i = 0; i<V; i++) visited[i] = false;
	    
	    q.push(0);
	    visited[0] = true;
	    ans.push_back(0);
	    while(!q.empty()){
	        int tmp = q.front();
	        for(auto u: adj[tmp]){
	            if (!visited[u]){
	                q.push(u);
	                ans.push_back(u);
	                visited[u] = true;
	            }
	        }
	        q.pop();
	    }
	    
	    return ans;
	    
	}
};

// { Driver Code Starts.
int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int V, E;
    	cin >> V >> E;

    	vector<int> adj[V];

    	for(int i = 0; i < E; i++)
    	{
    		int u, v;
    		cin >> u >> v;
    		adj[u].push_back(v);
    // 		adj[v].push_back(u);
    	}
        // string s1;
        // cin>>s1;
        Solution obj;
        vector<int>ans=obj.bfsOfGraph(V, adj);
        for(int i=0;i<ans.size();i++){
        	cout<<ans[i]<<" ";
        }
        cout<<endl;
	}
	return 0;
}  // } Driver Code Ends