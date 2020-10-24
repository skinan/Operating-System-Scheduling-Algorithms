// Shortest Remaining Time Job First Algorithm (SRTF)
#include <iostream>
#include <cstdio>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Process {
public:
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
};

void printOutput(vector<Process> &processList);

vector<Process> readInput();

vector<Process> selection_sort(vector<Process> processList);

int main() {
    cout << "OS Lab 3: SJF Scheduling Algorithm (Preemptive)" << endl;
    vector<Process> processList = readInput();
    processList = selection_sort(processList);

    int totalTime = 0;
    for (const auto &p:  processList) {
        totalTime = totalTime + p.burstTime;
    }
    int counter = 0;

    while (counter <= totalTime) {
        for (auto &p: processList) {
            if ((p.arrivalTime <= counter) and (p.remainingTime != 0)) {
                p.remainingTime--;
                if (p.remainingTime == 0) {
                    p.completionTime = counter + 1;
                    p.waitingTime = (p.completionTime - p.burstTime) - p.arrivalTime;
                }
                break;
            } else {
                continue;
            }
        }
        processList = selection_sort(processList);
        counter++;
    }

    for (auto &p:processList) {
        p.turnAroundTime = p.waitingTime + p.burstTime;
    }


    printOutput(processList);
    return 0;
}

vector<Process> readInput() {
    string arrivalTime, burstTime;  // for reading input from the file
    vector<Process> processList;
    int i = 1;
    ifstream file;
    // Open file containing inputs
    file.open("/home/inan/CLionProjects/OS Lab 3/input.txt");
    if (!file) {
        cerr << "Unable to open file input.txt for some error!";
        exit(1);   // call system to stop
    } else {
        while (file >> arrivalTime >> burstTime) {
            Process p{};
            p.id = i;
            p.arrivalTime = stoi(arrivalTime);
            p.burstTime = stoi(burstTime);
            p.remainingTime = stoi(burstTime);
            processList.push_back(p);
            i = i + 1;
        }
    }
    file.close(); // close the file
    return processList;
}

void printOutput(vector<Process> &processList) {


    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurn Around Time\n");
    for (auto &p: processList)
        printf("\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t\t%d\n",
               p.id, p.arrivalTime, p.burstTime, p.waitingTime, p.turnAroundTime);

    int sum = 0;
    for (const auto &p: processList) {
        sum = sum + p.waitingTime;
    }

    float awt = (float) sum / processList.size();

    sum = 0;
    for (const auto &p: processList) {
        sum = sum + p.turnAroundTime;
    }

    float atA = (float) sum / processList.size();

    cout << "Average Waiting Time:  " << awt << endl;
    cout << "Average Turn Around Time:  " << atA << endl;

}

vector<Process> selection_sort(vector<Process> processList) {
    for (int i = 0; i < processList.size(); i++) {
        for (int j = i + 1; j < processList.size(); j++) {
            if (processList[i].remainingTime > processList[j].remainingTime) {
                swap(processList[i], processList[j]);
            } else if (processList[i].remainingTime == processList[j].remainingTime) {
                if (processList[i].arrivalTime > processList[j].arrivalTime) {
                    swap(processList[i], processList[j]);
                } else if (processList[i].arrivalTime == processList[j].arrivalTime) {
                    if (processList[i].id > processList[j].id) {
                        swap(processList[i], processList[j]);
                    }
                }
            }
        }
    }

    return processList;
}