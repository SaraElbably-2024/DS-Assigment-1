#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class Process {
public:
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;

    Process(int id, int arrival, int burst) {
        this->id = id;
        this->arrivalTime = arrival;
        this->burstTime = burst;
        this->remainingTime = burst;
        this->completionTime = 0;
        this->turnaroundTime = 0;
        this->waitingTime = 0;
    }

    void calculateMetrics(int finishTime) {
        completionTime = finishTime;
        turnaroundTime = completionTime - arrivalTime;
        waitingTime = turnaroundTime - burstTime;
    }
};

class RoundRobinScheduler {
private:
    vector<Process> processes;
    int quantum;
    int currentTime;

    void printQueue(queue<int> q) {
        if (q.empty()) {
            cout << "\n[ Empty ]\n";
            return;
        }
        cout << "\n[ ";
        while (!q.empty()) {
            cout << "p" << processes[q.front()].id;
            q.pop();
            if (!q.empty()) cout << ", ";
        }
        cout << " ]";
    }

public:
    RoundRobinScheduler(int q) : quantum(q), currentTime(0) {}

    void addProcess(int id, int arrival, int burst) {
        processes.push_back(Process(id, arrival, burst));
    }

    void execute() {
        
        sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
            return a.arrivalTime < b.arrivalTime;
        });

        queue<int> readyQueue; // stores IDs of processes
        int completed = 0;
        int NumOfProcesses = processes.size();
        int nextIdx = 0;

        while (completed < NumOfProcesses) {
            // push processes' IDs in ReadyQueue if its arrival time < current time
            while (nextIdx < NumOfProcesses && processes[nextIdx].arrivalTime <= currentTime) {
                readyQueue.push(nextIdx);
                nextIdx++;
            }

            // if there aren't ready processes, increase current time to the next processes' arrival time
            // no need to check if there are processes or not cuz we wouldn't be here if there aren't processes
            if (readyQueue.empty()) {
                currentTime = processes[nextIdx].arrivalTime;
                continue;
            }

            // get the current process to excute 
            // update current time , remaining time
            int currentIdx = readyQueue.front();
            Process& currentProcess = processes[(currentIdx)];
            readyQueue.pop();

            int timeToSpend = min(currentProcess.remainingTime, quantum);
            currentTime += timeToSpend; // current time = past time + spentTime to excute
            currentProcess.remainingTime -= timeToSpend; // Remaining time = Remaining time for the process - spentTime to excute

            // ensure if there are processes arrived during excuting the current process or not
            while (nextIdx < NumOfProcesses && currentProcess.arrivalTime <= currentTime) {
                readyQueue.push(nextIdx);
                nextIdx++;
            }

             // if process didn't be finished yet , turn it back to Ready Queue
             // if finished, update completion_time, turnround_time, waiting_time and completed processes
            if (currentProcess.remainingTime > 0) {
                readyQueue.push(currentIdx);
            } else {
                completed++;
                currentProcess.calculateMetrics(currentTime);
            }

            printQueue(readyQueue);
        }
        displayResults();
    }

    void displayResults() {
        int totalWait = 0;
        cout<<"Process        Completion Time        Turnaround Time        Waiting Time" << endl;
        for(const auto& p : processes){
            cout<<"p"<<p.id << "             " << p.completionTime
            << "                      " << p.turnaroundTime
            << "                      " << p.waitingTime << endl << endl; 
            totalWait += p.waitingTime;
        } 

        cout << "Average Waiting Time: " << (float)totalWait / processes.size() << endl;
    }
};

int main() {
    int num, qt;
    cout << "How many processes? ";
    cin >> num;
    cout << "Quantum Time: ";
    cin >> qt;

    RoundRobinScheduler scheduler(qt);

    for (int i = 0; i < num; i++) {
        int arrival, burst;
        cout << "Enter Arrival and Burst for P" << (i + 1) << ": ";
        cin >> arrival >> burst;
        scheduler.addProcess(i + 1, arrival, burst);
    }

    scheduler.execute();

    return 0;
}
