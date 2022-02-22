//
// Created by Razvan Vranceanu on 23.03.2021.
//

#include "a_service.h"
#include "../validator/TutorialValidator.h"

AService::AService(Repository &repo) : repo{repo} {}

AService::~AService() = default;


int AService::admin_service_store_tutorial(const std::string &title,
                                           const std::string &presenter,
                                           const std::pair<int, int> &duration, int number_of_likes,
                                           const std::string &link) {
    Tutorial tutorial = {title, presenter, duration, number_of_likes, link};
    TutorialValidator::validate_tutorial(tutorial);
    return repo.admin_repo_store(tutorial);
}


int AService::admin_service_remove(const std::string &title,
                                   const std::string &presenter,
                                   const std::pair<int, int> &duration, int number_of_likes,
                                   const std::string &link) {
    Tutorial tutorial = {".", ".", std::make_pair(0, 0), 0, link};
    TutorialValidator::validate_tutorial(tutorial);
    return repo.admin_repo_remove(link);
}


Tutorial AService::get_tutorial_by_position_admin_service(int position) {
    return repo.get_tutorial_by_position(position);
}


int AService::admin_service_update(const std::string &new_tutorial_title,
                                   const std::string &new_tutorial_presenter,
                                   const std::pair<int, int> &new_duration, int new_number_of_likes,
                                   const std::string &tutorial_to_update_link) {
    Tutorial t(new_tutorial_title, new_tutorial_presenter, new_duration, new_number_of_likes, tutorial_to_update_link);
    TutorialValidator::validate_tutorial(t);
    return repo.admin_repo_update(tutorial_to_update_link, new_tutorial_title,
                                  new_tutorial_presenter, new_duration, new_number_of_likes);
}


std::vector<Tutorial> AService::admin_service_get_all() {
    return repo.get_all_repo();
}

const Tutorial &AService::operator[](int i) const
{
    return this->repo.get_all_repo()[i];
}

Tutorial AService::search(std::string link) {
    auto l = this->repo.get_all_repo();
    int i =0;
    for(auto &t : l) {
        if (t.get_link() == link)
            break;
        i++;
    }
    return this->repo.get_all_repo()[i];
}


