//Priority Scheduling Algorithm (Non-Preemptive)
#include <iostream>
#include <cstdio>
#include <vector>
#include <bits/stdc++.h>

using namespace std;


void printOutput(const vector<vector<int>> &bt, const vector<vector<int>> &wt, const vector<vector<int>> &tA);

vector<vector<int>> readInput();

int main() {
    cout << "OS Lab 4: Priority Scheduling Algorithm (Non-Preemptive)" << endl;
    vector<vector<int>> burstTImeList = readInput();
    vector<vector<int>> waitingTimeList;
    vector<vector<int>> turnAroundTimeList;
    //sort based on process burst time
    //sort using selection sort
    for (int i = 0; i < burstTImeList.size(); i++) {
        for (int j = i + 1; j < burstTImeList.size(); j++) {
            if (burstTImeList[i][2] > burstTImeList[j][2]) {
                swap(burstTImeList[i], burstTImeList[j]);
            }
        }
    }

    //calculate waiting time and turn around time
    for (int i = 0; i < burstTImeList.size(); i++) {
        if(i == 0)
        {
            waitingTimeList.push_back({burstTImeList[i][0], 0});
            turnAroundTimeList.push_back({burstTImeList[i][0], burstTImeList[i][1] + waitingTimeList[i][1]});
        }
        else {
            waitingTimeList.push_back({burstTImeList[i][0] , burstTImeList[i - 1][1] + waitingTimeList[i - 1][1]});
            turnAroundTimeList.push_back({burstTImeList[i][0] , waitingTimeList[i][1] + burstTImeList[i][1]});
        }

    }
    //sort based on process order
    //sort using selection sort
    for (int i = 0; i < burstTImeList.size(); i++) {
        for (int j = i + 1; j < burstTImeList.size(); j++) {
            if (burstTImeList[i][0] > burstTImeList[j][0]) {
                swap(burstTImeList[i], burstTImeList[j]);
            }
        }
    }

    //sort using selection sort
    for (int i = 0; i < waitingTimeList.size(); i++) {
        for (int j = i + 1; j < waitingTimeList.size(); j++) {
            if (waitingTimeList[i][0] > waitingTimeList[j][0]) {
                swap(waitingTimeList[i], waitingTimeList[j]);
            }
        }
    }

    //sort using selection sort
    for (int i = 0; i < turnAroundTimeList.size(); i++) {
        for (int j = i + 1; j < turnAroundTimeList.size(); j++) {
            if (turnAroundTimeList[i][0] > turnAroundTimeList[j][0]) {
                swap(turnAroundTimeList[i], turnAroundTimeList[j]);
            }
        }
    }


    printOutput(burstTImeList, waitingTimeList, turnAroundTimeList);
    return 0;
}

vector<vector<int>> readInput() {
    string bt, p;  // for reading input from the file
    vector<vector<int>> processList;
    int i = 1;
    ifstream file;
    // Open file containing inputs
    file.open("/home/inan/CLionProjects/OS Lab 4/input.txt");
    if (!file) {
        cerr << "Unable to open file input.txt for some error!";
        exit(1);   // call system to stop
    } else {
        while (file >> bt >> p) {
            processList.push_back({i, stoi(bt), stoi(p)}); // make a list of keywords
            i = i + 1;
        }
    }
    file.close(); // close the file
    // printList(keywordsList);
    return processList;
}

void printOutput(const vector<vector<int>> &bt, const vector<vector<int>> &wt, const vector<vector<int>> &tA) {


    printf("Process\tBurst time\tPriority Queue\tWaiting time\tTurn around time\n");
    for (int i = 0; i < bt.size(); i++)
        printf("\t%d\t\t%d\t\t\t%d\t\t\t\t%d\t\t\t\t%d\n",
               bt[i][0], bt[i][1], bt[i][2], wt[i][1], tA[i][1]);

    int sum = 0;
    for(const auto &x:  wt){
        sum = sum + x[1];
    }

    float awt = (float)sum / wt.size();

    sum = 0;
    for(const auto &x:  tA){
        sum = sum + x[1];
    }

    float atA = (float)sum / tA.size();

    cout << "Average Waiting Time:  " << awt<< endl;
    cout << "Average Turn Around Time:  " << atA << endl;
}
