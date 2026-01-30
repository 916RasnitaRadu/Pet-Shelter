#pragma once

#include "UserRepo.h"


class CSVUserRepo : public UserRepoFile
{
public:
	CSVUserRepo(std::vector<Dog>* repo_array, std::string file_name);

	~CSVUserRepo();
};
