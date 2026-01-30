#include "PetSheltQt.h"
#include <QtWidgets/QApplication>
#include "Service.h"
#include "UserRepo.h"
#include "CSVUserRepo.h"
#include "HTMLUserRepo.h"
#include "UserService.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vector<Dog> v1;
    FileRepository repo{ &v1, "dog.txt" };
    Service serv{ &repo };  
    vector<Dog> v2;
    HtmlUserRepo user_repo = HtmlUserRepo(&v2, "dogs.html");
    UserService user_sv{ &user_repo};

    PetSheltQt w{ &serv, &user_sv };
    w.show();
    return a.exec();
}
