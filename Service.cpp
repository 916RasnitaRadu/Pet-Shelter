#include "Service.h"

ServiceException::ServiceException(std::string& message_error) : message(message_error) {}

const char* ServiceException::what() const noexcept
{
	return this->message.c_str();
}


Service::Service(Repository* repository)
{
	this->repo = repository;
}

void Service::add_elem_service(int dog_id, std::string breed, std::string name, std::string photograph, int age)
{
	if (this->repo->get_position(dog_id) != -1)
	{
		std::string error;
		error += std::string("There is already a dog with this id.");
		throw(ServiceException(error));
	}
	if (age <= 0)
	{
		std::string error;
		error += std::string("There is already a dog with this id.");
		throw(ServiceException(error));
	}
	Dog new_dog = Dog(dog_id, breed, name, photograph, age);
	this->repo->add(new_dog);

	this->undo_actions.push_back(std::make_unique<UndoAdd>(*this->repo, new_dog));
	this->redo_actions.clear();
}

void Service::delete_elem_service(int dog_id)
{
	if (this->repo->get_position(dog_id) == -1)
	{
		std::string error;
		error += std::string("There isn't any dog with this id in the shelter.");
		throw(ServiceException(error));
	}
	Dog deleted_dog = find_by_id(dog_id);
	this->repo->remove(dog_id);
	
	this->undo_actions.push_back(std::make_unique<UndoRemove>(*this->repo, deleted_dog));
	this->redo_actions.clear();
}

void Service::update_elem_service(int dog_id, std::string breed, std::string name, std::string photograph, int age)
{
	if (this->repo->get_position(dog_id) == -1)
	{
		std::string error;
		error += std::string("There isn't any dog with this id in the shelter.");
		throw(ServiceException(error));
	}
	if (age <= 0)
	{
		std::string error;
		error += std::string("The age is an invalid integer.");
		throw(ServiceException(error));
	}

	Dog new_dog = Dog(dog_id, breed, name, photograph, age);
	Dog old_dog = find_by_id(dog_id);
	this->repo->update(new_dog);

	this->undo_actions.push_back(std::make_unique<UndoUpdate>(*this->repo, old_dog, new_dog));
	this->redo_actions.clear();
}

int Service::get_length_service()
{
	return this->repo->get_length();
}

Dog Service::get_element_service(int pos)
{
	return this->repo->get_element(pos);
}

int Service::find_by_name(std::string dog_name)
{
	Dog* all_dogs = this->repo->get_dogs();
	for (int i = 0; i < this->repo->get_length(); i++)
	{
		if (all_dogs[i].get_name() == dog_name) return i;
	}
	return -1;
}

Dog Service::find_by_id(int id)
{
	Dog* dogs = this->repo->get_dogs();
	for (int i = 0; i < this->repo->get_length(); i++)
		if (dogs[i].get_id() == id) return dogs[i];
}

std::vector<Dog> Service::get_vector_sv()
{
	return this->repo->get_dogs_vector();
}

void Service::undo()
{
	if (undo_actions.empty())
	{
		std::string error;
		error += std::string("There are not any actions to undo.");
		throw(ServiceException(error));
	}
	
	std::unique_ptr<UndoAction> last = move(this->undo_actions.back());
	last->do_undo();

	this->undo_actions.pop_back();
	this->redo_actions.push_back(move(last));

}

void Service::redo()
{
	if (redo_actions.empty())
	{
		std::string error;
		error += std::string("There are not any actions to redo.");
		throw(ServiceException(error));
	}

	std::unique_ptr<UndoAction> last = move(this->redo_actions.back());
	last->do_redo();

	this->redo_actions.pop_back();
	this->undo_actions.push_back(move(last));
}

Repository* Service::get_repo()
{
	return this->repo;
}

Dog* Service::get_dogs_service()
{
	return this->repo->get_dogs();
}

Service::~Service() = default;

