#include "hwlib.hpp"
using namespace std;

#define _0	0
#define _2 1
#define _20	2
#define _100 3

class Color{
	private:
		void setFrequency(const unsigned int S0, const unsigned int S1);
		void getFrequency(int f);
		int setColor(const unsigned int S2, const unsigned int S3);
		
	public:
		Color(const int FREQUENCY){
			getFrequency(FREQUENCY);
			auto pinS0 = hwlib::target::pin_out(hwlib::target::pins::d10);
			auto pinS1 = hwlib::target::pin_out(hwlib::target::pins::d11);
			auto pinS2 = hwlib::target::pin_out(hwlib::target::pins::d12);
			auto pinS3 = hwlib::target::pin_out(hwlib::target::pins::d13);
			auto pinLED = hwlib::target::pin_out(hwlib::target::pins::d8);
			auto pinSENSOR = hwlib::target::pin_in(hwlib::target::pins::d9);
		};
		
		int red();
		int green();
		int blue();
		int white();
};

void Color::getFrequency(int f){
	switch (f){
		case _0:
			setFrequency(0, 0);
			break;
		case _2:
			setFrequency(0, 1);
			break;
		case _20:
			setFrequency(1, 0);
			break;
		case _100:
			setFrequency(1, 1);
			break;
		default:
			setFrequency(1, 0);
			break;
	}
}

void Color::setFrequency(const unsigned int S0, const unsigned int S1){
	Color::pinS0::pin_in_out::write(S0);
	Color::pinS1::pin_in_out::write(S1);
}

int Color::red(){
	int color = setColor(0, 0);
	return color;
}

int Color::green(){
	int color = setColor(1, 1);
	return color;
}

int Color::blue(){
	int color = setColor(0, 1);
	return color;
}

int Color::white(){
	int color = setColor(1, 0);
	return color;
}

int Color::setColor(const unsigned int S2, const unsigned int S3){
	Color::pinLED::pin_in_out::write(1);
	Color::pinS2::pin_in_out::write(S2);
	Color::pinS3::pin_in_out::write(S3);
	int color = pulseIn(Color::pinSENSOR, 0);
	Color::pinLED::pin_in_out::write(0);
	return color;
}