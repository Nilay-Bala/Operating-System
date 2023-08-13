//FCFS Disk Scheduling
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int calculateSeekTime(vector<int>& requests, int head) {
    int n = requests.size();
    int seekTime = 0;

    for (int i = 0; i < n; i++) {
        int currentRequest = requests[i];
        seekTime += abs(currentRequest - head);
        head = currentRequest;
    }

    return seekTime;
}

double calculateThroughput(int numRequests, int totalSeekTime) {
    double totalProcessingTime = numRequests; // Assuming each request takes 1 unit of time
    double totalTime = totalSeekTime + totalProcessingTime;
    return numRequests / totalTime;
}

int main() {
    cout << "Enter the number of disk requests: ";
    int n;
    cin >> n;

    cout << "Enter the current head position: ";
    int head;
    cin >> head;

    cout << "Enter the disk request queue:" << endl;
    vector<int> requests(n);
    for (int i = 0; i < n; i++) {
        cin >> requests[i];
    }

    int totalSeekTime = calculateSeekTime(requests, head);
    double throughput = calculateThroughput(n, totalSeekTime);

    cout << "Total seek time: " << totalSeekTime << endl;
    cout << "Throughput: " << throughput << " requests per unit of time" << endl;

    return 0;
}
