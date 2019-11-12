#include <iostream>
#include <string>
#include <cstdint>
#include <thread>
#include <chrono>
#include <random>

#include <conio.h>//not standard.

#include "StopWatch_II.h"

//https://twitter.com/vitaone_/status/845954013103239168

bool ShowProgress(const std::string& Title, std::uintmax_t L, const std::string& Token,unsigned int S=0) {

	std::uniform_int_distribution<> TL(16, 1500);
	std::uniform_int_distribution<> OL(16, 16*5);
	std::mt19937 mt;


	StopWatch SW;
		std::cout << Title << ':';
	for (std::uintmax_t i = 0; i < L; i++) {
		std::chrono::milliseconds ms(TL(mt));
		SW.Start();
		std::cout << ' ';
		std::size_t GC = 0;
		while (ms >= SW.Ellipse<>()) {
			std::cout <<(char)8<< Token[GC++];
			GC %= Token.size();
			std::this_thread::sleep_for(std::chrono::milliseconds(OL(mt)));

			if (_kbhit()) { if (_getch() == 27) { std::cout << "--->> Aborted!" << std::endl; goto L;}  }
		}
		std::cout <<(char)8<< '*';
	}

	std::cout << " --->> Task End?" << std::endl;

	L:

	return true;
}

bool ShowTitle() {
	std::cout << "Think With Duck." << std::endl;
	std::cout << "Hit Key to Start!" << std::endl;
	int Key = _getch();

	if (Key == 27) { return false; }

	std::cout << std::endl;

	return true;
}

int main() {
	
	if (ShowTitle() == false) { return -1; }

	std::random_device rd;
	std::uniform_int_distribution<> ui(7, 70);
	std::mt19937 mt(rd());
	std::string T;
	int key = 0;
	do {
		std::cout << "TypeIn to Task Name:";
		std::cin >> T;
		std::cin.clear();

		std::cout << "Let's Start!" << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(2750));

		ShowProgress(T, ui(mt), " -\|/*",mt());
		std::cout << std::endl;
		std::cout << "You Have next Task?(y/n)";

		key = _getch();
		std::cout << std::endl;

	} while (key == 'y');
	
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "complete this time." << std::endl;


	return true;
}