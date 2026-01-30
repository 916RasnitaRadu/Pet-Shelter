#define _CRT_SECURE_NO_WARNINGS

#include "Domain.h"
#include <vector>
#include <utility>
#include <sstream>



Dog::Dog(int dog_id, std::string breed, std::string name, std::string photograph, int age)
{
	this->Dog_id = dog_id;
	this->Breed = breed;
	this->Name = name;
	this->Photograph = photograph;
	this->Age = age;

}

std::string Dog::get_name()
{
	return this->Name;
}

int Dog::get_id()
{
	return this->Dog_id;
}

std::string Dog::get_breed()
{
	return this->Breed;
}

std::string Dog::get_photograph()
{
	return this->Photograph;
}

int Dog::get_age()
{
	return this->Age;
}

void Dog::set_name(std::string name)
{
	this->Name = name;
}

void Dog::set_breed(std::string breed)
{
	this->Breed = breed;
}

void Dog::set_photograph(std::string photo)
{
	this->Photograph = photo;
}

void Dog::set_age(int new_age)
{
	this->Age = new_age;
}

bool Dog::operator==(const Dog& dog_check) const
{
	return this->Dog_id == dog_check.Dog_id;
}

std::istream& operator>>(std::istream& input_stream, Dog& dog)
{
	std::string line;
	std::getline(input_stream, line);
	std::vector<std::string> tokens;

	if (line.empty()) return input_stream;

	for (auto it = strtok(&line[0], ","); it != NULL; it = strtok(NULL, ","))
		tokens.push_back(it);

	dog.Dog_id = std::stoi(tokens[0]);
	dog.Name = tokens[1];
	dog.Breed = tokens[2];
	dog.Age = std::stoi(tokens[3]);
	dog.Photograph = tokens[4];

	return input_stream;

}

std::ostream& operator<<(std::ostream& output_stream, const Dog& dog_out)
{
	output_stream << dog_out.Dog_id << "," << dog_out.Name << "," << dog_out.Breed << "," << dog_out.Age << "," << dog_out.Photograph;
	return output_stream;
}
