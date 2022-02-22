//
// Created by Razvan Vranceanu on 03.06.2021.
//

#include "action.h"
#define perform_op(service, handler)  ((service).*(handler))

SimpleAction::SimpleAction(const Tutorial &t1, const Tutorial &t2) : tutorial1{t1}, tutorial2{t2} {}

UndoAction::UndoAction(AService &s, HandlerTutorials h, const Tutorial &t1, const Tutorial &t2)
:asrv{s}, handler{h}, SimpleAction{t1, t2}{
}

void UndoAction::execute() {
    perform_op(this->asrv, this->handler)(this->tutorial1.get_title(),
                                                         this->tutorial1.get_presenter(),
                                                         this->tutorial1.get_duration(),
                                                         this->tutorial1.get_likes(),
                                                         this->tutorial1.get_link());


}

RedoAction *UndoAction::get_redo_act() {
    return new RedoAction{this->asrv, this->handler, this->tutorial2, this->tutorial1};
}

HandlerTutorials RedoAction::get_reverse_handler() {
    if (this->handler == &AService::admin_service_store_tutorial)
        return HandlerTutorials(&AService::admin_service_remove);
    else if (this->handler == &AService::admin_service_remove)
        return &AService::admin_service_store_tutorial;
    else
        return &AService::admin_service_update;
}

RedoAction::RedoAction(AService &s, HandlerTutorials h, const Tutorial &t1, const Tutorial &t2):
asrv{s}, handler{h}, SimpleAction{t1, t2}
{}

void RedoAction::execute() {
    perform_op(this->asrv, this->get_reverse_handler())(this->tutorial1.get_title(), this->tutorial1.get_presenter(),
                                                           this->tutorial1.get_duration(), this->tutorial1.get_likes(),
                                                           this->tutorial1.get_link());

}

UndoAction *RedoAction::get_undo_act() {
    return new UndoAction{this->asrv, this->handler, this->tutorial2, this->tutorial2};
}




