//hasilnya harus di run dengan sudo biar reliabel hasilnya, kalau ga
//nanti bisa-gabisa-bisa terus
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "GPIOClass.cpp"
#include <signal.h>

using namespace std;

bool ctrl_c_pressed = false;

void sig_handler(int sig) {
	write(0, "nCtrl^C pressed in sig handlern", 32);
	ctrl_c_pressed = true;
}

int main(void) {
	
	struct sigaction sig_struct;
	sig_struct.sa_handler = sig_handler;
	sig_struct.sa_flags = 0;
	sigemptyset(&sig_struct.sa_mask);
	if(sigaction(SIGINT, &sig_struct, NULL)==-1) {
		cout << "Problem with sigaction" << endl;
		return -1;
	}

	GPIOClass* gpio4 = new GPIOClass("4");
	gpio4->export_gpio();
	cout << "gpio pins exported" << endl;
	gpio4->setdir_gpio("out");
	cout << "direction set " << endl;
	int j = 0;
	while(j<10) {
		usleep(1000000);
		gpio4->setval_gpio("1");
		cout << "HIGH" << endl;
		usleep(1000000);
		gpio4->setval_gpio("0");
		cout << "LOW" << endl;
		j++;
		if(ctrl_c_pressed) {
			cout << "Ctrl+C pressed" << endl;
			gpio4->unexport_gpio();
			delete gpio4;
			break;
		}
	}
	//gpio4->unexport_gpio();	//kalau ini diadakan disini ntah kenapa program berikutnya tidak lgsg bekerja dan harus double
	//delete gpio4;
	return 0;
}