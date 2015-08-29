#include <iostream>
#include <cstdlib>
using namespace std;

struct node {
	char info;
	struct node* next;
};

class stack {
	struct node* top;
public:
	stack();
	void push(char);
	char pop();
	bool isEmpty();
	void display();
};

stack::stack() {
	top = NULL;
}

void stack::push(char ch) {
	node* n = new node;
	
	n->info = ch;
	n->next = NULL;
	if (top != NULL) {
		n->next = top; //works as LIFO
	}
	top = n;
}

char stack::pop() {
	struct node* temp;
	char value;
	if (top == NULL) {
		cout << "\nThe stack is empty" << endl;
	}
	else {
		temp = top;
		top = top->next;
		value = temp->info;
		delete temp;
	}
	return value;
}

bool stack::isEmpty() {
	return (top == NULL);
}

void stack::display() {
	struct node* n = top;
	if (top == NULL) {
		cout << "\nStack is empty.\n";
	}
	else {
		while (n != NULL) {
			cout << n->info << endl;
			n = n->next;
		}
	}
}

class graph {
private:
	int noOfNodes;
	char* nodeNames;
	short** adjMatrix; // adjacency matrix, stores only 0 or 1
public:
	graph(int noOfNodes, char *names);
	~graph();
	bool isConnected(int, int);
	void addEdge(int n1, int n2);
	void addEdge(char start, char end);
	void addEdge(char startNode, char endNode, int noOfEdges);
	void DFS(int, int);
};

graph::graph(int n, char* names ) { //here graph is undirected connected simple graph
	int i, j;
	noOfNodes = n;
	adjMatrix = new short*[noOfNodes];
	nodeNames = new char[noOfNodes];
	for (i = 0; i < noOfNodes; ++i) {
		adjMatrix[i] = new short[noOfNodes];
		nodeNames[i] = names[i];
		for (j = 0; j < noOfNodes; ++j) {
			adjMatrix[i][j] = 0; // node i and node j are not adjacent or no edge between them
		}	
	}
}

graph::~graph() {
	for (int i = 0; i < noOfNodes; ++i) {
		delete[] adjMatrix[i];
	}		
	delete[] adjMatrix;
}

bool graph::isConnected(int node1, int node2) {
	return (adjMatrix[node1][node2] == 1);
}

void graph::addEdge(int n1, int n2) {
	adjMatrix[n1 - 1][n2 - 1] = adjMatrix[n2 - 1][n1 - 1] = 1;
}

void graph::addEdge(char startNode, char endNode) {
	int n1, n2, i;
	for (i = 0; i < noOfNodes; i++) {
		if (startNode == nodeNames[i]) {
			n1 = i; break;
		}
	}
	for (i = 0; i < noOfNodes; i++){
		if (endNode == nodeNames[i]) {
			n2 = i;
		}
	}
	adjMatrix[n1][n2] = adjMatrix[n2][n1] = 1;
}

void graph::addEdge(char startNode, char endNode, int noOfEdges) {
	int n1, n2, i, j;
	for (j = 0; j < noOfEdges; j++) {
		for (i = 0; i < noOfNodes; i++) {
			if (startNode == nodeNames[i]) {
				n1 = i; break;
			}
		}
		for (i = 0; i < noOfNodes; i++) {
			if (endNode == nodeNames[i]) {
				n2 = i;
			}
		}
		adjMatrix[n1][n2] = adjMatrix[n2][n1] = 1;
	}
}

void graph::DFS(int startNode, int goalNode) {
	stack s;
	startNode--; goalNode--; // to directly use in visited array as index
	bool* visited = new bool[noOfNodes];
	int i;
	int currentNode;
	for (i = 0; i < noOfNodes; i++) {
		visited[i] = false;
	}
	s.push(startNode);
	visited[startNode] = true;
	if (startNode == goalNode) return;
	cout << "Depth First Search starting from node ";
	cout << startNode+1 << " : " << endl;

	while (!s.isEmpty())
	{
		currentNode = s.pop();
		
		cout << currentNode+1;
		if (currentNode == goalNode) {
			cout << "\nGoal Node is found: " << goalNode+1;
			break;
		}
		else {
			cout << " -> ";
		}
		for (i = noOfNodes-1; i >= 0; i--) {
			if (isConnected(currentNode, i) && !visited[i]) {
				s.push(i);
				visited[i] = true;
			}
		}
	}
	cout << endl;
	delete[] visited;
}

int main() {
	char* nodes = "ABCDEFGH";
	graph g(8, nodes);

	//g.addEdge(1, 2); g.addEdge(1, 3); g.addEdge(2, 4);
	//g.addEdge(2, 5); g.addEdge(3, 6); g.addEdge(3, 7);
	g.addEdge('A', 'B'); g.addEdge('A', 'C'); g.addEdge('B', 'D');
	g.addEdge('B', 'E'); g.addEdge('C', 'F'); g.addEdge('C', 'G');

	g.DFS(1, 6);
	cout << endl;
	system("pause");
	return 0;
}
