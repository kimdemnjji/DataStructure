#include <ctime>
#include "BankSimulator.h"
#include <iostream>
#include "CustomerQueue.h"
#include "Customer.h"



int main()
{
	srand((unsigned int)time(NULL));
	BankSimulator	sim1;		// �ùķ����� ��ü ����
	sim1.readSimulationParameters();	// �ùķ��̼� �Ķ���� ����
	sim1.run();			// �ùķ��̼� ����
	sim1.printStat();			// �ùķ��̼� ��� ���



	system("pause");
	return 0;
}


