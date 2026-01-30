#pragma once

#include "Repo.h"

class UndoAction {
public:
	virtual void do_undo() = 0;
	virtual void do_redo() = 0;
	virtual ~UndoAction() {};
};

class UndoAdd : public UndoAction {
private:
	Dog added_dog;
	Repository& repo;

public:
	UndoAdd(Repository& rep, const Dog& d) : repo(rep), added_dog(d) {}

	void do_undo() {
		repo.remove(added_dog.get_id());
	}

	void do_redo() {
		repo.add(added_dog);

	}
};

class UndoRemove : public UndoAction {
private:
	Dog removed_dog;
	Repository& repo;

public:
	UndoRemove(Repository& rep, const Dog& d) : repo(rep), removed_dog(d) {}

	void do_undo() {
		repo.add(removed_dog);
	}

	void do_redo() {
		repo.remove(removed_dog.get_id());
	}
};

class UndoUpdate : public UndoAction{
private:
	Dog old_dog, new_dog;
	Repository& repo;

public:
	UndoUpdate(Repository& rep, const Dog& d1, const Dog& d2) : repo(rep), old_dog(d1) , new_dog(d2) {}

	void do_undo() {
		repo.update(old_dog);
	}

	void do_redo() {
		repo.update(new_dog);
	}
};