//
// Created by Razvan Vranceanu on 10.05.2021.
//

#include <QVBoxLayout>
#include <QPushButton>
#include "QtMenu.h"
#include "AdminGUI.h"
#include "UserGUI.h"

QtMenu::QtMenu(AService &adminService, Uservice &userService, undo_redo& urm): adminService{adminService}, userService{userService},
undo_redo_manager{urm}{
    this->setWindowTitle("Choose mode");
    this->resize(200, 100);

    auto vLayout = new QVBoxLayout();
    this->setLayout(vLayout);

    auto adminButton = new QPushButton("Admin");
    QObject::connect(adminButton, &QPushButton::clicked, this, &QtMenu::showAdmin);
    vLayout->addWidget(adminButton);

    auto userButton = new QPushButton("User");
    QObject::connect(userButton, &QPushButton::clicked, this, &QtMenu::showUser);
    vLayout->addWidget(userButton);
}

void QtMenu::showAdmin() {
    auto admin = new AdminGUI(this->adminService, this->undo_redo_manager);
    admin->show();
}

void QtMenu::showUser() {
    auto user = new UserGUI(this->userService, this->adminService);
    user->show();
}
