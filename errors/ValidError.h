//
// Created by Razvan Vranceanu on 19.04.2021.
//

#ifndef A45_RAZVANVRANCEANU21_VALIDERROR_H
#define A45_RAZVANVRANCEANU21_VALIDERROR_H

#include <exception>
#include <string>

class ValidError:public std::exception{
private:
    std::string _msg;
public:
    ValidError(const std::string& msg);
    const std::string& get_msg() const;

};

class UndoRedoException : public std::runtime_error
{
public:
    UndoRedoException(const char *err) : runtime_error(err)
    {}
};
#endif //A45_RAZVANVRANCEANU21_VALIDERROR_H
