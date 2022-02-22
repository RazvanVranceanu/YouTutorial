//
// Created by Razvan Vranceanu on 19.04.2021.
//


#include "ValidError.h"

ValidError::ValidError(const std::string &msg): _msg{msg}, std::exception() {

}

const std::string &ValidError::get_msg() const {
    return this->_msg;
}
