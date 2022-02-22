//
// Created by Razvan Vranceanu on 07.05.2021.
//

#ifndef A45_RAZVANVRANCEANU21_ADMINGUI_H
#define A45_RAZVANVRANCEANU21_ADMINGUI_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>

#include "../Service/a_service.h"
#include "../Service/user_service.h"
#include "../undo_redo/undo_redo.h"


class AdminGUI: public QWidget{
private:
    AService& adminService;
    undo_redo& undo_redo_manager;

    QListWidget* tutorialListWidget;

    ///buttons
    QPushButton* adminAddButton;
    QPushButton* adminDeleteButton;
    QPushButton* adminUpdateButton;
    QPushButton* undoButton;
    QPushButton* redoButton;


    ///Line edits
    QLineEdit* titleLineEdit;
    QLineEdit* presenterLineEdit;
    QLineEdit* durationLineEditMin;
    QLineEdit* durationLineEditSec;
    QLineEdit* likesLineEdit;
    QLineEdit* linkLineEdit;

public:
    AdminGUI(AService& adminService, undo_redo&);
    void mainWindow();
    void populateTutorialsList();
    void connectSignalsAndSlots();
    int getSelectedIndex() const;
    ~AdminGUI() override = default;
    void addTutorial();
    void deleteTutorial();
    void updateTutorial();

    void perform_undo();
    void perform_redo();


};


#endif //A45_RAZVANVRANCEANU21_ADMINGUI_H
