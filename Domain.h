#pragma once
#include <iostream>

class Dog {
private:
	std::string Breed, Name, Photograph;
	int Age, Dog_id;

public:

	// The constructor function - creates an object Dog
	Dog(int dog_id = 0, std::string breed = "", std::string name = "", std::string photograph = "", int  age = 0);

	// a function that returns the name of the dog
	std::string get_name();

	// a function that returns the id of the dog
	int get_id();

	// a function that returns the breed of the dog
	std::string get_breed();

	// a function that returns the photograph link of the dog
	std::string get_photograph();

	// a function that returns the age of the dog
	int get_age();

	void set_name(std::string name);

	void set_breed(std::string breed);

	void set_photograph(std::string photo);

	void set_age(int new_age);

	bool operator==(const Dog& dog_check) const;

	friend std::istream& operator>>(std::istream& input_stream, Dog& dog);

	friend std::ostream& operator<<(std::ostream& output_stream, const Dog& dog_out);
};
