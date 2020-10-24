//First Come First Serve (FCFS)
#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

void printOutput(const vector<int> &bt, const vector<int> &wt, const vector<int> &tA);

vector<int> readInput();

int main() {
    cout << "OS Lab 1: FCFS Scheduling Algorithm" << endl;
    vector<int> burstTImeList = readInput();
    vector<int> waitingTimeList;
    vector<int> turnAroundTimeList;

    // for the first process initialize
    waitingTimeList.push_back(0);
    turnAroundTimeList.push_back(burstTImeList[0]);

    for (int i = 1; i < burstTImeList.size(); i++) {
        waitingTimeList.push_back((burstTImeList[i - 1] + waitingTimeList[i - 1]));
        turnAroundTimeList.push_back((waitingTimeList[i] + burstTImeList[i]));
    }
    printOutput(burstTImeList, waitingTimeList, turnAroundTimeList);
    return 0;
}

vector<int> readInput() {
    string input;  // for reading input from the file
    vector<int> processList;
    ifstream file;
    // Open file containing inputs
    file.open("//home/inan/CLionProjects/OS Lab 1/input.txt");
    if (!file) {
        cerr << "Unable to open file input.txt for some error!";
        exit(1);   // call system to stop
    } else {
        while (file >> input) {
            processList.push_back(stoi(input)); // make a list of keywords
        }
    }
    file.close(); // close the file
    // printList(keywordsList);
    return processList;
}

void printOutput(const vector<int> &bt, const vector<int> &wt, const vector<int> &tA) {

    for (int i = 0; i < bt.size(); i++) {
        cout << "Process : " << i + 1 << "  Burst Time : " << bt[i] <<
             "  Waiting Time:  " << wt[i] << "  Turn Around TIme: " << tA[i] << endl;
    }

    cout<< "Average Waiting TIme:  "<<(float) accumulate(wt.begin(), wt.end(), 0)  / wt.size() << endl;
    cout<< "Average Turn Around TIme:  "<< (float)accumulate(tA.begin(), tA.end(), 0)  / tA.size() << endl;
}
