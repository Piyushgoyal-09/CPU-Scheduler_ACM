#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<climits>

using namespace std;

// Process structure
class Process {
	public:
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    
    //constructer
    Process(int id, int arrival_time, int burst_time, int priority){
	
        this->id = id;
		this->arrival_time = arrival_time; 
		this->burst_time = burst_time;
        this->priority = priority;
		this->remaining_time = burst_time;
		this->completion_time = 0, 
		this->turnaround_time = 0; 
		this->waiting_time = 0; 
		}
};

class ArrivalTimeComparator {
	public :
    bool operator()(const Process& p1, const Process& p2) const {
        return p1.arrival_time < p2.arrival_time;
    }
};

class PriorityComparator {
	public :
    bool operator()(const Process* p1, const Process* p2) const {
        return p1->priority > p2->priority;
    }
};

class Scheduler {
private:
    vector<Process> processes;
    int current_time;
    void calculateStats(){
    double avg_turnaround = 0.0;
    double avg_waiting = 0.0;
    int total_processes = processes.size();

    for (int i=0 ; i<processes.size() ; i++) {
        avg_turnaround += processes[i].turnaround_time;
        avg_waiting += processes[i].waiting_time;
    }

    avg_turnaround /= total_processes;
    avg_waiting /= total_processes;

    cout << "Average Turnaround Time: " << avg_turnaround << endl;
    cout << "Average Waiting Time: " << avg_waiting << endl;
    }

public:
Scheduler() {
    	current_time = 0;
    }

 void addProcess(int id, int arrival, int burst, int priority) {
       Process p(id, arrival, burst, priority);
       processes.push_back(p);
   }

   void displayProcesses() {
       cout << "Process\tArrival Time\tBurst Time\tPriority\n";
       for (int i=0;i<processes.size();i++) {
           cout << processes[i].id << "\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" << processes[i].priority << endl;
       }
   }

void scheduleFCFS(){
    sort(processes.begin(), processes.end(), ArrivalTimeComparator());

    current_time = processes[0].arrival_time;
    for (int i = 0; i < processes.size(); ++i) {
    if (processes[i].arrival_time > current_time) {
        current_time = processes[i].arrival_time;
    }
        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        current_time = processes[i].completion_time;
    }

    calculateStats();
}

void scheduleSJF() {
    sort(processes.begin(), processes.end(), ArrivalTimeComparator());

    int n = processes.size();
    for (int i =0 ;i<n;i++){
   	processes[i].waiting_time = 0;
   	processes[i].turnaround_time = 0;
    processes[i].remaining_time = processes[i].burst_time;
	}
    vector<bool> executed(n, false);
    current_time = processes[0].arrival_time;
    int complete = 0;

    while (complete != n) {
        int shortest_index;
        int shortest_burst = INT_MAX;

        // Find the shortest job that has arrived and not yet executed
        for (int i = 0; i < n; ++i) {
            if (!executed[i] && processes[i].arrival_time <= current_time && processes[i].burst_time < shortest_burst) {
                shortest_index = i;
                shortest_burst = processes[i].burst_time;
            }
        }

        // Execute the shortest job for a time quantum (1 unit) or until completion
        Process& current_process = processes[shortest_index];
        int execute_time = min(1, current_process.remaining_time); // Preemptive step
        current_process.remaining_time -= execute_time;
        current_time += execute_time;

        // If the process has completed its burst, update completion and waiting times
        if (current_process.remaining_time == 0) {
            current_process.completion_time = current_time;
            current_process.turnaround_time = current_process.completion_time - current_process.arrival_time;
            current_process.waiting_time = current_process.turnaround_time - current_process.burst_time;
            executed[shortest_index] = true;
            complete++;
        }
    }

    calculateStats();
}
void schedulePriority() {
    sort(processes.begin(), processes.end(), ArrivalTimeComparator());
    priority_queue<Process*, vector<Process*>, PriorityComparator> pq;

    int n = processes.size();
    int index = 0;
    current_time = processes[0].arrival_time;

    while (!pq.empty() || index < n) {

        while (index < n && processes[index].arrival_time <= current_time) {
            pq.push(&processes[index]);
            index++;
        }

        if (!pq.empty()) {
            Process* current_process_ptr = pq.top(); // Get pointer to the top process
            pq.pop();

            // Modify original process using pointer
            (*current_process_ptr).completion_time = current_time + (*current_process_ptr).burst_time;
            (*current_process_ptr).turnaround_time = (*current_process_ptr).completion_time - (*current_process_ptr).arrival_time;
            (*current_process_ptr).waiting_time = (*current_process_ptr).turnaround_time - (*current_process_ptr).burst_time;

            current_time = (*current_process_ptr).completion_time;
        } else {
            current_time++;
        	}
		}

    calculateStats();
}

void scheduleRoundRobin(int quantum) {
	 int n = processes.size();
     for (int i =0 ;i<n;i++){
   	processes[i].waiting_time = 0;
   	processes[i].turnaround_time = 0;
    processes[i].remaining_time = processes[i].burst_time;
	}
    sort(processes.begin(), processes.end(), ArrivalTimeComparator());
    
    current_time = processes[0].arrival_time;
     bool allDone = false;
     while(!allDone){
     	allDone = true;
     	for(int i =0;i<n;i++){
     		if(processes[i].remaining_time>0){
     			allDone = false;
     			if(processes[i].remaining_time>quantum){
     				current_time += quantum;
     				processes[i].remaining_time -= quantum;
				 }else{
				 	current_time += processes[i].remaining_time;
				 	processes[i].remaining_time = 0;
				 	processes[i].completion_time = current_time;
				 	processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
				 }
			 }
		 }
	 }


    calculateStats();
}

};

int main() {

       Scheduler scheduler;

    //----------------Input process details from user
   int num_processes;
   cout << "Enter the number of processes: ";
   cin >> num_processes;

   for (int i = 0; i < num_processes; ++i) {
       int id, arrival, burst, priority;
       cout << "Enter details for Process " << i + 1 << ":" << endl;
       cout << "ID: Arival Time:  Burst Time:  Priority:"<<endl;
       cin >> id >> arrival >> burst >> priority;
       // cout << "Arrival Time: ";
       // cin >> arrival;
       // cout << "Burst Time: ";
       // cin >> burst;
       // cout << "Priority: ";
       // cin >> priority;
       scheduler.addProcess(id, arrival, burst, priority);
   }
cout << "\nPriority Scheduling:" << endl;
    scheduler.schedulePriority();

    cout << "\nRound Robin Scheduling:" << endl;
    scheduler.scheduleRoundRobin(3);

    cout << "FCFS Scheduling:" << endl;
    scheduler.scheduleFCFS();

    cout << "\nSJF Scheduling:" << endl;
    scheduler.scheduleSJF();

    return 0;
	}
