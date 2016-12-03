#include <stdio.h>
#include <iostream>
#include <string>
#include "basicdemo.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

int main(int argc, char* argv[])
{
	BasicDemo *basicdemo = new BasicDemo();

	cout << "ProductName: " << basicdemo->getProductName() << endl;
	cout << "ProductRevision: " << basicdemo->getProductRevision() << endl;
	cout << "ProductSerial: " << basicdemo->getProductSerial() << endl;
	cout << "ProductVersion: " << basicdemo->getFirmVersion() << endl;

	int i = basicdemo->GetCount();
	cout << "Count: " << dec << i << endl;

	cout << "CountUp" << endl;
	basicdemo->CountUp();
	i = basicdemo->GetCount();
	cout << "Count: " << dec << i << endl;

	cout << "CountUp" << endl;
	basicdemo->CountUp();

	i = basicdemo->GetCount();
	cout << "Count: " << dec << i << endl;

#ifdef WIN32
	system("pause");
#endif
	return 0;
}
