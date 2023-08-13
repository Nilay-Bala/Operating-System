#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int burst_time;
    int deadline;
};

bool sortByDeadline(const Process& p1, const Process& p2) {
    return p1.deadline < p2.deadline;
}

void calculateMetrics(vector<Process>& processes) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int completed_processes = 0;
    int current_time = 0;

    sort(processes.begin(), processes.end(), sortByDeadline);

    cout << "Process\t\tBurst Time\t\tDeadline\t\tWaiting Time\t\tTurnaround Time\n";

    for (const auto& process : processes) {
        int waiting_time = max(0, current_time); // Waiting time is max(0, current_time) to account for non-preemptive scheduling.
        int turnaround_time = waiting_time + process.burst_time;

        total_waiting_time += waiting_time;
        total_turnaround_time += turnaround_time;

        current_time += process.burst_time;
        completed_processes++;

        cout << "P" << process.id << "\t\t\t" << process.burst_time << "\t\t" << process.deadline << "\t\t\t"
             << waiting_time << "\t\t\t" << turnaround_time << endl;
    }

    double avg_waiting_time = static_cast<double>(total_waiting_time) / completed_processes;
    double avg_turnaround_time = static_cast<double>(total_turnaround_time) / completed_processes;
    double throughput = static_cast<double>(completed_processes) / current_time;

    cout << "\nAverage Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
    cout << "Throughput: " << throughput << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes;
    for (int i = 1; i <= n; i++) {
        Process p;
        cout << "Process ID: P" << i << endl;
        p.id = i;
        cout << "Burst Time: ";
        cin >> p.burst_time;
        cout << "Deadline: ";
        cin >> p.deadline;
        processes.push_back(p);
    }

    calculateMetrics(processes);

    return 0;
}
