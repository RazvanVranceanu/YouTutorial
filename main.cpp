//
// Created by Razvan Vranceanu on 22.03.2021.
//

#include "tests/test.h"
#include "Ui/ui.h"
#include "GUI/AdminGUI.h"
#include "GUI/QtMenu.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>


int main(int argc, char *argv[]){
//    Tests::run_all_tests();

    QApplication a{ argc, argv };
//    a.setFont(QFont("San Francisco"));

    Repository repo{"datain.txt"};
    AService asrv(repo);
    Uservice usrv(repo);

//    Ui ui(asrv, usrv);
//    ui.run();

//    AdminGUI gui(asrv, usrv);
//    gui.resize(510, 590);
//    gui.show();

    undo_redo urm{};
    QtMenu menu(asrv, usrv, urm);
    menu.show();

    return a.exec();

//    return 0;
}
