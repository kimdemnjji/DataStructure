#pragma once
struct Customer {
    int id;         // 고객 번호
    int tArrival;   // 고객이 도착한 시간
    int tService;   // 이 고객의 서비스에 필요한 시간
    int counter;    // 고객이 어느 창구에서 서비스 받는지 나타내는 변수
    Customer(int i = 0, int tArr = 0, int tServ = 0, int cnt = 0) : id(i), tArrival(tArr), tService(tServ), counter(cnt) {}
};