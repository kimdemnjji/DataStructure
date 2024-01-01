#pragma once
#include "CustomerQueue.h"
#include "Customer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(suppress : 4996)

using namespace std;
class BankSimulator {
    int nSimulation;           // 입력: 전체 시뮬레이션 횟수
    double probArrival;        // 입력: 단위시간에 도착하는 평균 고객 수
    int tMaxService;          // 입력: 한 고객에 대한 최대 서비스 시간
    int totalWaitTime;        // 결과: 고객들이 기다린 전체 시간
    int nCustomers;           // 결과: 전체 고객 수
    int nServedCustomers;     // 결과: 서비스 받은 고객 수
    CustomerQueue que1;       // 고객 대기 큐 for counter A
    CustomerQueue que2;       // 고객 대기 큐 for counter B
    Customer currentCustomerAtCounterA; // Counter A에서 현재 서비스 중인 고객
    Customer currentCustomerAtCounterB; // Counter B에서 현재 서비스 중인 고객

    double Random() { return rand() / (double)RAND_MAX; }

    bool IsNewCustomer() { return Random() <= probArrival; }

    int RandServiceTime() { return (int)(tMaxService * Random()) + 1; }

    void InsertCustomer(int arrivalTime) {
        int counter = (rand() % 2) + 1;  // 무작위로 창구 선택
        Customer c(++nCustomers, arrivalTime, RandServiceTime(), counter);
        if (counter == 1) {
            que1.enqueue(c);
        }
        else {
            que2.enqueue(c);
        }
    }

public:
    BankSimulator() : nCustomers(0), totalWaitTime(0), nServedCustomers(0) {}

    void readSimulationParameters() {
        cout << "시뮬레이션 할 최대시간 (예: 10) = ";
        cin >> nSimulation;
        cout << "단위시간에 도착하는 고객 수 (예: 0.3) = ";
        cin >> probArrival;
        cout << "한 고객에 대한 최대 서비스 시간 (예:0.5) = ";
        cin >> tMaxService;
        cout << "===========================================\n";
        cout << "고객별 서비스 종료 정보\n";
        cout << "고객 창구 도착시각 대기시간 서비스시작시각 서비스기간 종료기간\n";
    }

    void run() {
        int clock = 0;

        while (clock < nSimulation) {
            clock++;

            if (IsNewCustomer()) {
                InsertCustomer(clock);
            }

            if (!que1.isEmpty() && currentCustomerAtCounterA.id == 0) {
                currentCustomerAtCounterA = que1.dequeue();
                nServedCustomers++;
                int waitTime = max(0, (clock - currentCustomerAtCounterA.tArrival));
                totalWaitTime += waitTime;
                int serviceStartTime = max(clock, currentCustomerAtCounterA.tArrival);
                int serviceEndTime = serviceStartTime + currentCustomerAtCounterA.tService;
                cout << currentCustomerAtCounterA.id << "    A      " << currentCustomerAtCounterA.tArrival << "        " << waitTime << "             " << serviceStartTime << "         " << currentCustomerAtCounterA.tService << "         " << serviceEndTime << endl;
            }

            if (!que2.isEmpty() && currentCustomerAtCounterB.id == 0) {
                currentCustomerAtCounterB = que2.dequeue();
                nServedCustomers++;
                int waitTime = max(0, (clock - currentCustomerAtCounterB.tArrival));
                totalWaitTime += waitTime;
                int serviceStartTime = max(clock, currentCustomerAtCounterB.tArrival);
                int serviceEndTime = serviceStartTime + currentCustomerAtCounterB.tService;
                cout << currentCustomerAtCounterB.id << "    B      " << currentCustomerAtCounterB.tArrival << "        " << waitTime << "             " << serviceStartTime << "         " << currentCustomerAtCounterB.tService << "         " << serviceEndTime << endl;
            }

            if (currentCustomerAtCounterA.id != 0) {
                currentCustomerAtCounterA.tService--;
                if (currentCustomerAtCounterA.tService == 0) {
                    currentCustomerAtCounterA = Customer(); // Counter A에서 서비스가 끝난 고객을 초기화
                }
            }

            if (currentCustomerAtCounterB.id != 0) {
                currentCustomerAtCounterB.tService--;
                if (currentCustomerAtCounterB.tService == 0) {
                    currentCustomerAtCounterB = Customer(); // Counter B에서 서비스가 끝난 고객을 초기화
                }
            }
        }
    }

    void printStat() {
        cout << "===========================================\n";
        cout << "서비스 받은 고객수 = " << nServedCustomers << endl;
        cout << "전체 대기시간 = " << totalWaitTime << "분\n";
        if (nServedCustomers > 0) {
            cout << "서비스고객 평균 대기시간 = " << (double)totalWaitTime / nServedCustomers << "분\n";
        }
        else {
            cout << "서비스고객 평균 대기시간 = 0분\n";
        }
        cout << "현재 대기고객 수 = " << que1.size() + que2.size() << endl;
    }
};