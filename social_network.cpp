#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Node {
    string data;
    vector<Node*> connections;

    Node(const string& value) : data(value) {}
};

void addConnection(Node* node1, Node* node2) {
    node1->connections.push_back(node2);
    node2->connections.push_back(node1);
}



vector<Node*> suggestFriends(Node* person) {
    vector<Node*> suggestions;

    vector<Node*>& connections = person->connections;
    int numConnections = connections.size();

    for (int i = 0; i < numConnections - 1; ++i) {
        Node* friend1 = connections[i];

        for (int j = i + 1; j < numConnections; ++j) {
            Node* friend2 = connections[j];
                
                int numConnections1 = connections.size();
                int numConnections2 = connections.size();

            for (Node* child1 : friend1->connections) {
                for (Node* child2 : friend2->connections) {
                    if (child1 == child2) {
                        suggestions.push_back(child1);
                    }
                }
            }
        }
    }

    return suggestions;
}




int binarySearch(const vector<Node*>& nodes, const string& name) {
    int left = 0;
    int right = nodes.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nodes[mid]->data == name) {
            return mid;
        } else if (nodes[mid]->data < name) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;  // Name not found
}

void bubbleSort(vector<Node*>& nodes) {
    int size = nodes.size();
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (nodes[j]->data > nodes[j + 1]->data) {
                // Swap the nodes
                Node* temp = nodes[j];
                nodes[j] = nodes[j + 1];
                nodes[j + 1] = temp;
            }
        }
    }
}

vector<string> pathFinder(Node* startNode, Node* endNode) {
    queue<pair<Node*, vector<string>>> bfsQueue;
    vector<Node*> visited;
    vector<string> path;

    bfsQueue.push({startNode, path});
    visited.push_back(startNode);

    while (!bfsQueue.empty()) {
        Node* currentNode = bfsQueue.front().first;
        path = bfsQueue.front().second;
        bfsQueue.pop();

        if (currentNode == endNode) {
            return path;
        }

        for (Node* connection : currentNode->connections) {
            if (find(visited.begin(), visited.end(), connection) == visited.end()) {
                vector<string> newPath = path;
                newPath.push_back(connection->data);
                bfsQueue.push({connection, newPath});
                visited.push_back(connection);
            }
        }
    }

    return {};  // No path found
}

vector<string> mutualFriends(Node* person1, Node* person2) {
    vector<string> commonFriends;

    for (Node* friend1 : person1->connections) {
        for (Node* friend2 : person2->connections) {
            if (friend1 == friend2) {
                commonFriends.push_back(friend1->data);
            }
        }
    }

    return commonFriends;
}

int main() {
    vector<Node*> nodes;
    int numNodes;

    cout << "Enter the number of persons: ";
    cin >> numNodes;
    cin.ignore();  // Ignore the newline character

    // Create the nodes
    for (int i = 0; i < numNodes; i++) {
        cout << "Enter the name for person " << i + 1 << ": ";
        string name;
        getline(cin, name);

        nodes.push_back(new Node(name));
    }

    // Sort the nodes vector in ascending order based on name using bubble sort
    bubbleSort(nodes);

    // Establish connections
    for (int i = 0; i < numNodes; i++) {
        cout << "Enter the number of connections for person " << nodes[i]->data << ": ";
        int numConnections;
        cin >> numConnections;
        cin.ignore();  // Ignore the newline character

        for (int j = 0; j < numConnections; j++) {
            cout << "Enter the name of the connected person " << j + 1 << ": ";
            string connectedName;
            getline(cin, connectedName);

            int connectedIndex = binarySearch(nodes, connectedName);
            if (connectedIndex != -1 && connectedIndex != i) {
                addConnection(nodes[i], nodes[connectedIndex]);
            } else {
                cout << "Invalid connected person name. Skipping connection." << endl;
            }
        }
    }

    // Search for a person by name
    string searchName;
    cout << "Enter the name of the person to search: ";
    getline(cin, searchName);

    int searchIndex = binarySearch(nodes, searchName);
    if (searchIndex != -1) {
        cout << "Person " << searchName << " found at index " << searchIndex + 1 << endl;
        cout << "Connections of " << searchName << ": " << endl;
        for (const auto& connection : nodes[searchIndex]->connections) {
            cout << " - " << connection->data << endl;
        }
    } else {
        cout << "Person " << searchName << " not found." << endl;
    }

    // Find the shortest path between two persons
    string person1, person2;
    cout << "Enter the name of the first person: ";
    getline(cin, person1);
    cout << "Enter the name of the second person: ";
    getline(cin, person2);

    int index1 = binarySearch(nodes, person1);
    int index2 = binarySearch(nodes, person2);

    if (index1 != -1 && index2 != -1) 
    {
        Node* startNode = nodes[index1];
        Node* endNode = nodes[index2];

        vector<string> shortestPath = pathFinder(startNode, endNode);

        if (!shortestPath.empty()) 
        {
            cout << "Shortest path between " << person1 << " and " << person2 << ":" << endl;
            for (const string& person : shortestPath) 
            {
                cout << " - " << person << endl;
            }
        }
        else 
        {
            cout << "No path found between " << person1 << " and " << person2 << "." << endl;
        }
    }   
    else
    {
        cout << "One or both of the person's names are invalid." << endl;
    }


    cout << "Enter the name of the first person for common friends: ";
    getline(cin, person1);
    cout << "Enter the name of the second person for common friends: ";
    getline(cin, person2);

    index1 = binarySearch(nodes, person1);
    index2 = binarySearch(nodes, person2);

        Node* Node11 = nodes[index1];
        Node* Node22 = nodes[index2];
        // Find mutual friends
        vector<string> commonFriends = mutualFriends(Node11, Node22);

        if (!commonFriends.empty()) {
            cout << "Mutual friends between " << person1 << " and " << person2 << ":" << endl;
            for (const string& friendName : commonFriends) {
                cout << " - " << friendName << endl;
            }
        } else {
            cout << "No mutual friends found between " << person1 << " and " << person2 << "." << endl;
        }
    


    cout << "Enter the name of the person for suggestions \n";
    getline(cin, person1);
    index1 = binarySearch(nodes, person1);
    Node11 = nodes[index1] ; 
    vector<Node*> friends = suggestFriends(Node11);

for (Node* child2 : friends) {
                    cout << child2->data<<"\n";
                }


    // Clean up memory
    for (Node* node : nodes) {
        delete node;
    }

    return 0;
    }
