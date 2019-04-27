#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

//bank event variables
class Event {
private:
    string type;
    int eventTime;
    int eventLength;

public:
    //constructor
    Event(string type, int eventTime, int eventLength) : type(type), eventTime(eventTime), eventLength(eventLength) {
    }

    string getType() const {
        return type;
    }

    int getEventTime() const {
        return eventTime;
    }

    int getEventLength() const{
        return eventLength;
    }
};


bool tellerAvailable = true;
int currentTime = 0;

struct Compare {
    bool operator()(const Event& lhs, const Event& rhs) const {
        return lhs.getEventTime() > rhs.getEventTime();
    }
};

//update bank line
void processArrival(Event event, priority_queue<Event, vector<Event>, Compare> &eventQueue, queue<Event> &bankLine) {
    eventQueue.pop();
    if(bankLine.size() == 0 && tellerAvailable) {
        int departureTime = currentTime + event.getEventLength();
        Event departureEvent("depart", departureTime, event.getEventLength());
        eventQueue.emplace(departureEvent);
        tellerAvailable = false;
    } else {
        bankLine.emplace(event);
    }
}

void processDeparture(Event event, priority_queue<Event, vector<Event>, Compare> &eventQueue, queue<Event> &bankLine) {
    eventQueue.pop();
    if(bankLine.size() != 0) {
        event = bankLine.front();
        bankLine.pop();
        int departureTime = currentTime + event.getEventLength();
        Event departureEvent("depart", departureTime, event.getEventLength());
        eventQueue.emplace(departureEvent);
    } else {
        tellerAvailable = true;
    }
}

void simulate() {
    queue<Event> bankLine;
    priority_queue<Event, vector<Event>, Compare> eventQueue;

    //read data from textfile
    ifstream data{"input.txt"};
    if (!data) {
        cerr << "Error opening input.txt..." << std::endl;
        return;
    }

    int start;
    int eventLength;

    //assign data in textfile to variables
    while (data >> start >> eventLength) {
        Event event("arrive", start, eventLength);
        eventQueue.emplace(event);
    }

    while(eventQueue.size() > 0) {
        Event event = eventQueue.top();
        currentTime = event.getEventTime();

        if(event.getType().compare("arrive") == 0) {
            cout << "Processing an arrival event at time: " << currentTime << endl;
            processArrival(event, eventQueue, bankLine);
        } else {
            cout << "Processing a departure event at time: " << currentTime << endl;
            processDeparture(event, eventQueue, bankLine);
        }
    }
}

int main() {
    cout << "Simulation begins" << endl;
    simulate();
    return 0;
}