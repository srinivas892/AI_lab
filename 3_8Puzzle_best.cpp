// 8 Puzzle Problem
// Best First Search

#include <iostream>
using namespace std;

struct PuzzleNode
{
    int board[9];
    char prevop;
    int blank;
    PuzzleNode *next;
    PuzzleNode *prev;
    int heuristic;
};

PuzzleNode *initial = nullptr, *goal = nullptr;
PuzzleNode *open = nullptr, *closed = nullptr, *steps;

void printNodeCount(PuzzleNode *list, const char *listName)
{
    int count = 0;
    PuzzleNode *temp = list;

    while (temp != nullptr)
    {
        count++;
        temp = temp->next;
    }

    cout << "Number of nodes in " << listName << ": " << count << endl;
}

int misplacedTiles(PuzzleNode *current, PuzzleNode *goal)
{
    int count = 0;
    for (int i = 0; i < 9; ++i)
    {
        if (current->board[i] != 0 && current->board[i] != goal->board[i])
        {
            ++count;
        }
    }
    return count;
}

void insertNode(PuzzleNode *prev, PuzzleNode *curr, char prevop, PuzzleNode *&list)
{
    PuzzleNode *newnode = new PuzzleNode;

    for (int i = 0; i < 9; i++)
        newnode->board[i] = curr->board[i];
    newnode->next = nullptr; // Initialize next pointer to nullptr
    newnode->blank = curr->blank;
    newnode->prev = prev;
    newnode->heuristic = misplacedTiles(curr, goal);
    newnode->prevop = prevop;

    PuzzleNode *itr = list, *prevnode = NULL;

    while (itr != NULL)
    {
        //cout<<"in while"<<endl;
        if (newnode->heuristic < itr->heuristic)
        {
            //cout<<"insert here"<<endl;
            if (prevnode != NULL)
                prevnode->next = newnode;
            newnode->next = itr;
            
            if(itr==list) list = newnode;
            itr = newnode;
            break;
        }
        prevnode = itr;
        itr = itr->next;
        
    }
    if (itr == NULL)
    {
        if (prevnode != NULL)
        {
            prevnode->next = newnode;
        }
        else
        {
            list = newnode;
        }
    }
}


PuzzleNode *deleteNode(PuzzleNode *&list)
{
    if (list == nullptr)
    {
        return nullptr;
    }
    PuzzleNode *minNode = list;
    list = list->next;
    return minNode;
}

void buildSteps(PuzzleNode *current)
{
    steps = nullptr;
    while (current != nullptr)
    {
        PuzzleNode *newStep = new PuzzleNode;
        for (int i = 0; i < 9; i++)
            newStep->board[i] = current->board[i];

        newStep->prevop = current->prevop;
        newStep->blank = current->blank;
        newStep->next = steps;

        steps = newStep;
        current = current->prev;
    }
}


void swap(PuzzleNode *curr, int a, int b)
{
    int temp = curr->board[a];
    curr->board[a] = curr->board[b];
    curr->board[b] = temp;
    curr->blank = b;
}

bool compareBoards(int *b1, int *b2)
{
    for (int i = 0; i < 9; i++)
        if (b1[i] != b2[i])
            return false;
    return true;
}

bool inList(PuzzleNode *current, PuzzleNode *list)
{
    struct PuzzleNode *temp = list;
    while (temp != NULL)
    {
        if (compareBoards(temp->board, current->board))
            return true;
        temp = temp->next;
    }
    return false;
}

bool findTargetBestFirst()
{
    insertNode(NULL, initial, '\0', open);
    // printNodeCount(open, "open");
    PuzzleNode *current = open, *parent = NULL;
    int hvalue;
    while (open != nullptr)
    {
        current = deleteNode(open);
        // printNodeCount(open, "open");
        insertNode(current->prev, current, current->prevop, closed);
        // printNodeCount(closed, "clo");
        parent = current;
        if (current->heuristic == 0){
            buildSteps(current);
            return true;
        }

        if (!(current->blank < 3) && current->prevop != 'D') // UP
        {
            // cout << "UP" << endl;
            // cout << current->blank << " " << current->blank - 3 << " " << endl;
            swap(current, current->blank, current->blank - 3);
            // for (int i = 0; i < 9; i++)
            //     cout << current->board[i] << " ";
            // cout << hvalue << endl;
            // cout << inList(current, open) << endl;
            // cout << inList(current, closed) << endl;
            if (!inList(current, open) && !inList(current, closed))
            {
                insertNode(parent, current, 'U', open);
                // printNodeCount(open, "open");
            }
            swap(current, current->blank, current->blank + 3);
        }

        if (!(current->blank > 5) && current->prevop != 'U') // DOWN
        {
            // cout << "DOWN" << endl;
            swap(current, current->blank, current->blank + 3);
            if (!inList(current, open) && !inList(current, closed))
            {
                insertNode(parent, current, 'D', open);
                // printNodeCount(open, "open");
            }
            swap(current, current->blank, current->blank - 3);
        }

        if ((current->blank % 3 != 0) && current->prevop != 'R') // LEFT
        {
            //cout << "LEFT" << endl;
            swap(current, current->blank, current->blank - 1);
           if (!inList(current, open) && !inList(current, closed))
            {
                insertNode(parent, current, 'L', open);
                // printNodeCount(open, "open");
            }
            swap(current, current->blank, current->blank + 1);
        }

        if (((current->blank + 1) % 3 != 0) && current->prevop != 'L') // RIGHT
        {
            // cout << "RIGHT" << endl;
            swap(current, current->blank, current->blank + 1);
            if (!inList(current, open) && !inList(current, closed))
            {
                insertNode(parent, current, 'R', open);
                // printNodeCount(open, "open");
            }
            swap(current, current->blank, current->blank - 1);
        }
        cout << "Boards in open" << endl;
        PuzzleNode *temp = open;
        while (temp != nullptr)
        {
            cout<<temp->prevop<<endl;
            for (int i = 0; i < 9; i++)
            {
                cout << temp->board[i] << " ";
                if (i % 3 == 2)
                    cout << " " << endl;
            }
            cout << endl;
            temp = temp->next;
        }
        cout << "---------------------------------------------" << endl;

        cout << "Boards in closed" << endl;
        temp = closed;
        while (temp != nullptr)
        {
            cout<<temp->prevop<<endl;
            for (int i = 0; i < 9; i++)
            {
                cout << temp->board[i] << " ";
                if (i % 3 == 2)
                    cout << " " << endl;
            }
            cout << endl;
            temp = temp->next;
        }
        cout << "---------------------------------------------" << endl;
        //int x;
        //cin >> x;
    }

    return false;
}

void freeMemory(struct PuzzleNode *node)
{
    if (node == NULL)
        return;
    freeMemory(node->next);
    delete node;
}

void printSteps()
{
    struct PuzzleNode *temp = steps;
    while (temp != NULL)
    {
        switch (temp->prevop)
        {
        case 'U':
            cout << "Move UP" << endl;
            break;
        case 'D':
            cout << "Move DOWN" << endl;
            break;
        case 'L':
            cout << "Move LEFT" << endl;
            break;
        case 'R':
            cout << "Move RIGHT" << endl;
            break;
        default:
            break;
        }
        for (int i = 0; i < 9; i = i + 3)
            cout << temp->board[i] << " " << temp->board[i + 1] << " " << temp->board[i + 2] << endl;
        temp = temp->next;
    }
}

int main()
{
    initial = new PuzzleNode;
    cout << "Enter initial state (0 for blank): ";
    // int tempb[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    // for (int i = 0; i < 9; ++i)
    // {
    //     initial->board[i] = tempb[i];
    // }
    initial->blank = 8;
    for (int i = 0; i < 9; i++)
        cin >> initial->board[i];
    // Initialize the initial node

    for (int i = 0; i < 9; i++)
    {
        if (initial->board[i] == 0)
            initial->blank = i;
    }
    // for(int i=0; i<9; i++) initial->board[i] = i+1;
    // initial->board[8] = 0;
    // initial->blank = 8;
    initial->prevop = '\0';
    initial->next = NULL;

    cout << "Enter goal state (0 for blank): ";
    goal = new PuzzleNode;
    for (int i = 0; i < 9; i++)
        cin >> goal->board[i];
    for (int i = 0; i < 9; i++)
    {
        if (goal->board[i] == 0)
            goal->blank = i;
    }
    //int tempb1[] = {1, 2, 3, 0, 5, 6, 4, 7, 8};
    // for (int i = 0; i < 9; ++i)
    // {
    //     goal->board[i] = tempb1[i];
    // }
    goal->blank = 3;
    goal->prevop = '\0';
    goal->heuristic = 0;
    initial->heuristic = misplacedTiles(initial, goal);
    goal->next = NULL;

    cout << endl;

    if (findTargetBestFirst())
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
    freeMemory(initial);
    freeMemory(goal);
    freeMemory(open);
    freeMemory(closed);

    return 0;
}
