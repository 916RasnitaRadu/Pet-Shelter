#pragma once

#include <QtWidgets/QWidget>
#include "ui_PetSheltQt.h"
#include "Service.h"
#include "UserService.h"
#include <qlabel.h>
#include <qpushbutton.h>
#include <QLineEdit>
#include <qlistwidget.h>
#include <qradiobutton.h>
#include <QKeyEvent>


class DogListModel : public QAbstractTableModel {
private:
    std::vector<Dog> dogs;

public:
    DogListModel(std::vector<Dog> dt);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    void clear_data();
    void propagate();
};

class PetSheltQt : public QWidget
{
private:
    Service* serv;
    UserService* user_sv;
    void init_gui();
    QLabel* title_widget;
    QPushButton* admin_button;
    QPushButton* user_button;
    void show_admin();
    void show_user();
    void connect_signal_and_slots(); 
    Ui::PetSheltQtClass ui;

public:
    PetSheltQt(Service* sv, UserService* us_sv);

    ~PetSheltQt();
};

class AdminGUI : public QWidget {
private:
    Service* serv;
    void init_admin_gui();
    QLabel* title_widget;
    QListWidget* dog_list_widget;
    QLineEdit* id_line_edit, *name_line_edit, * breed_line_edit, * age_line_edit, * link_line_edit;
    QPushButton* add_button, * delete_button, * update_button, *undo_button, *redo_button, *chart_button;
    DogListModel* list_model;
    QWidget* chart_window;

    void populate_list();
    void connect_signal_and_slots();
    void gui_add_dog();
    void gui_delete_dog();
    void gui_update_dog();
    void gui_undo();
    void gui_redo();
    void display_chart();
    void key_press_event(QKeyEvent* event);
    int get_selected_index() const;
    std::string make_string_lower(std::string str);
    bool validate_string(std::string something);

public:
    AdminGUI(QWidget* parent, Service* serv);
    ~AdminGUI();
};

class UserGUI : public QWidget {
private:
    UserService* user_sv;
    Service* serv;
    QLabel* title_widget;
    QListWidget* dog_list_widget, * adoption_list_widget, *filter_dog_list_widget;
    QLineEdit* name_line_edit, * id_line_edit, * breed_line_edit, * age_line_edit, * link_line_edit, * breed_filter_line_edit, * age_filter_line_edit, *filter_line_edit;
    QPushButton* add_button, * filter_button, * open_list_button;
    QRadioButton* csv_button, *html_button;
    bool repo_type_selected, filtered;
    void populate_dog_list();
    void populate_adoption_list();
    void connecting_signals_and_slots();
    void init_user_gui();
    int get_selected_index() const;
    void gui_add_dog();
    void gui_filter_dogs();
    bool validate_string(std::string something);
    void gui_filter_dogs_activity();
public:
    UserGUI(QWidget* parent, Service* serv, UserService* us_sv);
    ~UserGUI();
};
