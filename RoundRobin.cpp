#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

struct process{
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnround_time;
    int waiting_time;
};

void PrintQueue(queue<int> q){
    if(q.empty()){
        cout << endl << "[ Empty ]" << endl << endl;
        return;
    }
    cout << endl << "[ ";
    while(!q.empty()){
        cout<< "p" <<(q.front() + 1);
        q.pop();
        if (!q.empty()) cout<< ", " ;
    }
    cout<< " ]";
}

void RoundRobin(vector<process>& processes, int QuantumTime){
    sort(processes.begin(), processes.end(), [](const process& a, const process& b){return a.arrival_time < b.arrival_time;});
    queue<int> ReadyQueue; // stores IDs of processes
    int currentTime = 0;
    int completed = 0;
    int NumOfProcesses = processes.size();
    int IdxNextProcess = 0;

    while(completed < NumOfProcesses){
        // push processes' IDs in ReadyQueue if its arrival time < current time
        while((IdxNextProcess < NumOfProcesses) && (processes[IdxNextProcess].arrival_time <= currentTime)){
            ReadyQueue.push(IdxNextProcess);
            IdxNextProcess++;
        }

        // if there aren't ready processes, increase current time to the next processes' arrival time
        // no need to check if there are processes or not cuz we wouldn't be here if there aren't processes
        if(ReadyQueue.empty()){
            currentTime = processes[IdxNextProcess].arrival_time;
            continue;
        }

        // get the current process to excute 
        // update current time , remaining time
        int currentIdx = ReadyQueue.front(); 
        process& currentProcess = processes[(currentIdx)];
        ReadyQueue.pop();

        int TimeToSpend = min(currentProcess.remaining_time, QuantumTime);
        currentTime += TimeToSpend; // current time = past time + spentTime to excute
        currentProcess.remaining_time -= TimeToSpend ; // Remaining time = Remaining time for the process - spentTime to excute
        

        // ensure if there are processes arrived during excuting the current process or not
        while((IdxNextProcess < NumOfProcesses) && (processes[IdxNextProcess].arrival_time <= currentTime)){
            ReadyQueue.push(IdxNextProcess);
            IdxNextProcess++;
        }

        // if process didn't be finished yet , turn it back to Ready Queue
        if(currentProcess.remaining_time > 0){
            ReadyQueue.push(currentIdx);
        }
        // if finished, update completion_time, turnround_time, waiting_time and completed processes
        else{
            completed++;
            currentProcess.completion_time = currentTime;
            currentProcess.turnround_time = currentProcess.completion_time - currentProcess.arrival_time;
            currentProcess.waiting_time = currentProcess.turnround_time - currentProcess.burst_time;
        }

        PrintQueue(ReadyQueue);
    }

    cout<<"Process        Completion Time        Turnaround Time        Waiting Time" << endl;
    for(int i =0; i<NumOfProcesses; i++){
        cout<<"p"<<processes[i].id << "             " << processes[i].completion_time
        << "                      " << processes[i].turnround_time
        << "                      " << processes[i].waiting_time << endl << endl; 
    } 
    
    int sumWaitTime = 0;
    for(int i =0; i<NumOfProcesses; i++){
        sumWaitTime += processes[i].waiting_time;
    } 
    cout << "Average Waiting Time: " <<sumWaitTime / (float)NumOfProcesses << endl;
}

int main(){
    vector<process> processes;
    int Num;
    cout<< "How many processes will be excuted?" << endl;
    cin>> Num;

    int QT;
    cout<< endl << "what is the Quantum Time ?" << endl;
    cin >> QT;

    for(int i = 0; i < Num; i++){
        int id = i+1;
        int arrival, burst;

        cout << endl << "Enter Arrival and Needed time for P" << id << ": " ;
        cin >> arrival >> burst;

        processes.push_back({id, arrival, burst, burst});
    }

    RoundRobin(processes, QT);

    return 0;

}