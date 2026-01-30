#include "PetSheltQt.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QErrorMessage>
#include <QMessageBox>
#include <QGradient>
#include <qpainter.h>
#include <qshortcut.h>
#include <qtableview.h>
#include <qheaderview.h>

using namespace std;

PetSheltQt::PetSheltQt(Service* sv, UserService* us_sv)
{
    this->serv = sv;
    this->user_sv = us_sv;
    this->title_widget = new QLabel(this);
    this->admin_button = new QPushButton(this);
    this->user_button = new QPushButton(this);
    this->init_gui();
    this->connect_signal_and_slots();
    ui.setupUi(this);
}

PetSheltQt::~PetSheltQt() = default;

void PetSheltQt::init_gui()
{
    auto* layout = new QVBoxLayout(this);
    QFont title_font = this->title_widget->font();
    this->title_widget->setText("<p style='text-align:center'><font color=#4D5D52>Welcome to the DogShelter! <br> Please select your mode!</font></p>");
    title_font.setItalic(true);
    title_font.setPointSize(14);
    title_font.setStyleHint(QFont::System);
    this->title_widget->setFont(title_font);

    layout->addWidget(this->title_widget);
    this->admin_button->setText("Admin mode ;)");
    layout->addWidget(this->admin_button);
    this->user_button->setText("User mode");
    layout->addWidget(this->user_button);
    this->setLayout(layout);
    this->setStyleSheet("background - color:#FDEADA");
}

void PetSheltQt::connect_signal_and_slots()
{
    QObject::connect(this->admin_button, &QPushButton::clicked, this, &PetSheltQt::show_admin);
    QObject::connect(this->user_button, &QPushButton::clicked, this, &PetSheltQt::show_user);
}

void PetSheltQt::show_admin()
{
    QWidget* admin = new AdminGUI(NULL, this->serv);
    admin->showNormal();
}

void PetSheltQt::show_user()
{
    QWidget* user = new UserGUI(NULL, this->serv, this->user_sv);
    user->showNormal();
}

AdminGUI::AdminGUI(QWidget* parent, Service* serv)
{
    setParent(parent);
    this->serv = serv;
    this->title_widget = new QLabel(this);
    this->dog_list_widget = new QListWidget();
    this->id_line_edit = new QLineEdit{};
    this->name_line_edit = new QLineEdit{};
    this->breed_line_edit = new QLineEdit{};
    this->age_line_edit = new QLineEdit{};
    this->link_line_edit = new QLineEdit{};
    this->add_button = new QPushButton("Add");
    this->delete_button = new QPushButton("Delete");
    this->update_button = new QPushButton("Update");
    this->undo_button = new QPushButton("Undo");
    this->redo_button = new QPushButton("Redo");
    this->chart_button = new QPushButton("Display chart");

    
    this->init_admin_gui();
    this->connect_signal_and_slots();
    this->populate_list();

}

AdminGUI::~AdminGUI() = default;

void AdminGUI::init_admin_gui()
{
    auto* layout = new QVBoxLayout(this);
    QFont title_font = this->title_widget->font();
    this->title_widget->setText("<p style='text-align:center'><font color=#4D5D52>ADMIN MODE</font></p>");
    title_font.setItalic(true);
    title_font.setPointSize(14);
    title_font.setStyleHint(QFont::System);
    this->title_widget->setFont(title_font);
    layout->addWidget(this->title_widget);
    layout->addWidget(this->dog_list_widget);

    auto* dog_details_layout = new QFormLayout{};
    dog_details_layout->addRow("ID", this->id_line_edit);
    dog_details_layout->addRow("Name", this->name_line_edit);
    dog_details_layout->addRow("Breed", this->breed_line_edit);
    dog_details_layout->addRow("Age", this->age_line_edit);
    dog_details_layout->addRow("Link", this->link_line_edit);
    layout->addLayout(dog_details_layout);

    auto* buttons_layout = new QGridLayout{};
    buttons_layout->addWidget(this->add_button, 0, 0);
    buttons_layout->addWidget(this->delete_button, 0, 1);
    buttons_layout->addWidget(this->update_button, 0, 2);
    buttons_layout->addWidget(this->undo_button, 1, 0);
    buttons_layout->addWidget(this->redo_button, 1, 1);
    buttons_layout->addWidget(this->chart_button, 1, 2);

    layout->addLayout(buttons_layout);

    QLinearGradient linearGrad(QPointF(100, 100), QPointF(200, 200));
    linearGrad.setColorAt(0, QColor(100, 120, 140));
    linearGrad.setColorAt(0.5, QColor(170, 185, 220));
    linearGrad.setColorAt(1, QColor(160, 180, 200));
    QPalette palette = qApp->palette();
    palette.setBrush(QPalette::Base, linearGrad);
    palette.setBrush(QPalette::Highlight, linearGrad);
    palette.setBrush(QPalette::HighlightedText, Qt::white);
    palette.setBrush(QPalette::Text, Qt::white);
    this->dog_list_widget->setPalette(palette);
}

void AdminGUI::populate_list()
{
    this->dog_list_widget->clear();
    Dog* dogs = this->serv->get_dogs_service();
    for (int i = 0; i < this->serv->get_length_service(); ++i)
        this->dog_list_widget->addItem(QString::fromStdString(dogs[i].get_name()));
}

void AdminGUI::connect_signal_and_slots()
{
    QObject::connect(this->dog_list_widget, &QListWidget::itemSelectionChanged, [this]() {
        int index = this->get_selected_index();
        if (index == -1) return;
        Dog dog = this->serv->get_dogs_service()[index];
        this->id_line_edit->setText(QString::fromStdString(to_string(dog.get_id())));
        this->name_line_edit->setText(QString::fromStdString(dog.get_name()));
        this->breed_line_edit->setText(QString::fromStdString(dog.get_breed()));
        this->age_line_edit->setText(QString::fromStdString(to_string(dog.get_age())));
        this->link_line_edit->setText(QString::fromStdString(dog.get_photograph()));
    });

    QObject::connect(this->add_button, &QPushButton::clicked, this, &AdminGUI::gui_add_dog);
    QObject::connect(this->delete_button, &QPushButton::clicked, this, &AdminGUI::gui_delete_dog);
    QObject::connect(this->update_button, &QPushButton::clicked, this, &AdminGUI::gui_update_dog);
    QObject::connect(this->undo_button, &QPushButton::clicked, this, &AdminGUI::gui_undo);
    QObject::connect(this->redo_button, &QPushButton::clicked, this, &AdminGUI::gui_redo);
    QObject::connect(this->chart_button, &QPushButton::clicked, this, &AdminGUI::display_chart);

    auto* ptr1 = new QShortcut(QKeyCombination(Qt::KeyboardModifier::ControlModifier, Qt::Key_Z), this);
    QObject::connect(ptr1, SIGNAL(activated()), SLOT(gui_undo()));
    auto* ptr2 = new QShortcut(QKeyCombination(Qt::KeyboardModifier::ControlModifier, Qt::Key_Y), this);
    QObject::connect(ptr2, SIGNAL(activated()), SLOT(gui_redo()));
}


string AdminGUI::make_string_lower(string str)
{
    for (int i = 0; i < str.length(); i++)
        str[i] = tolower(str[i]);
    return str;
}


bool AdminGUI::validate_string(string something)
{
    for (int i = 0; i < something.length(); i++)
        if (isdigit(something[i]) == true)
            return false;
    return true;
}
void AdminGUI::gui_add_dog()
{
    string id_s = this->id_line_edit->text().toStdString();
    string breed = this->breed_line_edit->text().toStdString();
    string name = this->name_line_edit->text().toStdString();
    string age_s = this->age_line_edit->text().toStdString();
    string link = this->link_line_edit->text().toStdString();
    int age, id;
    try {
        if (!validate_string(breed) || breed.length() == 0) throw("Invalid input.");
        if (!validate_string(name) || name.length() == 0) throw("Name is not valid.");
        if (link.length() == 0) { throw ("Photograph link is not valid."); }
        id = stoi(id_s);
        age = stoi(age_s);
        if (id <= 0) throw("ID must be a positive number.");
        if (age <= 0) throw("Age must be a positive number.");
        this->serv->add_elem_service(id, breed, name, link, age);
        this->populate_list( );
    }
    catch (exception& e) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(e.what());
        error->setWindowTitle("Invalid input!");
        error->exec();
    }
}

void AdminGUI::gui_delete_dog()
{
    try {
        string id_s = this->id_line_edit->text().toStdString();
        int id = stoi(id_s);
        if (id <= 0) throw("ID must be a positive number.");
        this->serv->delete_elem_service(id);
        this->populate_list();
    }
    catch (exception& e) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(e.what());
        error->setWindowTitle("Invalid input!");
        error->exec();
    }
}

void AdminGUI::gui_update_dog()
{
    int index = this->get_selected_index();
    try {
        if (index < 0) {
            auto* error = new QMessageBox();
            error->setIcon(QMessageBox::Critical);
            error->setText("No dog selected!");
            error->setWindowTitle("Selection error!");
            error->exec();
        }
        else {
            string dog_id_s = this->id_line_edit->text().toStdString();
            int dog_id = stoi(dog_id_s);
            if (dog_id <= 0) throw("ID must be a positive number.");
            string new_name = this->name_line_edit->text().toStdString();
            string new_breed = this->breed_line_edit->text().toStdString();
            string new_link = this->link_line_edit->text().toStdString();
            string new_age = this->age_line_edit->text().toStdString();
            if (!validate_string(new_breed) || new_breed.length() == 0) throw("Invalid input.");
            if (!validate_string(new_name) || new_name.length() == 0) throw("Name is not valid.");
            if (new_link.length() == 0) throw("Invalid input.");
            int age = stoi(new_age);
            if (age <= 0) throw("Age must be a positive number.");
            this->serv->update_elem_service(dog_id, new_breed, new_name, new_link, age);
            this->populate_list();
        }
    }
    catch (exception& e) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(e.what());
        error->setWindowTitle("Invalid input!");
        error->exec();
    }
}

void AdminGUI::display_chart()
{
    DogListModel* dog_list = new DogListModel(this->serv->get_vector_sv());
    QWidget* list_widget = new QWidget{};
    QTableView* table = new QTableView();
    table->setModel(dog_list);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    list_widget->setMinimumWidth(table->width());
    QVBoxLayout* layout = new QVBoxLayout(list_widget);
    layout->addWidget(table);
    list_widget->show();

}

void AdminGUI::gui_undo()
{
    try {
        this->serv->undo();
        this->populate_list();
    } 
    catch (ServiceException& e) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(e.what());
        error->setWindowTitle("Invalid action!");
        error->exec();
    }
   
}

void AdminGUI::gui_redo()
{
    try {
        this->serv->redo();
        this->populate_list();
    }
    catch (ServiceException& e) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(e.what());
        error->setWindowTitle("Invalid action!");
        error->exec();
    }
}



void AdminGUI::key_press_event(QKeyEvent* ev)
{
    if (ev->keyCombination() == QKeyCombination(Qt::KeyboardModifier::ControlModifier, Qt::Key_Z)) { gui_undo(); }
    if (ev->keyCombination() == QKeyCombination(Qt::KeyboardModifier::ControlModifier, Qt::Key_Y)) { gui_redo();  }

}

int AdminGUI::get_selected_index() const
{
    QModelIndexList selected_indexes = this->dog_list_widget->selectionModel()->selectedIndexes();
    if (selected_indexes.isEmpty()) {
        this->id_line_edit->clear();
        this->name_line_edit->clear();
        this->breed_line_edit->clear();
        this->age_line_edit->clear();
        this->link_line_edit->clear();
        return -1;
    }
    int selected_index = selected_indexes.at(0).row();
    return selected_index;
}

UserGUI::UserGUI(QWidget* parent, Service* serv, UserService* us_sv)
{
    this->serv = serv;
    this->user_sv = us_sv;
    this->title_widget = new QLabel(this);
    this->adoption_list_widget = new QListWidget{};
    this->dog_list_widget = new QListWidget();
    this->filter_dog_list_widget = new QListWidget();
    this->id_line_edit = new QLineEdit{};
    this->name_line_edit = new QLineEdit{};
    this->breed_line_edit = new QLineEdit{};
    this->age_line_edit = new QLineEdit{};
    this->link_line_edit = new QLineEdit{};
    this->filter_line_edit = new QLineEdit{};
    this->breed_filter_line_edit = new QLineEdit{};
    this->age_filter_line_edit = new QLineEdit{};
    this->add_button = new QPushButton("Add to the adoption list");
    this->filter_button = new QPushButton("Filter the dogs");
    this->open_list_button = new QPushButton("Open file");
    this->csv_button = new QRadioButton("CSV");
    this->html_button = new QRadioButton("HTML");
    this->repo_type_selected = false;
    this->filtered = false;
    setParent(parent);
    setWindowFlag(Qt::Window);
    this->init_user_gui();
    this->populate_dog_list();
    this->connecting_signals_and_slots();
}

UserGUI::~UserGUI() = default;

void UserGUI::populate_dog_list()
{
    this->dog_list_widget->clear();
    Dog* all_dogs = this->serv->get_dogs_service();
    for (int i = 0; i < this->serv->get_length_service(); ++i)
        this->dog_list_widget->addItem(QString::fromStdString(all_dogs[i].get_name()));
}

void UserGUI::populate_adoption_list()
{
    this->adoption_list_widget->clear();
    Dog* all_dogs = this->user_sv->get_dogs_wishlist_service();
    for (int i = 0; i < this->user_sv->get_lenght_service_user(); i++)
        this->adoption_list_widget->addItem(QString::fromStdString(all_dogs[i].get_name()));
}

void UserGUI::connecting_signals_and_slots()
{
    QObject::connect(this->dog_list_widget, &QListWidget::clicked, [this]() {
        string dog_name = this->dog_list_widget->selectedItems().at(0)->text().toStdString();
        int index = this->serv->find_by_name(dog_name);
        Dog dog = this->serv->get_dogs_service()[index];
        this->id_line_edit->setText(QString::fromStdString(to_string(dog.get_id())));
        this->name_line_edit->setText(QString::fromStdString(dog.get_name()));
        this->breed_line_edit->setText(QString::fromStdString(dog.get_breed()));
        this->age_line_edit->setText(QString::fromStdString(to_string(dog.get_age())));
        this->link_line_edit->setText(QString::fromStdString(dog.get_photograph()));
        string link = string("start ").append(dog.get_photograph());
        system(link.c_str());
        });

    QObject::connect(this->csv_button, &QRadioButton::clicked, [this]() {
      //  this->user_sv->repository_type("csv");
        this->repo_type_selected = true;
        });

    QObject::connect(this->html_button, &QRadioButton::clicked, [this]() {
   //     this->user_sv->repository_type("html");
        this->repo_type_selected = true;
        });

    QObject::connect(this->open_list_button, &QPushButton::clicked, [this]() {
        if (!this->repo_type_selected) {
            auto* error = new QMessageBox();
            error->setIcon(QMessageBox::Warning);
            error->setText("Please select the type of file you want!");
            error->setWindowTitle("File type warning!");
            error->exec();
        }
        else {
            string link = string("start ").append(this->user_sv->get_file_name_service());
            system(link.c_str());
        }
        });

    QObject::connect(this->add_button, &QPushButton::clicked, this, &UserGUI::gui_add_dog);
    QObject::connect(this->filter_button, &QPushButton::clicked, this, &UserGUI::gui_filter_dogs);

    QObject::connect(this->filter_line_edit, &QLineEdit::textChanged, this, &UserGUI::gui_filter_dogs_activity);
}

void UserGUI::init_user_gui()
{
    auto* layout = new QVBoxLayout(this);
    QFont title_font = this->title_widget->font();
    this->title_widget->setText("<p style='text-align:center'><font color=#4D5D52>USER MODE <br> Select the type of file you want for saving your adopted dogs!</font></p>");
    title_font.setItalic(true);
    title_font.setPointSize(14);
    title_font.setStyleHint(QFont::System);
    this->title_widget->setFont(title_font);
    layout->addWidget(this->title_widget);

    auto* radio_buttons_layout = new QGridLayout(this);
    radio_buttons_layout->addWidget(this->csv_button, 0, 0);
    radio_buttons_layout->addWidget(this->html_button, 1, 0);
    radio_buttons_layout->addWidget(this->open_list_button, 0, 1);
    layout->addLayout(radio_buttons_layout);

    auto* list_layout = new QGridLayout(this);
    list_layout->addWidget(this->dog_list_widget, 0, 0);
    list_layout->addWidget(this->adoption_list_widget, 0, 0);
    layout->addLayout(list_layout);

    auto* dog_details_layout = new QFormLayout{};
    dog_details_layout->addRow("ID", this->id_line_edit);
    dog_details_layout->addRow("Name", this->name_line_edit);
    dog_details_layout->addRow("Breed", this->breed_line_edit);
    dog_details_layout->addRow("Age", this->age_line_edit);
    dog_details_layout->addRow("Link", this->link_line_edit);
    dog_details_layout->addRow(this->add_button);
    dog_details_layout->addRow(this->filter_button);
    layout->addLayout(dog_details_layout);

    auto *filter_title1 = new QLabel("<p style='text-align:center'><font color=#4D2D52><br>Filter the available dogs by a substring.</font></p>");
    QFont filter_font1 = filter_title1->font();
    filter_font1.setItalic(true);
    filter_font1.setPointSize(14);
    filter_font1.setStyleHint(QFont::System);
    layout->addWidget(filter_title1);



    auto* list_filtered_layout = new QGridLayout(this);
    list_filtered_layout->addWidget(this->filter_dog_list_widget, 0, 0);
    layout->addLayout(list_filtered_layout);

    auto* dog_filter_layout = new QFormLayout{};
    dog_details_layout->addRow(this->filter_line_edit);
    layout->addLayout(dog_filter_layout);
    //

    auto* filter_title = new QLabel("<p style='text-align:center'><font color=#4D2D52><br>Filter the available dogs by breed and age</font></p>");
    QFont filter_font = filter_title->font();
    filter_font.setItalic(true);
    filter_font.setPointSize(14);
    filter_font.setStyleHint(QFont::System);
    layout->addWidget(filter_title);

    auto* filter_details_layout = new QFormLayout{};
    filter_details_layout->addRow("Breed", this->breed_filter_line_edit);
    filter_details_layout->addRow("Age", this->age_filter_line_edit);
    layout->addLayout(filter_details_layout);
}

int UserGUI::get_selected_index() const
{
    QModelIndexList selected_indexes = this->dog_list_widget->selectionModel()->selectedIndexes();
    if (selected_indexes.isEmpty())
    {
        this->id_line_edit->clear();
        this->name_line_edit->clear();
        this->breed_line_edit->clear();
        this->age_line_edit->clear();
        this->link_line_edit->clear();

        return -1;
    }
    int selected_index = selected_indexes.at(0).row();
    return selected_index;
}

void UserGUI::gui_add_dog()
{
    if (!this->repo_type_selected)
    {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText("Please select the type of file that you want!");
        error->setWindowTitle("File type error.");
        error->exec();
    }
    else {
        string id_s = this->id_line_edit->text().toStdString();
        string breed = this->breed_line_edit->text().toStdString();
        string name = this->name_line_edit->text().toStdString();
        string age_s = this->age_line_edit->text().toStdString();
        string link = this->link_line_edit->text().toStdString();
        int id, age;
        try {
            if (!validate_string(breed) || breed.length() == 0) throw("Invalid input.");
            if (!validate_string(name) || name.length() == 0) throw("Name is not valid.");
            if (link.length() == 0) { throw ("Photograph link is not valid."); }
            id = stoi(id_s);
            age = stoi(age_s);
            if (id <= 0) throw("ID must be a positive number.");
            if (age <= 0) throw("Age must be a positive number.");
            Dog dog = Dog(id, breed, name, link, age);
            this->user_sv->add_dog_wishlist_service(dog);
            if (!this->filtered) {
                this->populate_dog_list();
            }
            else this->adoption_list_widget->addItem(this->dog_list_widget->takeItem(this->get_selected_index()));
        }
        catch (exception& e)
        {
            auto* error = new QMessageBox();
            error->setIcon(QMessageBox::Critical);
            error->setText(e.what());
            error->setWindowTitle("Error at adding dog!");
            error->exec();
        }
    }
}

void UserGUI::gui_filter_dogs()
{
    try {
        string breed_filter = this->breed_filter_line_edit->text().toStdString();
        string age_filter = this->age_filter_line_edit->text().toStdString();
        this->adoption_list_widget->clear();

        if (breed_filter.empty() && age_filter.empty()) {
            this->filtered = false;
            this->populate_dog_list();
        }
        else {
            if (!validate_string(breed_filter) || breed_filter.length() == 0) throw("Invalid input.");
            int age = stoi(age_filter);
            if (age <= 0) throw("Age is not valid.");
            Dog* dogs = this->serv->get_dogs_service();
            int repo_len = this->serv->get_length_service();
            Dog* dogs_filtered = new Dog[repo_len];
            int length = this->user_sv->filter_dogs(breed_filter, age, dogs, dogs_filtered, repo_len);

            this->filtered = true;
            this->dog_list_widget->clear();
            for (int i = 0; i < length; i++)
                this->adoption_list_widget->addItem(QString::fromStdString(dogs_filtered[i].get_name()));
            delete[] dogs_filtered;
        }
    }
    catch (exception& e) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(e.what());
        error->setWindowTitle("Filter error!");
        error->exec();
    }
}

bool UserGUI::validate_string(std::string something)
{
    for (int i = 0; i < something.length(); i++)
        if (isdigit(something[i]) == true)
            return false;
    return true;
}

void UserGUI::gui_filter_dogs_activity()
{
    this->filter_dog_list_widget->clear();
    string substr = this->filter_line_edit->text().toStdString();
    //this->filter_dog_list_widget->addItem(QString::fromStdString(substr));
    Dog* all_dogs = this->serv->get_dogs_service();

    for (int i = 0; i < this->serv->get_length_service(); i++)
    {
        if (all_dogs[i].get_name().find(substr,0) != string::npos)
        {
            this->filter_dog_list_widget->addItem(QString::fromStdString(all_dogs[i].get_name()));
        }
    }
}


DogListModel::DogListModel(std::vector<Dog> dt)
{
    this->dogs = dt;
}

int DogListModel::rowCount(const QModelIndex& parent) const
{
    return dogs.size();
}

int DogListModel::columnCount(const QModelIndex& parent) const
{
    return 5;
}

QVariant DogListModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int column = index.column();

    Dog p = this->dogs[row];

    if (role == Qt::DisplayRole)
    {
        switch (column)
        {
        case 0:
            return QString::fromStdString(to_string(p.get_id()));
        case 1:
            return QString::fromStdString(p.get_name());
        case 2:
            return QString::fromStdString(p.get_breed());
        case 3:
            return QString::fromStdString(to_string(p.get_age()));
        case 4:
            return QString::fromStdString(p.get_photograph());
        default:
            break;
        }
    }
    return QVariant();
}

void DogListModel::clear_data()
{
    this->beginResetModel();

    this->endResetModel();
}

void DogListModel::propagate()
{
    emit layoutChanged();
}
