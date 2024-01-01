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
    int nSimulation;           // �Է�: ��ü �ùķ��̼� Ƚ��
    double probArrival;        // �Է�: �����ð��� �����ϴ� ��� �� ��
    int tMaxService;          // �Է�: �� ���� ���� �ִ� ���� �ð�
    int totalWaitTime;        // ���: ������ ��ٸ� ��ü �ð�
    int nCustomers;           // ���: ��ü �� ��
    int nServedCustomers;     // ���: ���� ���� �� ��
    CustomerQueue que1;       // �� ��� ť for counter A
    CustomerQueue que2;       // �� ��� ť for counter B
    Customer currentCustomerAtCounterA; // Counter A���� ���� ���� ���� ��
    Customer currentCustomerAtCounterB; // Counter B���� ���� ���� ���� ��

    double Random() { return rand() / (double)RAND_MAX; }

    bool IsNewCustomer() { return Random() <= probArrival; }

    int RandServiceTime() { return (int)(tMaxService * Random()) + 1; }

    void InsertCustomer(int arrivalTime) {
        int counter = (rand() % 2) + 1;  // �������� â�� ����
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
        cout << "�ùķ��̼� �� �ִ�ð� (��: 10) = ";
        cin >> nSimulation;
        cout << "�����ð��� �����ϴ� �� �� (��: 0.3) = ";
        cin >> probArrival;
        cout << "�� ���� ���� �ִ� ���� �ð� (��:0.5) = ";
        cin >> tMaxService;
        cout << "===========================================\n";
        cout << "���� ���� ���� ����\n";
        cout << "�� â�� �����ð� ���ð� ���񽺽��۽ð� ���񽺱Ⱓ ����Ⱓ\n";
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
                    currentCustomerAtCounterA = Customer(); // Counter A���� ���񽺰� ���� ���� �ʱ�ȭ
                }
            }

            if (currentCustomerAtCounterB.id != 0) {
                currentCustomerAtCounterB.tService--;
                if (currentCustomerAtCounterB.tService == 0) {
                    currentCustomerAtCounterB = Customer(); // Counter B���� ���񽺰� ���� ���� �ʱ�ȭ
                }
            }
        }
    }

    void printStat() {
        cout << "===========================================\n";
        cout << "���� ���� ���� = " << nServedCustomers << endl;
        cout << "��ü ���ð� = " << totalWaitTime << "��\n";
        if (nServedCustomers > 0) {
            cout << "���񽺰� ��� ���ð� = " << (double)totalWaitTime / nServedCustomers << "��\n";
        }
        else {
            cout << "���񽺰� ��� ���ð� = 0��\n";
        }
        cout << "���� ���� �� = " << que1.size() + que2.size() << endl;
    }
};