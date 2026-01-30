#include "CSVUserRepo.h"


CSVUserRepo::CSVUserRepo(std::vector<Dog>* repo_array, std::string file_name)
	: UserRepoFile(repo_array, file_name) {}

CSVUserRepo::~CSVUserRepo() = default;