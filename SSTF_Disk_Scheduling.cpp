//SSTF Disk Scheduling
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

int calculateSeekTime(const vector<int>& requests, int head) {
    int n = requests.size();
    int seekTime = 0;
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) {
        int closestRequestIndex = -1;
        int minDistance = numeric_limits<int>::max();

        // Find the closest unvisited request
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int distance = abs(requests[j] - head);
                if (distance < minDistance) {
                    minDistance = distance;
                    closestRequestIndex = j;
                }
            }
        }

        // Mark the closest request as visited and update seek time
        visited[closestRequestIndex] = true;
        int closestRequest = requests[closestRequestIndex];
        seekTime += abs(closestRequest - head);
        head = closestRequest;
    }

    return seekTime;
}

int main() {
    // Get input from the user
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

    // Calculate seek time using SSTF algorithm
    int totalSeekTime = calculateSeekTime(requests, head);

    // Calculate throughput
    double throughput = static_cast<double>(n) / totalSeekTime;

    // Display the results
    cout << "Total seek time: " << totalSeekTime << endl;
    cout << "Throughput: " << throughput << endl;

    return 0;
}
