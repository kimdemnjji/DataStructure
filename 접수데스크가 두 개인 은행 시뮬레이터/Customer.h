#pragma once
struct Customer {
    int id;         // �� ��ȣ
    int tArrival;   // ���� ������ �ð�
    int tService;   // �� ���� ���񽺿� �ʿ��� �ð�
    int counter;    // ���� ��� â������ ���� �޴��� ��Ÿ���� ����
    Customer(int i = 0, int tArr = 0, int tServ = 0, int cnt = 0) : id(i), tArrival(tArr), tService(tServ), counter(cnt) {}
};