//
// Created by Razvan Vranceanu on 03.06.2021.
//

#ifndef A45_RAZVANVRANCEANU21_UNDO_REDO_H
#define A45_RAZVANVRANCEANU21_UNDO_REDO_H
#include <stack>
#include "action.h"

class undo_redo {
private:
    std::stack<action* > undo_stack;
    std::stack<action* > redo_stack;
public:
    void push_undo(action* act);
    void clear_redo();
    void undo();
    void redo();
};


#endif //A45_RAZVANVRANCEANU21_UNDO_REDO_H
