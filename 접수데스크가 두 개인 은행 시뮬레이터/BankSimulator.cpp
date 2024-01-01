#include <ctime>
#include "BankSimulator.h"
#include <iostream>
#include "CustomerQueue.h"
#include "Customer.h"



int main()
{
	srand((unsigned int)time(NULL));
	BankSimulator	sim1;		// 시뮬레이터 객체 생성
	sim1.readSimulationParameters();	// 시뮬레이션 파라미터 설정
	sim1.run();			// 시뮬레이션 시작
	sim1.printStat();			// 시뮬레이션 결과 출력



	system("pause");
	return 0;
}


