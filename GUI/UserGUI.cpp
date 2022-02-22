//
// Created by Razvan Vranceanu on 10.05.2021.
//

#include <QVBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include "UserGUI.h"

UserGUI::UserGUI(Uservice& userService, AService& adminService): userService{userService}, adminService{adminService}{
    this->mainWindow();
    this->connectSignalsAndSlots();
}

void UserGUI::mainWindow() {
    this->setWindowTitle("User");
    this->resize(510, 590);
    auto* MainLayout = new QVBoxLayout{this};

    ///display section
    this->watchListWidget = new QListWidget{};
    MainLayout->addWidget(this->watchListWidget);

    ///start watching section
    this->presenterLineEdit = new QLineEdit{};
    presenterLineEdit->setPlaceholderText("Enter presenter or type \"all\"");
    this->watchButton = new QPushButton{"Start watching"};
    auto* entryAndButtonLayout = new QHBoxLayout{this}; //layout
    entryAndButtonLayout->addWidget(presenterLineEdit);
    entryAndButtonLayout->addWidget(watchButton);
    MainLayout->addLayout(entryAndButtonLayout);
//    this->nextButton = new QPushButton{"Next"};
//    MainLayout->addWidget(nextButton);

    ///Delete tutorial section
    auto* deleteLayout = new QHBoxLayout{this};
//    this->linkLineEdit = new QLineEdit{};
//    linkLineEdit->setPlaceholderText("Enter link");
    this->deleteButton = new QPushButton{"Delete tutorial"};
//    deleteLayout->addWidget(linkLineEdit);
    deleteLayout->addWidget(deleteButton);
    MainLayout->addLayout(deleteLayout);

    ///See watchlist section
    auto* seeWatchlistLayout = new QHBoxLayout{this};
    this->filenameLineEdit = new QLineEdit{};
    filenameLineEdit->setPlaceholderText("Enter file extension");
    this->seeWatchButton = new QPushButton{"See watchlist"};
    seeWatchlistLayout->addWidget(filenameLineEdit);
    seeWatchlistLayout->addWidget(seeWatchButton);
    MainLayout->addLayout(seeWatchlistLayout);

}

void UserGUI::connectSignalsAndSlots() {
    QObject::connect(this->watchButton, &QPushButton::clicked, this, &UserGUI::start_watching);
    QObject::connect(this->deleteButton, &QPushButton::clicked, this, &UserGUI::delete_tutorial);
    QObject::connect(this->seeWatchButton, &QPushButton::clicked, this, &UserGUI::get_to_file);
}

void UserGUI::start_watching() {
    std::string presenter;
    presenter = this->presenterLineEdit->text().toStdString();
    if(presenter == "all")
        start_iterate_all(presenter);
    else
        start_iterate_presenter(presenter);
}

void UserGUI::start_iterate_all(const std::string &presenter) {

    QMessageBox msgBox;
    msgBox.setText(tr("like and add to watchlist?"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("Yes"), QMessageBox::YesRole);
    msgBox.addButton(tr("No"), QMessageBox::NoRole);

    std::vector<Tutorial>listOfTutorials = adminService.admin_service_get_all();
    ///populate
//    this->watchListWidget->clear();

    ///iterate through the tutorials
    for (auto& tutorial : listOfTutorials){

        const std::string open = "open ";
        const std::string url = tutorial.get_link();
        const std::string r = open + url;
        system(r.c_str());

        msgBox.exec();
        if (msgBox.clickedButton()==pButtonYes){
            int rez = userService.like_dislike("y", tutorial);
            if (rez == 1)
                QMessageBox::information(this, "Already added!", "Tutorial already in the watchlist!");
            else
                this->watchListWidget->addItem(QString::fromStdString("title: " + tutorial.get_title() + ",     presenter: " + tutorial.get_presenter()));
        }
    }
}

void UserGUI::start_iterate_presenter(const std::string &presenter) {

    QMessageBox msgBox;
    msgBox.setText(tr("like and add to watchlist?"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("Yes"), QMessageBox::YesRole);
    msgBox.addButton(tr("No"), QMessageBox::NoRole);

    std::vector<Tutorial>listOfTutorials = adminService.admin_service_get_all();
    ///populate
//    this->watchListWidget->clear();

    ///iterate through the tutorials
    for (auto& tutorial : listOfTutorials)
        if(tutorial.get_presenter() == presenter) {
            const std::string open = "open ";
            const std::string url = tutorial.get_link();
            const std::string r = open + url;
            system(r.c_str());

            msgBox.exec();
            if (msgBox.clickedButton() == pButtonYes) {
                int rez = userService.like_dislike("y", tutorial);
                if (rez == 1)
                    QMessageBox::information(this, "Already added!", "Tutorial already in the watchlist!");
                else
                    this->watchListWidget->addItem(QString::fromStdString(
                            "title: " + tutorial.get_title() + ",     presenter: " + tutorial.get_presenter()));
            }
        }
}

int UserGUI::getSelectedIndex() const{
    QModelIndexList selectedIndexes = this->watchListWidget->selectionModel()->selectedIndexes();

    if (selectedIndexes.empty()){
        this->linkLineEdit->clear();
        return -1;
    }

    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void UserGUI::delete_tutorial() {
    int index = this->getSelectedIndex();
    userService.delete_from_watchlist(index);
    this->watchListWidget->clear();
    std::vector<Tutorial> tuts = userService.get_watchlist();
    for(auto& t : tuts)
        this->watchListWidget->addItem(QString::fromStdString("title: " + t.get_title() + ",     presenter: " + t.get_presenter()));
}

void UserGUI::get_to_file() {
    std::string name = this->filenameLineEdit->text().toStdString();

    if(name == "html")
    {
        see_watchlist_html();
        system("open tutorial.html");
    }
    else if (name == "csv")
    {
        see_watchlist_csv();
        system("open tutorial.csv");
    }
    else
        QMessageBox::information((QWidget *) this, "Error!", "Wrong extension");
}

void UserGUI::see_watchlist_html() {
    std::ofstream fout("tutorial.html");
    fout << "<!DOCTYPE html>\n";
    fout << "<html>\n<head>\n";
    fout << "<title>\nTutorial\n</title>\n";
    fout << "</head>\n<body>\n";
    fout << "<table border=\"1\">\n";
    std::vector<Tutorial>listOfTutorials = userService.get_watchlist();
    for(auto& tutorial: listOfTutorials) {
    fout << "<tr>\n";
    fout << "<td>" << tutorial.get_title() << "</td>";
    fout << "<td>" << tutorial.get_presenter() << "</td>";
    fout << "<td>" << tutorial.get_likes() << "</td>";
    fout << "<td>" << tutorial.get_duration().first << "</td>";
    fout << "<td>" << tutorial.get_duration().second << "</td>";
    }
    fout << "</table>\n</body>\n</html>";
};

void UserGUI::see_watchlist_csv()  {
    std::ofstream fout("tutorial.csv");
    std::vector<Tutorial>listOfTutorials = userService.get_watchlist();
    for(auto& tutorial: listOfTutorials)
    fout << tutorial.get_title() << "," << tutorial.get_presenter() << "," << tutorial.get_likes() << "," <<
    tutorial.get_duration().first << "," << tutorial.get_duration().second << '\n';
};
