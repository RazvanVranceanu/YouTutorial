//
// Created by Razvan Vranceanu on 19.04.2021.
//

#include "TutorialValidator.h"
#include "../errors/ValidError.h"

void TutorialValidator::validate_tutorial(const Tutorial &t) {
    std::string errors;
    if (t.get_title().empty())
        errors += "invalid title!\n";
    if (t.get_presenter().empty())
        errors += "invalid presenter!\n";
    if (t.get_duration().first < 0 or t.get_duration().second < 0)
        errors += "invalid duration!\n";
    if (t.get_likes() < 0)
        errors += "invalid likes!\n";
    if (t.get_link().empty())
        errors += "invalid link!\n";
    if(!errors.empty())
        throw ValidError(errors);
}
