//
// Created by Razvan Vranceanu on 10.05.2021.
//

#ifndef A45_RAZVANVRANCEANU21_QTMENU_H
#define A45_RAZVANVRANCEANU21_QTMENU_H


#include <QWidget>
#include "../Service/user_service.h"
#include "../Service/a_service.h"
#include "../undo_redo/undo_redo.h"

class QtMenu : public QWidget {
private:

    AService& adminService;
    Uservice& userService;
    undo_redo& undo_redo_manager;
public:
    explicit QtMenu(AService &adminService, Uservice &userService, undo_redo &urm);

    void showAdmin();

    void showUser();
};


#endif //A45_RAZVANVRANCEANU21_QTMENU_H
