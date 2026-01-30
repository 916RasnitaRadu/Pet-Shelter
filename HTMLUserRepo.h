#pragma once

#include "UserRepo.h"

class HtmlUserRepo : public UserRepoFile
{
public:
	HtmlUserRepo(std::vector<Dog>* repo_array, std::string file_name);

	void write_file_user() override;

	~HtmlUserRepo();
};
