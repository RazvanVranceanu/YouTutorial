//
// Created by Razvan Vranceanu on 10.05.2021.
//

#ifndef A45_RAZVANVRANCEANU21_USERGUI_H
#define A45_RAZVANVRANCEANU21_USERGUI_H


#include <QWidget>
#include <fstream>
#include "../Service/user_service.h"
#include "../Service/a_service.h"

class UserGUI : public QWidget{
protected:
    Uservice& userService;
    AService& adminService;
private:

    QListWidget* watchListWidget;

    QPushButton* watchButton;
//    QPushButton* nextButton;
    QPushButton* deleteButton;
    QPushButton* seeWatchButton;

    QLineEdit* presenterLineEdit;
    QLineEdit* linkLineEdit;
    QLineEdit* filenameLineEdit;


public:
    explicit UserGUI(Uservice& userService, AService& adminService);
    void mainWindow();
    void connectSignalsAndSlots();
    void start_watching();
    void start_iterate_presenter(const std::string &presenter);
    void start_iterate_all(const std::string &presenter);
    void delete_tutorial();
    int getSelectedIndex() const;
    void get_to_file();
    ~UserGUI() override = default;

    void see_watchlist_csv();
    void see_watchlist_html();
};



#endif //A45_RAZVANVRANCEANU21_USERGUI_H
