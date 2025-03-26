#include "data/car.hpp"
#include "data/colors.hpp"

#include "example.silica.hpp"

#include "silica/reflection/reflection.hpp"
#include "silica/serialization/json.hpp"

#include <iostream>

int main() {
	//We have a car
	Car car;
	car.brand = "Toyota";
	car.year = 2023;
	car.owner = "John Smith";

	//Let's dump it to the console as JSON
	std::cout << "I have a car:\n"
			  << silica::serialization::json::to_string(&car).unwrap() << std::endl;

	//Let's reflect it
	silica::TypeInfo info = silica::reflection::reflect(&car);

	//Let's see if the car is insured
	auto insuredVar = info.get<silica::Object>().get_field("insured").unwrap().var();
	bool insured = *(insuredVar.rt_cast<bool>().unwrap());
	std::cout << "According to reflection, car is " << (insured ? "" : "NOT ") << "insured" << std::endl;

	//Give the car insurance now
	silica::reflection::reflect(insuredVar).get<silica::Bool>().set(true);
	std::cout << "THE INSURANCE WIZARD HATH SPOKEN! ABRA-CADRABA-INSURANCE!" << std::endl;
	insured = *(insuredVar.rt_cast<bool>().unwrap());
	std::cout << "According to reflection, car is " << (insured ? "" : "NOT ") << "insured" << std::endl;

	//What color is the car?
	Color carColor = car.whatColorAmI();
	std::cout << "The car is " << silica::reflection::reflect(&carColor).get<silica::Enum>().to_string() << std::endl;

	//Let's recolor the car
	car.refinish(Color::Black);
	std::cout << "Imma recolor the car." << std::endl;
	carColor = car.whatColorAmI();
	std::cout << "The car is " << silica::reflection::reflect(&carColor).get<silica::Enum>().to_string() << std::endl;

	//By the way, sat radio?
	std::cout << "By the way, the car does " << (car.hasSatRadio ? "" : "NOT ") << "have satellite radio. Reflection just can't see it because we marked it as ignored." << std::endl;

	//Recolor the car via reflection
	std::cout << "Anyways, let's recolor the car with reflection" << std::endl;
	int cost = info.get<silica::Object>().get_method("refinish").unwrap().invoke<int>(Color::Yellow).unwrap();
	carColor = car.whatColorAmI();
	std::cout << "The car is " << silica::reflection::reflect(&carColor).get<silica::Enum>().to_string() << std::endl;
	std::cout << "Refinishing it cost $" << cost << " though :(" << std::endl;

	//Direct private field access
	std::cout << "Why not do it for free? Unleash the direct private field access!" << std::endl;
	silica::reflection::reflect(info.get<silica::Object>().get_field("color").unwrap().var()).get<silica::Enum>().parse("White").unwrap();
	carColor = car.whatColorAmI();
	std::cout << "The car is " << silica::reflection::reflect(&carColor).get<silica::Enum>().to_string() << std::endl;

	//Done
	std::cout << "Thanks for checking out the Silica demo!" << std::endl;

	return 0;
}