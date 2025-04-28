#ifndef ali_H
#define ali_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int timeToMinutes(const string& time) {
    int hours = stoi(time.substr(0, 2)); // Extract hours
    int minutes = stoi(time.substr(3, 2)); // Extract minutes
    return hours * 60 + minutes; // Convert to total minutes
}

class Queue {
    struct Node {
        Edge* path[11]; // Store a path of up to 11 flights
        int pathSize;   // Number of flights in the path
        Node* next;
    };

    Node* front; // Points to the first node
    Node* rear;  // Points to the last node

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(Edge* path[], int pathSize) {
        Node* newNode = new Node;
        for (int i = 0; i < pathSize; i++) {
            newNode->path[i] = path[i];
        }
        newNode->pathSize = pathSize;
        newNode->next = nullptr;

        if (rear == nullptr) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void dequeue(Edge* outputPath[], int& pathSize) {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty!");
        }

        Node* temp = front;
        pathSize = temp->pathSize;
        for (int i = 0; i < pathSize; i++) {
            outputPath[i] = temp->path[i];
        }

        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
    }

    ~Queue() {
        while (!isEmpty()) {
            int dummySize;
            Edge* dummyPath[11];
            dequeue(dummyPath, dummySize);
        }
    }
};


////////////////////// CLASS EDGE //////////////////////
class Edge {
public:
    string date;
    int departure_time; // Stored in minutes
    int arrival_time;   // Stored in minutes
    int ticket_price;
    string airline;

    Edge() {}

    Edge(string dt, int dep_time, int arr_time, int price, string air) {
        this->date = dt;
        this->departure_time = dep_time;
        this->arrival_time = arr_time;
        this->ticket_price = price;
        this->airline = air;
    }

    void printDetails() const {
        cout << "Date: " << date << "\n"
            << "Departure Time: " << departure_time << " mins\n"
            << "Arrival Time: " << arrival_time << " mins\n"
            << "Ticket Price: " << ticket_price << "\n"
            << "Airline: " << airline << "\n";
    }
};

////////////////////// CLASS NODE //////////////////////
class Node {
public:
    string dest;   // Destination city
    Edge* flight;  // Pointer to flight details (Edge)
    Node* next;    // Pointer to the next node

    Node(string d, Edge* f) : dest(d), flight(f), next(nullptr) {}
};

///////////////////// CLASS LINKED LIST /////////////////////
class LinkedList {
public:
    Node* head; // Pointer to the head of the list
    Node* tail; // Pointer to the tail of the list

    LinkedList() : head(nullptr), tail(nullptr) {}

    void insert(const string& dest, Edge* flight) {
        Node* newNode = new Node(dest, flight);
        if (!head) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void print() const {
        Node* temp = head;
        while (temp) {
            cout << "Destination: " << temp->dest << "\n";
            temp->flight->printDetails();
            cout << endl;
            temp = temp->next;
        }
    }
};

///////////////////// CLASS GRAPH /////////////////////
class Graph {
public:
    int vertices;
    string* cities;
    LinkedList* adjList;

    Graph(int v) {
        vertices = v;
        cities = new string[v];
        adjList = new LinkedList[v];
    }

    void addCity(const string& fileName) {
        ifstream file(fileName);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << fileName << endl;
            return;
        }

        string line, cityName;
        int count = 0;

        while (getline(file, line) && count < vertices) {
            stringstream ss(line);
            ss >> cityName; // Extract city name, ignoring the fees
            cities[count++] = cityName;
        }

        if (count != vertices) {
            cerr << "Error: Number of cities in file does not match the expected number of vertices." << endl;
        }

        file.close();
    }

    void insertEdge(const string& origin, const string& dest, const string& date, int dep_time, int arr_time, int price, const string& airline) {
        int srcIndex = findCityIndex(origin);
        int destIndex = findCityIndex(dest);

        if (srcIndex != -1 && destIndex != -1) {
            Edge* flight = new Edge(date, dep_time, arr_time, price, airline);
            adjList[srcIndex].insert(dest, flight);
        }
        else {
            cout << "Invalid cities: " << origin << " or " << dest << endl;
        }
    }

    void addEdgesFromFile(const string& fileName) {
        ifstream file(fileName);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << fileName << endl;
            return;
        }

        string line, origin, dest, date, dep_time_str, arr_time_str, airline;
        int ticket_price;

        while (getline(file, line)) {
            stringstream ss(line);
            ss >> origin >> dest >> date >> dep_time_str >> arr_time_str >> ticket_price >> airline;

            // Convert time strings to minutes
            int dep_time = timeToMinutes(dep_time_str);
            int arr_time = timeToMinutes(arr_time_str);

            // Insert the edge into the graph
            insertEdge(origin, dest, date, dep_time, arr_time, ticket_price, airline);
        }

        file.close();
    }

    int findCityIndex(const string& city) const {
        for (int i = 0; i < vertices; i++) {
            if (cities[i] == city) {
                return i;
            }
        }
        return -1;
    }

    void printGraph() const {
        for (int i = 0; i < vertices; i++) {
            cout << "-----------------" << endl;
            cout << cities[i] << ": " << endl;
            cout << "-----------------" << endl;
            adjList[i].print();
            cout << endl;
        }
    }

    //////////////////// DFS Function ////////////////////
    void dfsBookingAllPathFinder(int current, int destination, bool visited[], string path[], int pathIndex, Edge* prevFlight, Edge* flightDetails[], Edge* allPaths[][10], int* pathCounts, int& totalPaths) {
        visited[current] = true; // Mark current city as visited
        path[pathIndex] = cities[current]; // Add current city to the path
        flightDetails[pathIndex] = prevFlight; // Add flight details for the current path segment
        pathIndex++; // Move to the next position in the path

        // If destination is reached, save the path
        if (current == destination) {
            for (int i = 1; i < pathIndex; i++) { // Start from 1 to skip the origin city
                allPaths[totalPaths][i - 1] = flightDetails[i];
            }
            pathCounts[totalPaths] = pathIndex - 1;
            totalPaths++;
            visited[current] = false; // Backtrack
            return;
        }

        // Traverse all adjacent cities (neighbors)
        Node* neighbor = adjList[current].head;
        while (neighbor) {
            int nextCityIndex = findCityIndex(neighbor->dest);
            Edge* currentFlight = neighbor->flight;

            // Layover and revisit checks
            if (!visited[nextCityIndex] && (prevFlight == nullptr || isValidLayover(prevFlight, currentFlight))) {
                dfsBookingAllPathFinder(nextCityIndex, destination, visited, path, pathIndex, currentFlight, flightDetails, allPaths, pathCounts, totalPaths);
            }

            neighbor = neighbor->next;
        }

        visited[current] = false; // Backtrack
    }


    void BookingAllPathFlightsFinder(const string& origin, const string& destination, Edge* allPaths[][10], int* pathCounts, int& totalPaths) {
        int srcIndex = findCityIndex(origin);
        int destIndex = findCityIndex(destination);

        // Ensure both origin and destination are valid cities
        if (srcIndex == -1 || destIndex == -1) {
            cout << "Invalid origin or destination city!" << endl;
            return;
        }

        // Prepare visited array and path tracker
        bool visited[11] = { false }; // Mark all cities as unvisited
        string path[11];            // To store the current path
        Edge* flightDetails[11] = { nullptr }; // To store flight details for the path

        // Perform DFS to find and print all valid paths
        cout << "Searching for flights from " << origin << " to " << destination << "...\n";
        dfsBookingAllPathFinder(srcIndex, destIndex, visited, path, 0, nullptr, flightDetails, allPaths, pathCounts, totalPaths);

        cout << "Search completed.\n";
    }


    //////////////////// Helper Function for Layover Validation ////////////////////
    bool isValidLayover(const Edge* prevFlight, const Edge* nextFlight) {
        // Check if dates are valid
        if (nextFlight->date < prevFlight->date) return false;

        // If flights are on the same day, validate arrival and departure times
        if (nextFlight->date == prevFlight->date) {
            if (prevFlight->arrival_time >= nextFlight->departure_time) return false;

            // Ensure at least 60 minutes layover time
            int layoverTime = nextFlight->departure_time - prevFlight->arrival_time;
            if (layoverTime < 60) return false;
        }

        // If departure time is less than arrival time, it indicates a date change
        if (prevFlight->departure_time > prevFlight->arrival_time) {
            if (nextFlight->date <= prevFlight->date) return false;
        }

        return true;
    }

};

////////////////////// MAIN FUNCTION //////////////////////
int main() {
    // Create a graph with 11 cities
    Graph flightGraph(11);

    // Read city names from the file and add them as vertices
    flightGraph.addCity("HotelCharges_perday.txt");

    // Add flights from a file
    flightGraph.addEdgesFromFile("Flights.txt");

    // Search for flights
    string origin, destination;
    cout << "Enter origin city: ";
    cin >> origin;
    cout << "Enter destination city: ";
    cin >> destination;

    cout << "Possible paths:\n";

    // Dynamically allocate arrays to store paths
    const int maxPaths = 100; // Maximum number of paths
    Edge* allPaths[maxPaths][10] = { nullptr }; // Array of paths (each path can have up to 10 flights)
    int pathCounts[maxPaths] = { 0 };          // Array to store the number of flights in each path
    int totalPaths = 0;                      // Total number of valid paths

    flightGraph.BookingAllPathFlightsFinder(origin, destination, allPaths, pathCounts, totalPaths);

    // Allow the user to book a flight
    if (totalPaths > 0) {
        cout << "\nAvailable flight paths:\n";
        for (int i = 0; i < totalPaths; i++) {
            cout << "Path " << i + 1 << ":\n";
            for (int j = 0; j < pathCounts[i]; j++) {
                allPaths[i][j]->printDetails();
                cout << endl;
            }
            cout << "-----------------------------\n";
        }

        int choice;
        cout << "Enter the number of the path you want to book (1-" << totalPaths << "): ";
        cin >> choice;

        if (choice > 0 && choice <= totalPaths) {
            ofstream bookingFile("booking.txt", ios::app);
            if (bookingFile.is_open()) {
                bookingFile << "Booked Flight Details:\n";
                for (int j = 0; j < pathCounts[choice - 1]; j++) {
                    Edge* flight = allPaths[choice - 1][j];
                    bookingFile << "Date: " << flight->date << "\n"
                        << "Departure Time: " << flight->departure_time << " mins\n"
                        << "Arrival Time: " << flight->arrival_time << " mins\n"
                        << "Ticket Price: " << flight->ticket_price << "\n"
                        << "Airline: " << flight->airline << "\n";
                    bookingFile << "-----------------------------\n";
                }
                bookingFile.close();
                cout << "Booking confirmed! Details have been saved to booking.txt.\n";
            }
            else {
                cerr << "Error: Could not open booking.txt for writing.\n";
            }
        }
        else {
            cout << "Invalid choice. No flight booked.\n";
        }
    }
    else {
        cout << "No flights available between the specified cities.\n";
    }

    return 0;
}

#endif