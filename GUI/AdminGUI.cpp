//
// Created by Razvan Vranceanu on 07.05.2021.
//


#include <QApplication>
#include <QListWidget>
#include <QLineEdit>
#include <QFormLayout>
#include "AdminGUI.h"
#include "../errors/ValidError.h"
#include <iostream>
#include <QMessageBox>
#include <QShortcut>


std::string strip(std::string &s)
{
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) {
        start++;
    }

    auto end = s.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

AdminGUI::AdminGUI(AService &adminService, undo_redo &urm): adminService{adminService},undo_redo_manager{urm}{
    this->mainWindow();
    this->populateTutorialsList();
    this->connectSignalsAndSlots();
}

void AdminGUI::mainWindow() {
    this->setWindowTitle("Admin");
    this->resize(510, 590);
    auto* MainLayout = new QVBoxLayout{this};///main layout

    // tutorial list widget
    this->tutorialListWidget = new QListWidget{};
    MainLayout->addWidget(this->tutorialListWidget);

    //line edits
    this->titleLineEdit = new QLineEdit{};
    this->presenterLineEdit = new QLineEdit{};
    this->durationLineEditMin = new QLineEdit{};
    this->durationLineEditSec = new QLineEdit{};
    this->likesLineEdit = new QLineEdit{};
    this->linkLineEdit = new QLineEdit{};

    auto* tutorialDetails = new QFormLayout{ this }; ///layout
    tutorialDetails->addRow("Title", titleLineEdit);
    tutorialDetails->addRow("Presenter", presenterLineEdit);
    tutorialDetails->addRow("Duration (min)", durationLineEditMin);
    tutorialDetails->addRow("Duration (sec)", durationLineEditSec);
    tutorialDetails->addRow("Likes", likesLineEdit);
    tutorialDetails->addRow("Link", linkLineEdit);
    MainLayout->addLayout(tutorialDetails);

    // butoane add, update, delete
    auto* adminButtonsLayout = new QHBoxLayout {this}; ///layout cele 3 butoane
    this->adminAddButton = new QPushButton{"Add"};
    this->adminDeleteButton = new QPushButton{"Delete"};
    this->adminUpdateButton = new QPushButton{"Update"};
    adminButtonsLayout->addWidget(adminAddButton);
    adminButtonsLayout->addWidget(adminDeleteButton);
    adminButtonsLayout->addWidget(adminUpdateButton);

    MainLayout->addLayout(adminButtonsLayout);


    this->undoButton = new QPushButton{"Undo"};
    this->redoButton = new QPushButton{"Redo"};
    auto* undoRedoLayout = new QHBoxLayout{this};
    undoRedoLayout->addWidget(this->undoButton);
    undoRedoLayout->addWidget(this->redoButton);

    MainLayout->addLayout(undoRedoLayout);
}

void AdminGUI::populateTutorialsList() {
    this->tutorialListWidget->clear();
//    QFont f("San Francisco", 14);
//    this->tutorialListWidget->setFont(f);

    std::vector<Tutorial> tutorials_list = adminService.admin_service_get_all();

    for (auto& t : tutorials_list)
        this->tutorialListWidget->addItem(QString::fromStdString("title: " + t.get_title() + ",     presenter: " + t.get_presenter()));
}


void AdminGUI::connectSignalsAndSlots() {
    //connecting buttons
    QObject::connect(this->adminAddButton, &QPushButton::clicked, this, &AdminGUI::addTutorial);
    QObject::connect(this->adminDeleteButton, &QPushButton::clicked, this, &AdminGUI::deleteTutorial);
    QObject::connect(this->adminUpdateButton, &QPushButton::clicked, this, &AdminGUI::updateTutorial);

    QObject::connect(this->undoButton, &QPushButton::clicked, this, &AdminGUI::perform_undo);
    QObject::connect(this->redoButton, &QPushButton::clicked, this, &AdminGUI::perform_redo);
    QObject::connect(new QShortcut(QKeySequence("Ctrl+Z"), undoButton), &QShortcut::activated,
                     [this]() { undoButton->animateClick(); });
    QObject::connect(new QShortcut(QKeySequence("Ctrl+Y"), redoButton), &QShortcut::activated,
                     [this]() { redoButton->animateClick(); });


    //connecting the list of tutorials
    QObject::connect(this->tutorialListWidget, &QListWidget::itemSelectionChanged, [this]() {

        int selectedIndex = this->getSelectedIndex();

        if (selectedIndex < 0)
            return;

        Tutorial t = this->adminService.get_tutorial_by_position_admin_service(selectedIndex);
        this->titleLineEdit->setText(QString::fromStdString(t.get_title()));
        this->presenterLineEdit->setText(QString::fromStdString(t.get_presenter()));
        this->durationLineEditMin->setText(QString::fromStdString(std::to_string(t.get_duration().first)));
        this->durationLineEditSec->setText(QString::fromStdString(std::to_string(t.get_duration().second)));
        this->likesLineEdit->setText(QString::fromStdString(std::to_string(t.get_likes())));
        this->linkLineEdit->setText(QString::fromStdString(t.get_link()));

    });
}

int AdminGUI::getSelectedIndex() const{
    QModelIndexList selectedIndexes = this->tutorialListWidget->selectionModel()->selectedIndexes();

    if (selectedIndexes.empty()){
        this->titleLineEdit->clear();
        this->presenterLineEdit->clear();
        this->durationLineEditMin->clear();

        this->durationLineEditSec->clear();
        this->likesLineEdit->clear();
        this->linkLineEdit->clear();
        return -1;
    }

    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void AdminGUI::addTutorial() {
    std::string title, presenter, link, likes, duration_min, duration_sec;

    title = this->titleLineEdit->text().toStdString();
    presenter = this->presenterLineEdit->text().toStdString();
    link = this->linkLineEdit->text().toStdString();
    likes = this->likesLineEdit->text().toStdString();
    duration_min = this->durationLineEditMin->text().toStdString();
    duration_sec = this->durationLineEditSec->text().toStdString();

    QMessageBox mb("Duplicate!",
                   "The tutorial is already added.\n",
                   QMessageBox::NoIcon,
                   QMessageBox::Ok | QMessageBox::Default,
                   QMessageBox::NoButton,
                   QMessageBox::NoButton);

    //get rid of spaces and split the duration
    duration_min = strip(duration_min);
    duration_sec = strip(duration_sec);

    std::replace( title.begin(), title.end(), ' ', '_'); // replace all 'x' to 'y'

    try {
        int rez = adminService.admin_service_store_tutorial(title, presenter,
                                                            std::make_pair(stoi(duration_min), stoi(duration_sec)),
                                                            stoi(likes), link);
        if (rez == 1) {

            mb.exec();
        }
        else{
            this->undo_redo_manager.clear_redo();
            Tutorial t{title, presenter, std::make_pair(stoi(duration_min), stoi(duration_sec)), stoi(likes), link};
            auto *op = new UndoAction{this->adminService, &AService::admin_service_remove, t, t};
            this->undo_redo_manager.push_undo(op);
            QMessageBox::information(this, "Added!", "The tutorial was added");
            this->populateTutorialsList();
        }

    }catch(const ValidError& ve){
        QMessageBox::information(this, "Error!", QString::fromStdString(ve.get_msg()));
    }


    std::cout << "added!\n";
}

void AdminGUI::deleteTutorial() {
    std::string link;
    link = this->linkLineEdit->text().toStdString();
    QMessageBox mb("Deletion error!",
                   "There is no tutorial to delete by this link.\n",
                   QMessageBox::NoIcon,
                   QMessageBox::Ok | QMessageBox::Default,
                   QMessageBox::NoButton,
                   QMessageBox::NoButton);
    try{
        Tutorial tut = this->adminService.search(link);
        Tutorial old_tut{tut.get_title(), tut.get_presenter(), tut.get_duration(), tut.get_likes(), tut.get_link()};
        std::string t, p;
        std::pair<int, int> d = std::make_pair(0, 0);
        int l = 0;
        int rez = adminService.admin_service_remove(t, p, d, l, link);
        if(rez == 1) {
            mb.exec();
        }
        else{
            this->undo_redo_manager.clear_redo();

            auto *op = new UndoAction{this->adminService, &AService::admin_service_store_tutorial, old_tut, old_tut};
            this->undo_redo_manager.push_undo(op);

            QMessageBox::information(this, "Deleted!", "The tutorial was deleted");
            this->populateTutorialsList();
        }
    }catch(const ValidError& ve){
        QMessageBox::information(this, "Error!", QString::fromStdString(ve.get_msg()));
    }
}

void AdminGUI::updateTutorial() {
    std::string title, presenter, link, likes, duration_min, duration_sec;

    title = this->titleLineEdit->text().toStdString();
    presenter = this->presenterLineEdit->text().toStdString();
    link = this->linkLineEdit->text().toStdString();
    likes = this->likesLineEdit->text().toStdString();
    duration_min = this->durationLineEditMin->text().toStdString();
    duration_sec = this->durationLineEditSec->text().toStdString();

    QMessageBox mb("Updated!",
                   "There is no tutorial to update by this name.\n",
                   QMessageBox::NoIcon,
                   QMessageBox::Ok | QMessageBox::Default,
                   QMessageBox::NoButton,
                   QMessageBox::NoButton);

    //get rid of spaces and split the duration
    duration_min = strip(duration_min);
    duration_sec = strip(duration_sec);

    try{
        Tutorial old_t = this->adminService.search(link);
        int rez = adminService.admin_service_update(title, presenter, std::make_pair(stoi(duration_min), stoi(duration_sec)), stoi(likes), link);
        if(rez == 1) {
            mb.exec();
        }
        else{
            Tutorial new_t{title, presenter, std::make_pair(stoi(duration_min), stoi(duration_sec)), stoi(likes), link};
            this->undo_redo_manager.clear_redo();
            auto *op = new UndoAction{this->adminService, &AService::admin_service_update, old_t, new_t};
            this->undo_redo_manager.push_undo(op);

            QMessageBox::information(this, "Updated!", "The tutorial was updated");
            this->populateTutorialsList();
        }
    }catch(const ValidError& ve){
        QMessageBox::information(this, "Error!", QString::fromStdString(ve.get_msg()));
    }
}

void AdminGUI::perform_undo() {
    try
    {
        this->undo_redo_manager.undo();
        auto l = adminService.admin_service_get_all();
        for(auto & t: l)
            std::cout << t << '\n';
        this->populateTutorialsList();

        QMessageBox messageBox;
        messageBox.setText("Undone...");
        messageBox.exec();
    }
    catch (const UndoRedoException &ur)
    {
        QMessageBox err;
        err.setText(ur.what());
        err.exec();
    }
}

void AdminGUI::perform_redo() {
    try
    {
        this->undo_redo_manager.redo();
        auto l = adminService.admin_service_get_all();
        for(auto & t: l)
            std::cout << t << '\n';
        this->populateTutorialsList();

        QMessageBox messageBox;
        messageBox.setText("Redone...");
        messageBox.exec();
    }
    catch (const UndoRedoException &ur)
    {
        QMessageBox err;
        err.setText(ur.what());
        err.exec();
    }
}


