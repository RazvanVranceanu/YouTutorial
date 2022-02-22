//
// Created by Razvan Vranceanu on 03.06.2021.
//

#include "undo_redo.h"
#include "../errors/ValidError.h"

void undo_redo::push_undo(action *act) {
    this->undo_stack.push(act);
}

void undo_redo::clear_redo() {
    while (!this->redo_stack.empty())
    {
        auto *op = (RedoAction *) this->redo_stack.top();
        this->redo_stack.pop();
        delete op;
    }
}

void undo_redo::undo() {
    if (this->undo_stack.empty())
        throw UndoRedoException("No more undos!\n");
    auto *op = (UndoAction *) this->undo_stack.top();
    this->undo_stack.pop();
    op->execute();
    RedoAction *redo_op = op->get_redo_act();
    this->redo_stack.push(redo_op);
    delete op;
}

void undo_redo::redo() {
    if (this->redo_stack.empty())
        throw UndoRedoException("No more redos!\n");
    auto *op = (RedoAction *) this->redo_stack.top();
    this->redo_stack.pop();
    op->execute();
    UndoAction *undo_op = op->get_undo_act();
    this->undo_stack.push(undo_op);
    delete op;
}
