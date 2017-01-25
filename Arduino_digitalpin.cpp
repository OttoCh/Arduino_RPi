#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <string>
#include "GPIOClass.cpp"
#include "Arduino_digitalpin.h"

using namespace std;

bool ctrl_c_pressed = false;

void sig_handler(int sig) {
	write(0, "nCtrl^C pressed in sig handlern", 32);
	ctrl_c_pressed = true;
}

int setSignal() {
	struct sigaction sig_struct;
	sig_struct.sa_handler = sig_handler;
	sig_struct.sa_flags = 0;
	sigemptyset(&sig_struct.sa_mask);
	if(sigaction(SIGINT, &sig_struct, NULL)==-1) {
		cout << "Problem with sigaction" << endl;
		return -1;
	}
	return 0;
}

int pinMode(int gpionum, string mode) {
	int export_gpio_status;
	int setdir_gpio_status;

	string gpionum_str = to_string(gpionum);
	GPIOClass *current_gpio = new GPIOClass(gpionum_str);

	string mode_str;
	if(mode == "OUTPUT") {
		mode_str = "out";
	}
	else if(mode == "INPUT") {
		mode_str = "in";
	}
	else {
		//some error warning and stuff
		std::cout << "Doesnt recognize \"" << mode << "\" command" << std::endl;
		exit(1);
	}
	export_gpio_status = current_gpio->export_gpio();
	if(export_gpio_status<0) {
		//export stuff is error
		std::cout << "Fail to export" << std::endl;
		exit(1);
	}
	setdir_gpio_status = current_gpio->setdir_gpio(mode_str);
	if(setdir_gpio_status<0) {
		//dirrectin stuff is error
		exit(1);
	}
	return 0;	//success
}

int digitalWrite(int gpionum, string logicLevel) {
	int setval_gpio_status;

	string gpionum_str = to_string(gpionum);
	GPIOClass *current_gpio = new GPIOClass(gpionum_str);

	string logicLevel_str;
	if(logicLevel=="HIGH") {
		logicLevel_str="1";
	}
	else if(logicLevel=="LOW") {
		logicLevel_str="0";
	}
	else {
		//some error stuff
		std::cout << "Doesnt recognize \"" << logicLevel << "\" command" << std::endl;
		exit(1);
	}
	setval_gpio_status = current_gpio->setval_gpio(logicLevel_str);
	if(setval_gpio_status<0) {
		//some error status
		std::cout << "Fail to set value" << std::endl;
		exit(1);
	}
	return 0;
}

int digitalRead(int gpionum) {

	string gpionum_str = to_string(gpionum);
	GPIOClass *current_gpio = new GPIOClass(gpionum_str);
	int val;
	val = current_gpio->getval_gpio(gpionum_str);
	return val;
}

void delay(long time) {
	usleep(time*1000);
	return;
}

