#pragma once

#include "UserRepo.h"


class UserService {
private:
	UserRepo* user_repo;
	bool repo_type_selected;
public:
	// the constructor of the service of the user
	UserService(UserRepo* user_repository);

	explicit UserService();

	// a function that adds a dog to the user repo
	void add_dog_wishlist_service(Dog new_dog);

	// a function that returns the length of the user repo
	int get_lenght_service_user();

	// a function that returns the array of elements from the user repo
	Dog* get_dogs_wishlist_service();

	std::string get_file_name_service();

	// a function that receives a string breed, an integer age, the list of dogs from the repo, the length of that list and an empty array which will be
	// modified. The function adds in the second array the dogs with the breed and with the age less or equal than the given age. The function returns the
	// length of the created vector.
	int filter_dogs(std::string breed, int age, Dog* dogs_list, Dog* dogs_list_filtered, int length);

	void repository_type(const std::string& file_type);

	// class destructor
	~UserService();
};

class UserServiceException : public std::exception {
private:
	std::string message;
public:
	UserServiceException(std::string& message_error);

	const char* what() const noexcept override;
};
