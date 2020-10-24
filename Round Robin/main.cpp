#include <iostream>
#include <cstdio>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Process {
public:
    int id{};
    int arrivalTime{};
    int burstTime{};
    int remainingTime{};
    int completionTime{};
    int waitingTime{};
    int turnAroundTime{};
    int responseTime = -1;
};

void printOutput(vector<Process> &processList);

vector<Process> readInput();


int main() {
    cout << "OS Lab 5: RR Scheduling Algorithm" << endl;
    vector<Process> processList = readInput();
    int quantum = 2;

    int totalTime = 0;

    for (const auto &p:  processList) {
        totalTime = totalTime + p.burstTime;
    }

    int counter = 0;
    int i = 0;
    while (counter < totalTime) {
        if (i >= processList.size()) {
            i = 0;
        }
        if (processList[i].arrivalTime <= counter) {
            if (processList[i].remainingTime > quantum) {
                processList[i].remainingTime = processList[i].remainingTime - quantum;
                if (processList[i].responseTime == -1) {
                    processList[i].responseTime = counter - processList[i].arrivalTime;
                }
                counter = counter + quantum;
            } else if (processList[i].remainingTime != 0) {
                if (processList[i].responseTime == -1) {
                    processList[i].responseTime = counter - processList[i].arrivalTime;
                }
                counter = counter + processList[i].remainingTime;
                processList[i].completionTime = counter;
                processList[i].waitingTime =
                        processList[i].completionTime - processList[i].burstTime - processList[i].arrivalTime;
                processList[i].remainingTime = 0;
            }
        }
        i++;
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
    int j = 1;
    ifstream file;
    // Open file containing inputs
    file.open("/home/inan/CLionProjects/OS_Lab_5/input.txt");
    if (!file) {
        cerr << "Unable to open file input.txt for some error!";
        exit(1);   // call system to stop
    } else {
        while (file >> arrivalTime >> burstTime) {
            Process p{};
            p.id = j;
            p.arrivalTime = stoi(arrivalTime);
            p.burstTime = stoi(burstTime);
            p.remainingTime = stoi(burstTime);
            processList.push_back(p);
            j = j + 1;
        }
    }
    file.close(); // close the file
    return processList;
}

void printOutput(vector<Process> &processList) {
    printf("Process\tArrival Time\tBurst Time\tResponse Time\tWaiting Time\tTurn Around Time\n");
    for (auto &p: processList)
        printf("\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t\t%d\t\t\t\t%d\n",
               p.id, p.arrivalTime, p.burstTime, p.responseTime, p.waitingTime, p.turnAroundTime);

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
