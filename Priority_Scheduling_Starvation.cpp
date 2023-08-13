//Priority Scheduling Starvation
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>


struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int tempPriority;
    int startTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    bool completed;
    int age;

    Process(int id, int arrivalTime, int burstTime, int priority) {
        this->id = id;
        this->arrivalTime = arrivalTime;
        this->burstTime = burstTime;
        this->priority = priority;
        this->tempPriority = priority;
        this->startTime = 0;
        this->completionTime = 0;
        this->waitingTime = 0;
        this->turnaroundTime = 0;
        this->completed = false;
        this->age=2;
    }
};

bool compareArrivalTime(const Process& p1, const Process& p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

int main() {
    std::vector<Process> processes;

    int n;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    std::cout << "Enter Arrival, Burst, Priority:\n";
    for (int i = 0; i < n; i++) {
        std::cout << "for process " << (i + 1) << ":\n";
        int arrivalTime, burstTime, priority;
        std::cin >> arrivalTime >> burstTime >> priority;

        Process process(i + 1, arrivalTime, burstTime, priority);
        processes.push_back(process);
    }

    // Sort processes based on arrival time
    std::sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        Process* selectedProcess = nullptr;
       int highestPriority = INT_MAX;



        for (auto& process : processes) {
            if (process.arrivalTime <= currentTime && process.priority < highestPriority && !process.completed) {
                highestPriority = process.priority;
                selectedProcess = &process;
            }
        }

        if (selectedProcess == nullptr) {
            currentTime++;
            continue;
        }

        selectedProcess->startTime = currentTime;
        selectedProcess->completionTime = selectedProcess->startTime + selectedProcess->burstTime;
        currentTime += selectedProcess->burstTime;
        selectedProcess->turnaroundTime = selectedProcess->completionTime - selectedProcess->arrivalTime;
        selectedProcess->waitingTime = selectedProcess->turnaroundTime - selectedProcess->burstTime;
        selectedProcess->completed = true;
        completedProcesses++;

        // Aging: Increase the priority of waiting processes
        for (auto& process : processes) {
            if (process.arrivalTime <= currentTime && &process != selectedProcess) {
                process.priority--;
                process.age--;
                            }
        }
    }

    float averageWaitingTime = 0.0f;
    float averageTurnaroundTime = 0.0f;

    std::cout << "\nProcess\t\tArrival\t\tBurst\t\tPriority\tCompletion\t\tWaiting\t\tTurnaround\n";
    std::cout << "--------------------------------------------------------------------------------------------------------------------------\n";
    for (const auto& process : processes) {
        averageTurnaroundTime += process.turnaroundTime;
        averageWaitingTime += process.waitingTime;
        std::cout << process.id << "\t\t" << process.arrivalTime << "\t\t" << process.burstTime << "\t\t" << process.tempPriority << "\t\t"
                  << process.completionTime << "\t\t" << process.waitingTime << "\t\t" << process.turnaroundTime << std::endl;
}

std::cout << "Average Waiting Time: " << averageWaitingTime / n << std::endl;
std::cout << "Average Turnaround Time: " << averageTurnaroundTime / n << std::endl;

return 0;
}