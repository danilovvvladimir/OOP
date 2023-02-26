#include "Car.h"
#include <iostream>

int main()
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Gear::First);
	car.SetSpeed(20);
	car.SetGear(Gear::Second);
	car.SetSpeed(50);
	car.SetGear(Gear::Fifth);
	car.SetSpeed(150);
	car.SetSpeed(50);
	car.SetGear(Gear::Second);
	car.SetSpeed(20);
	car.SetGear(Gear::First);
	car.SetSpeed(0);
	car.SetGear(Gear::Neutral);
	car.SetGear(Gear::Reversed);
	car.SetSpeed(10);
	car.SetGear(Gear::Neutral);
	car.SetSpeed(0);
	car.SetGear(Gear::Reversed);
	car.SetSpeed(10);
	car.SetGear(Gear::Neutral);
	car.SetSpeed(0);
	car.SetGear(Gear::First);
	car.PrintInfo();
	return 0;
}