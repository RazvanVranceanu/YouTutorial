//
// Created by Razvan Vranceanu on 03.06.2021.
//

#ifndef A45_RAZVANVRANCEANU21_ACTION_H
#define A45_RAZVANVRANCEANU21_ACTION_H

#include "../Service/a_service.h"
#include <string>

typedef int (AService::*HandlerTutorials)(const std::string &, const std::string &, const std::pair<int, int>&, int ,
                                           const std::string &);

class action {
public:
    virtual void execute() = 0;
};

class SimpleAction: public action{
protected:
    Tutorial tutorial1;
    Tutorial tutorial2;
public:
    SimpleAction(const Tutorial &, const Tutorial &);
};

class RedoAction;

class UndoAction : public SimpleAction{
private:
    AService &asrv;
    HandlerTutorials handler;
public:
    explicit UndoAction(AService& , HandlerTutorials, const Tutorial&, const Tutorial&);
    void execute() override;
    RedoAction *get_redo_act();
};

class RedoAction : public SimpleAction{
private:
    AService &asrv;
    HandlerTutorials handler;
    HandlerTutorials get_reverse_handler();
public:
    explicit RedoAction(AService &, HandlerTutorials, const Tutorial&, const Tutorial&);
    void execute() override;
    UndoAction *get_undo_act();
};


#endif //A45_RAZVANVRANCEANU21_ACTION_H
