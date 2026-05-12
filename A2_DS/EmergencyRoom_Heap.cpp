#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Patient {
    int id;
    string name;
    int severity;
    int arrivalTime;
};

class EEPrioritySystem {
private:
    vector<Patient> heap;

    bool hasHigherPriority(Patient p1, Patient p2) {
        if (p1.severity != p2.severity)
            return p1.severity > p2.severity; 
        return p1.arrivalTime < p2.arrivalTime;
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (hasHigherPriority(heap[index], heap[parent])) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else break;
        }
    }

    void heapifyDown(int index) {
        int priorityIdx = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < heap.size() && hasHigherPriority(heap[left], heap[priorityIdx]))
            priorityIdx = left;
        if (right < heap.size() && hasHigherPriority(heap[right], heap[priorityIdx]))
            priorityIdx = right;

        if (priorityIdx != index) {
            swap(heap[index], heap[priorityIdx]);
            heapifyDown(priorityIdx);
        }
    }

public:
    void insertPatient(int id, string name, int severity, int arrivalTime) {
        heap.push_back({id, name, severity, arrivalTime});
        heapifyUp(heap.size() - 1);
    }

    void treatNext() {
        if (heap.empty()) return;
        cout << "Treating: " << heap[0].name << endl;
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    void peekNext() {
        if (!heap.empty()) 
            cout << "Next up: " << heap[0].name << " (Severity: " << heap[0].severity << ")\n";
    }

    void updateSeverity(int id, int newSeverity) {
        for (int i = 0; i < heap.size(); i++) {
            if (heap[i].id == id) {
                int oldSeverity = heap[i].severity;
                heap[i].severity = newSeverity;
               
                if (newSeverity > oldSeverity) heapifyUp(i);
                else heapifyDown(i);
                return;
            }
        }
    }

    void displayAll() {
        for (const auto& p : heap)
            cout << "[" << p.id << ": " << p.name << " (S:" << p.severity << ")] ";
        cout << endl;
    }
};

int main(){
   
    EEPrioritySystem er;

    cout << "--- 1. Adding Patients to the ER ---" << endl;
    
    er.insertPatient(101, "Ahmed", 5, 1000); 
    er.insertPatient(102, "Sara", 9, 1005); 
    er.insertPatient(103, "John", 5, 1010); 
    er.insertPatient(104, "Mona", 10, 1020);
    er.insertPatient(105, "Ziad", 2, 1030);

    cout << "Current Heap (Level Order): " << endl;
    er.displayAll();
    cout << "------------------------------------" << endl;

    cout << "\n--- 2. Viewing and Treating Patients ---" << endl;
    er.peekNext();
    er.treatNext(); 
    er.peekNext(); 
    er.treatNext(); 
    cout << "------------------------------------" << endl;

    cout << "\n--- 3. Updating Severity (Priority Shift) ---" << endl;
    
    cout << "Updating Ziad's severity from 2 to 10..." << endl;
    er.updateSeverity(105, 10);
    
    er.peekNext();  
    er.treatNext();
    cout << "------------------------------------" << endl;

    cout << "\n--- 4. Final Queue Status ---" << endl;
    er.displayAll(); 

    return 0;

}