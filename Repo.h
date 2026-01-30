#pragma once

#include "Domain.h"
#include <vector>
#include <iostream>


class Repository {
protected:
	std::vector<Dog>* data;

public:
	Repository(std::vector<Dog>* repo_array);

	virtual void initialise_repo();

	virtual void add(Dog new_dog);

	virtual void remove(int dog_id);

	virtual void update(Dog new_dog);

	virtual int get_position(int dog_id);

	virtual int get_length();

	virtual Dog get_element(int position);

	virtual Dog* get_dogs();

	virtual std::vector<Dog> get_dogs_vector();
	~Repository();
};

class FileRepository : public Repository
{
private:
	std::string file_name;

public:
	FileRepository(std::vector<Dog>* repo_array, std::string file_name);

	void load_file();

	void write_to_file();

	void initialise_repo() override;

	void add(Dog new_dog) override;

	void remove(int dog_id) override;

	void update(Dog new_dog) override;

	std::vector<Dog> get_dogs_vector() override;

	//int get_position(int dog_id);

	//int get_length();

	//Dog get_element(int position);

	//Dog* get_dogs();

	~FileRepository();
};
