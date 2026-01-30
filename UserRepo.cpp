#include "UserRepo.h"
#include <fstream>
#include <algorithm>


UserRepo::UserRepo() = default;

void UserRepo::initialise_user_repo()
{
}

void UserRepo::add_whishlist(Dog new_dog)
{
	this->data->push_back(new_dog);
}

Dog* UserRepo::get_dogs_user()
{
	return this->data->data();
}

int UserRepo::get_length_user()
{
	return this->data->size();
}

UserRepo::UserRepo(std::vector<Dog>*repo_array)
{
	this->data = repo_array;
}

UserRepo::~UserRepo() = default;

// =============== FileRepo ==============


UserRepoFile::UserRepoFile(std::vector<Dog>*repo_array, std::string file_name)
	:UserRepo(repo_array)
{
	this->file_name_user = file_name;
}

void UserRepoFile::load_file_user()
{
	if (!this->file_name_user.empty())
	{
		Dog dog;
		std::ifstream fin(this->file_name_user);
		while (fin >> dog)
		{
			if (std::find(this->data->begin(), this->data->end(), dog) == this->data->end())
				this->data->push_back(dog);
		}
		fin.close();
	}
}

void UserRepoFile::write_file_user()
{
	if (!this->data->empty())
	{
		std::ofstream fout(this->file_name_user);
		for (Dog& const dog : *this->data)
			fout << dog << "\n";
	}
}

void UserRepoFile::initialise_user_repo()
{
	this->load_file_user();
}

void UserRepoFile::add_whishlist(Dog new_dog)
{
	this->data->push_back(new_dog);
	write_file_user();
}

std::string UserRepoFile::get_file_name()
{
	return this->file_name_user;
}

UserRepoFile::~UserRepoFile() = default;