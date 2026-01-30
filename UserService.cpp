#include "UserService.h"
#include <vector>
#include "HTMLUserRepo.h"
#include "CSVUserRepo.h"

UserServiceException::UserServiceException(std::string& message_error) : message(message_error) {}

const char* UserServiceException::what() const noexcept
{
	return this->message.c_str();
}


UserService::UserService(UserRepo* user_repository)
{
	this->user_repo = user_repository;
	this->repo_type_selected = false;
}

UserService::UserService()
{
	this->repo_type_selected = false;
}

void UserService::add_dog_wishlist_service(Dog new_dog)
{
	this->user_repo->add_whishlist(new_dog);
}

int UserService::get_lenght_service_user()
{
	return this->user_repo->get_length_user();
}

Dog* UserService::get_dogs_wishlist_service()
{
	return this->user_repo->get_dogs_user();
}

std::string UserService::get_file_name_service()
{
	return this->user_repo->get_file_name();
}

int UserService::filter_dogs(std::string breed, int age, Dog* dogs_list, Dog* dogs_list_filtered, int length)
{
	int dogs_filtered_length = 0;

	for (int i = 0; i < length; i++)
	{
		if (dogs_list[i].get_breed() == breed && dogs_list[i].get_age() < age)
			dogs_list_filtered[dogs_filtered_length++] = dogs_list[i];
	}


	if (dogs_filtered_length <= 0)
	{
		std::string error;
		error += std::string("There aren't any dogs that obey the filters.");
		throw(UserServiceException(error));
	}
	return dogs_filtered_length;
}

void UserService::repository_type(const std::string& file_type)
{
	Dog* repo;
	std::vector<Dog> repo_vector;
	std::string user_file;
	if (file_type == "csv") {
		user_file = "dogs.csv";
		if (!this->repo_type_selected) {
			this->repo_type_selected = true;
		}
		else {
			for (int i = 0; i < this->user_repo->get_length_user(); i++)
				repo_vector.push_back(repo[i]);
		}
		auto* repo = new CSVUserRepo(&repo_vector, user_file);
		this->user_repo = repo;
		this->user_repo->write_file_user();
	}
	if (file_type == "html") {
		user_file = "dogs.html";
		if (!this->repo_type_selected) {
			this->repo_type_selected = true;
		}
		else {
			for (int i = 0; i < this->user_repo->get_length_user(); i++)
				repo_vector.push_back(repo[i]);
		}
		auto* repo = new HtmlUserRepo(&repo_vector, user_file);
		this->user_repo = repo;
		this->user_repo->write_file_user();
	}
}

UserService::~UserService() = default;


