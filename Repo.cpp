#include "Repo.h"
#include <fstream>
#include <algorithm>

Repository::Repository(std::vector<Dog>* repo_array)
{
	this->data = repo_array;

	initialise_repo();
}

void Repository::initialise_repo()
{
	add(Dog(1, "Labrador", "Johnny", "https://www.wowwow.ro/labrador-retriever-caine/2155", 5));
	add(Dog(2, "Corgi", "Alfie", "https://www.wowwow.ro/welsh-corgi-pembroke-caine/2332", 2));
	add(Dog(3, "Husky", "Ice", "https://www.wowwow.ro/husky-caine/2152", 3));
	add(Dog(4, "Golden Retriever", "Sarah", "https://www.wowwow.ro/golden-retriever-caine/2151", 5));
	add(Dog(5, "Chihuahua", "Killer", "https://www.wowwow.ro/chihuahua-caine/2143", 3));
	add(Dog(6, "Labrador", "Aurelian", "https://www.wowwow.ro/labrador-retriever-caine/2155", 6));
	add(Dog(7, "German Shepherd", "Ilie", "https://www.wowwow.ro/ciobanesc-german-caine/2145", 10));
	add(Dog(8, "Labrador", "Dash", "https://www.wowwow.ro/labrador-retriever-caine/2155", 4));
	add(Dog(9, "Doberman", "Tara", "https://www.wowwow.ro/doberman-caine/2149", 7));
	add(Dog(10, "Corgi", "Rita", "https://www.wowwow.ro/welsh-corgi-pembroke-caine/2332", 2));
}

void Repository::add(Dog new_dog)
{
	this->data->push_back(new_dog);
}

void Repository::remove(int dog_id)
{
	int const position = get_position(dog_id);
	this->data->erase(this->data->begin() + position);
}

void Repository::update(Dog new_dog)
{
	int const position = get_position(new_dog.get_id());
	this->data->erase(this->data->begin() + position);
	this->data->insert(this->data->begin() + position, new_dog);
}

int Repository::get_position(int dog_id)
{
	int count = 0;
	for (Dog& it : *this->data)
	{
		if (it.get_id() == dog_id) return count;
		count++;
	}
	return -1;
}

int Repository::get_length()
{
	return this->data->size();
}

Dog Repository::get_element(int position)
{
	return this->data->at(position);
}

Dog* Repository::get_dogs()
{
	return this->data->data();
}

std::vector<Dog> Repository::get_dogs_vector()
{
	return std::vector<Dog>();
}

Repository::~Repository() = default;


// ======================= File Repo ==============================


FileRepository::FileRepository(std::vector<Dog>*repo_array, std::string file_name)
	:Repository(repo_array)
{
	this->file_name = file_name;


void FileRepository::load_file()
{
	if (!this->file_name.empty())
	{
		Dog new_dog;
		std::ifstream fin(this->file_name);
		while (fin >> new_dog)
		{
			if (std::find(this->data->begin(), this->data->end(), new_dog) == this->data->end())
				this->data->push_back(new_dog);
		}
		fin.close();
	}
}

void FileRepository::write_to_file()
{
	if (!this->file_name.empty())
	{
		std::ofstream fout(this->file_name);
		for (Dog& const dog : *this->data)
		{
			fout << dog << "\n";
		}
		fout.close();
	}
}

void FileRepository::initialise_repo()
{
	this->load_file();
}

void FileRepository::add(Dog new_dog)
{
	this->data->push_back(new_dog);
	write_to_file();
}

void FileRepository::remove(int dog_id)
{
	int const position = this->get_position(dog_id);
	this->data->erase(this->data->begin() + position);
	write_to_file();
}

void FileRepository::update(Dog new_dog)
{
	int const position = get_position(new_dog.get_id());
	this->data->erase(this->data->begin() + position);
	this->data->insert(this->data->begin() + position, new_dog);
	write_to_file();
}

std::vector<Dog> FileRepository::get_dogs_vector()
{
	return *this->data;
}

FileRepository::~FileRepository() = default;
