// { Driver Code Starts
// C++ program to merge k sorted arrays of size n each
#include <bits/stdc++.h>
using namespace std;

// A Linked List node
struct Node
{
	int data;
	Node* next;
	
	Node(int x){
	    data = x;
	    next = NULL;
	}
	
};

/* Function to print nodes in a given linked list */
void printList(Node* node)
{
	while (node != NULL)
	{
		printf("%d ", node->data);
		node = node->next;
	}
	cout<<endl;
}

 // } Driver Code Ends
/*Linked list Node structure

struct Node
{
	int data;
	Node* next;
	
	Node(int x){
	    data = x;
	    next = NULL;
	}
	
};
*/ 

class Solution{
  public:
    //Function to merge K sorted linked list.
    struct compare{
        bool operator()(struct Node* a, struct Node* b)
        {
            return a->data > b->data;
        }
    };
    
    Node * mergeKLists(Node *arr[], int K)
    {
           // Your code here
           priority_queue<Node*, vector<Node*>, compare> pq;
           for(int i = 0; i<K; i++){
               if(arr[i] != NULL) pq.push(arr[i]);
           }
           
           if(pq.empty()) return NULL;
           
           struct Node *headptr = new Node(0);
           struct Node *tailptr = headptr;
           
           while(!pq.empty()){
               struct Node* curr = pq.top();
               pq.pop();
               
               tailptr->next = curr;
               tailptr = tailptr->next;
               
               if (curr->next != NULL) pq.push(curr->next);
           }
           
           return headptr->next;
           
          
    }
};



// { Driver Code Starts.
// Driver program to test above functions
int main()
{
   int t;
   cin>>t;
   while(t--)
   {
	   int N;
	   cin>>N;
       struct Node *arr[N];
       for(int j=0;j<N;j++)
        {
           int n;
           cin>>n;

           int x;
           cin>>x;
           arr[j]=new Node(x);
           Node *curr = arr[j];
           n--;

           for(int i=0;i<n;i++)
           {
               cin>>x;
               Node *temp = new Node(x);
               curr->next =temp;
               curr=temp;
           }
   		}
   		Solution obj;
   		Node *res = obj.mergeKLists(arr,N);
		printList(res);

   }

	return 0;
}
  // } Driver Code Ends