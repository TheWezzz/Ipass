#include "color.cpp"
#include "hwlib.hpp"

#include <string>
#include <iostream>

using namespace std;

void servo_angle(const unsigned int angle){
	auto pinSERVO = hwlib::target::pin_in_out(hwlib::target::pins::d7);
	double sleepsec = angle/90000 + 0.0004;
	cout << sleepsec << endl;
	pinSERVO::pin_in_out::write(1);
	hwlib::wait_ms(sleepsec);
	pinSERVO::pin_in_out::write(0);
}

void servo_switch(const unsigned int pos){
	if(pos == 0){
		servo_angle(90);
	}else if(pos == 1){
		servo_angle(45);
	}else if(pos == 2){
		servo_angle(135);
	}else{
		return;
	}
}


int main(){
	
	string c1 = "blue"
	string c2 = "green"
	string c = ""
	
	int Red;
	int Green;
	int Blue;
	
	while(true){
		Red = Color.red();
		Green = Color.green();
		Blue = Color.blue();
		
		if(Red > Green and Red > Blue){
			c = "red";
		}else if(Green > Red and Green > Blue{
			c = "green";
		}else if(Blue > Red and Blue > Green){
			c = "blue";
		}else{
			continue;
		}
	
		if(c == c1){
			servo_switch(1)
		}else if(c == c2{
			servo_switch(2)
		}else{
			servo_switch(0)
		}
		
		hwlib::wait_ms(250);
	}
}