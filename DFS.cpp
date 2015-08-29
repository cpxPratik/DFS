#include <iostream>
#include <cstdlib>
using namespace std;

struct node {
	int info;
	struct node* next;
};

class stack {
	struct node* top;
public:
	stack();
	void push(int);
	int pop();
	bool isEmpty();
	void display();
};

stack::stack() {
	top = NULL;
}

void stack::push(int item) {
	node* n = new node;
	
	n->info = item;
	n->next = NULL;
	if (top != NULL) {
		n->next = top; //works as LIFO
	}
	top = n;
}

int stack::pop() {
	struct node* temp;
	int value;
	if (top == NULL) {
		cout << "\nThe stack is empty" << endl;
	}
	else {
		temp = top;
		top = top->next;
		value = temp->info;
		delete temp;
	}
//	return value;
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
	void addEdge(char edgeList[][3], int noOfEdges);
	void DFS(char start, char goal);
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
	delete[] nodeNames;
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

void graph::addEdge(char edgeList[][3], int noOfEdges) {
	int n1, n2, i, j;
	for (j = 0; j < noOfEdges; j++) {
		for (i = 0; i < noOfNodes; i++) {
			if (edgeList[j][0] == nodeNames[i]) {
				n1 = i; break;
			}
		}
		for (i = 0; i < noOfNodes; i++) {
			if (edgeList[j][1] == nodeNames[i]) {
				n2 = i;
			}
		}
		adjMatrix[n1][n2] = adjMatrix[n2][n1] = 1;
	}
}


void graph::DFS(char cStartNode, char cGoalNode) {
	int i, startNode, goalNode;
	for (i = 0; i < noOfNodes; i++) {
		if (nodeNames[i] == cStartNode) {
			startNode = i; break;
		}
	}
	for (i = 0; i < noOfNodes; i++) {
		if (nodeNames[i] == cGoalNode) {
			goalNode = i; break;
		}
	}
	stack s;
	//startNode--; goalNode--; // to directly use in visited array as index
	bool* visited = new bool[noOfNodes];
	
	int currentNode;
	for (i = 0; i < noOfNodes; i++) {
		visited[i] = false;
	}
	s.push(startNode);
	visited[startNode] = true;
	//if (startNode == goalNode) return;
	cout << "Depth First Search starting from node ";
	//cout << startNode+1 ;
	cout << nodeNames[startNode];
	cout << " : " << endl;
	while (!s.isEmpty())
	{
		currentNode = s.pop();
		//cout << currentNode+1;
		cout << nodeNames[currentNode];
		if (currentNode == goalNode) {
			cout << "\nGoal Node is found: " << nodeNames[goalNode]; //goalNode+1;
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
	char* nodes = "ABCDEFGHIJKLMNO";
	graph g(15, nodes);

	//g.addEdge(1, 2); g.addEdge(1, 3); g.addEdge(2, 4);
	//g.addEdge(2, 5); g.addEdge(3, 6); g.addEdge(3, 7);
	//g.addEdge('A', 'B'); g.addEdge('A', 'C'); g.addEdge('B', 'D');
	//g.addEdge('B', 'E'); g.addEdge('C', 'F'); g.addEdge('C', 'G');

	char edgeList[][3] = {
		//{ 'A', 'B' }, 'A', 'C', { 'B', 'D' }, {'B', 'E'} , 'C', 'F', 'C', 'G'
		"AB", "AC", "BD", "BE", "CF", "CG",
		"DH", "DI", "EJ", "EK", "FL", "FM",
		"GN", "GO"
	};

	g.addEdge(edgeList, 14);

	//g.DFS('A', 'N');
	char cStart, cGoal;
	cout << "Given nodes are \n";
	for (int i = 0; i < 15; i++)
		cout << nodes[i] << "\t";
	cout << "\n\nEdges of the connected graph are\n";
	for(int i = 0; i < 14; i++) {
		cout << edgeList[i][0] << "---" << edgeList[i][1] << "\t";
	}
	do {
		
		cout << "\nEnter Start node and Goal node within node A to node O :\n";
		cin >> cStart >> cGoal;
		cin.clear();
		//fflush(stdin);
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cStart = toupper(cStart);
		cGoal = toupper(cGoal);
	} while (cStart < 'A' || cStart > 'O' || cGoal < 'A' || cGoal > 'O');

	cout << endl;
	g.DFS(cStart, cGoal);
	cout << endl;
	system("pause");
	return 0;
}
