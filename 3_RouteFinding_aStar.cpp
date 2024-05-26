#include <iostream>
using namespace std;

struct GraphNode
{
    char name;
    GraphNode *listnext; // next node in list
    GraphNode *adjnext;  // adjacent nodes to the given node
    int wt;
    int heuristics;
};

struct Node
{
    char name;
    int wt;
    int g;
    int h;
    Node *next;
    Node *prev;
};

GraphNode *adjlist = NULL;
Node *open = NULL, *closed = NULL, *steps = NULL;

void insertNodeinList(char nodename, bool initialInsertion, char parent, int wt, int hvalue)
{
    if (initialInsertion)
    {
        if (adjlist == NULL)
        {
            adjlist = new GraphNode;
            adjlist->name = nodename;
            adjlist->adjnext = NULL;
            adjlist->listnext = NULL;
            adjlist->wt = -1;
            adjlist->heuristics = hvalue;
        }
        else
        {
            GraphNode *temp = adjlist;
            while (temp->listnext != NULL)
            {
                temp = temp->listnext;
            }
            temp->listnext = new GraphNode;
            temp->listnext->name = nodename;
            temp->listnext->adjnext = NULL;
            temp->listnext->listnext = NULL;
            temp->listnext->wt = -1;
            temp->listnext->heuristics = hvalue;
        }
    }
    else
    {
        GraphNode *temp = adjlist;

        // Find the parent node
        while (temp->name != parent && temp->listnext != NULL)
            temp = temp->listnext;

        // If parent node not found, return
        if (temp->name != parent)
        {
            cerr << "Parent node not found: " << parent << endl;
            return;
        }

        int h = temp->heuristics;

        // find given node
        GraphNode *temp2 = adjlist;

        // Find the parent node
        while (temp2->name != nodename && temp2->listnext != NULL)
            temp2 = temp2->listnext;

        // If parent node not found, return
        if (temp2->name != nodename)
        {
            cerr << " node not found: " << nodename << endl;
            return;
        }

        // Insert the new node into the adjacency list of the parent
        if (temp->adjnext == NULL)
        {
            temp->adjnext = new GraphNode;
            temp->adjnext->name = nodename;
            temp->adjnext->adjnext = NULL;
            temp->adjnext->listnext = NULL;
            temp->adjnext->wt = wt;
            temp->adjnext->heuristics = temp2->heuristics; // Set proper value for heuristics
        }
        else
        {
            GraphNode *adjTemp = temp->adjnext;
            while (adjTemp->adjnext != NULL)
                adjTemp = adjTemp->adjnext;

            adjTemp->adjnext = new GraphNode;
            adjTemp->adjnext->name = nodename;
            adjTemp->adjnext->adjnext = NULL;
            adjTemp->adjnext->listnext = NULL;
            adjTemp->adjnext->wt = wt;
            adjTemp->adjnext->heuristics = temp2->heuristics; // Set proper value for heuristics
        }

        // Insert the parent node into the adjacency list of the given node
        if (temp2->adjnext == NULL)
        {
            temp2->adjnext = new GraphNode;
            temp2->adjnext->name = parent;
            temp2->adjnext->adjnext = NULL;
            temp2->adjnext->listnext = NULL;
            temp2->adjnext->wt = wt;
            temp2->adjnext->heuristics = h; // Set proper value for heuristics
        }
        else
        {
            GraphNode *adjTemp = temp2->adjnext;
            while (adjTemp->adjnext != NULL)
                adjTemp = adjTemp->adjnext;

            adjTemp->adjnext = new GraphNode;
            adjTemp->adjnext->name = parent;
            adjTemp->adjnext->adjnext = NULL;
            adjTemp->adjnext->listnext = NULL;
            adjTemp->adjnext->wt = wt;
            adjTemp->adjnext->heuristics = h; // Set proper value for heuristics
        }
    }
}

void printGraph()
{
    GraphNode *temp = adjlist;
    while (temp != NULL)
    {
        cout << temp->name << " : -> ";
        GraphNode *adjTemp = temp->adjnext;
        while (adjTemp != NULL)
        {
            cout << adjTemp->name << "(" << adjTemp->wt << ")";
            if (adjTemp->adjnext != NULL)
            {
                cout << "->";
            }
            adjTemp = adjTemp->adjnext;
        }
        cout << endl;
        temp = temp->listnext;
    }
}

Node *deleteNode(Node *&list)
{
    if (list == NULL)
    {
        return NULL;
    }
    Node *minNode = list;
    list = list->next;
    return minNode;
}

bool inList(char nodeName, Node *&list)
{
    Node *temp = list;
    while (temp != NULL)
    {
        if (temp->name == nodeName)
            return true;
        temp = temp->next;
    }
    return false;
}

void insertNode(Node *prev, char nodeName, int wt, int h, Node *&list)
{
    Node *newNode = new Node;
    newNode->name = nodeName;
    newNode->wt = wt;
    newNode->h = h;
    newNode->next = NULL;
    newNode->prev = prev;

    if (prev != NULL)
        newNode->g = prev->g + wt;
    else
        newNode->g = 0;

    if (list == NULL || (newNode->h + newNode->g) < (list->h + list->g))
    {
        newNode->next = list;
        list = newNode;
        return;
    }

    Node *itr = list;

    while (itr->next != NULL && (itr->next->h + itr->next->g) <= (newNode->h + newNode->g))
    {
        itr = itr->next;
    }

    newNode->next = itr->next;
    itr->next = newNode;
}


void printExistingNeightbours(GraphNode *node)
{
    cout << "Current Existing neighbours of " << node->name << " in adjacency list are: ";
    GraphNode *temp = node->adjnext;
    while (temp != NULL)
    {
        cout << temp->name << "(" << temp->wt << "), ";
        temp = temp->adjnext;
    }
    cout << endl;
}

void printExistingNodes(Node *list)
{
    Node *temp = list;
    while (temp != NULL)
    {
        cout << temp->name << " ";
        temp = temp->next;
    }
    cout << endl;
}

bool findTargetAStar(char source, char destination)
{
    insertNode(NULL, source, 0, 0, open);

    while (open != NULL)
    {
        Node *current = deleteNode(open);
        insertNode(current, current->name, current->wt, current->h, closed);

        if (current->name == destination)
        {
            steps = NULL;
            while (current != NULL)
            {
                if(steps==NULL)
                {
                    steps = new Node;
                    steps->name = current->name;
                    steps->wt = current->wt;
                }
                else
                {
                    Node *newnode = new Node;
                    newnode->name = current->name;
                    newnode->wt = current->wt;
                    newnode->next = steps;
                    steps = newnode;
                }
                current = current->prev;
            }
            return true;
        }
        else
        {
            GraphNode *adj = adjlist;
            while (adj->name != current->name)
                adj = adj->listnext;
            adj = adj->adjnext;
            while (adj != NULL)
            {
                int g = current->g + adj->wt;
                int h = adj->heuristics;

                if (!inList(adj->name, open) && !inList(adj->name, closed))
                    insertNode(current, adj->name, adj->wt, h, open);
                else if (inList(adj->name, open))
                {
                    Node *existingNode = open;
                    while (existingNode != NULL && existingNode->name != adj->name)
                    {
                        existingNode = existingNode->next;
                    }
                    if (existingNode == NULL || (existingNode->g + existingNode->h) > (g + h))
                    {
                        // Update or insert node with a lower total cost
                        insertNode(current, adj->name, adj->wt, h, open);
                    }
                }

                adj = adj->adjnext;
            }
        }

        cout << "Open List: ";
        printExistingNodes(open);
        cout << "Closed List: ";
        printExistingNodes(closed);
    }

    return false;
}

void freeMemory(Node *&node)
{
    if (node == NULL)
        return;
    freeMemory(node->next);
    delete node;
    node = NULL; // Set the pointer to NULL after deletion
}

void printSteps()
{
    Node *temp = steps;
    int totalCost = 0;

    cout << "Steps from source to destination:" << endl;

    while (temp != NULL)
    {
        cout << "Node: " << temp->name << " | Cost: " << temp->wt << endl;
        totalCost += temp->wt;
        temp = temp->next;
    }
    cout << "Total Cost to reach destination: " << totalCost << endl;
}

int main()
{
    int numvertices, numadj, wt, hvalue;
    char nodename, source, destination;
    cout << "Enter number of nodes in the graph: ";
    cin >> numvertices;
    cout << "Enter character of nodes and hValue (straight line distance): " << endl;
    for (int i = 0; i < numvertices; i++)
    {
        cout << "Enter for node " << i + 1 << " ";
        cin >> nodename >> hvalue;
        insertNodeinList(nodename, true, '\0', -1, hvalue);
    }

    cout << "Enter source and destination: ";
    cin >> source >> destination;

    GraphNode *temp = adjlist;

    for (int i = 0; i < numvertices; i++)
    {
        printExistingNeightbours(temp);
        cout << "\nEnter additional number of nodes adjacent to " << temp->name << ": ";
        cin >> numadj;
        for (int j = 0; j < numadj; j++)
        {
            cout << "Enter name of adjacent node and weight " << j + 1 << ": ";
            cin >> nodename >> wt;
            insertNodeinList(nodename, false, temp->name, wt, -1);
        }
        temp = temp->listnext;
    }
    printGraph();

    if (findTargetAStar(source, destination))
    {
        cout << endl
             << "Solution found" << endl
             << endl;
        printSteps();
    }
    else
    {
        cout << endl
             << "No Solution found" << endl
             << endl;
    } 

    // Free allocated memory
    freeMemory(open);
    freeMemory(closed);

    return 0;
}
