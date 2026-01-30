#include "HTMLUserRepo.h"
#include <fstream>

using namespace std;

HtmlUserRepo::HtmlUserRepo(std::vector<Dog>* repo_array, std::string file_name)
	: UserRepoFile(repo_array, file_name) {}

void HtmlUserRepo::write_file_user()
{
	ofstream fout(this->file_name_user);
	fout << "<!DOCTYPE html>\n<html><head><title>Adoption List</title></head><body>\n";
	fout << "<table border=\"1\">\n";
	fout << "<tr><td>Breed</td><td>Name</td><td>Age</td><td>Link</td></tr>\n";
	for (Dog& dog : *this->data)
	{
		fout << "<tr><td>" << dog.get_breed() << "</td>" << "<td>" << dog.get_name() << "</td>" << "<td>" << dog.get_age() << "</td>"
			<< "<td><a href=\"" << dog.get_photograph() << "\">" << dog.get_photograph() << "</a></td>\n";
	}
	fout << "</table></body></html>";
	fout.close();
}

HtmlUserRepo::~HtmlUserRepo() = default;
