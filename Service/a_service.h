//
// Created by Razvan Vranceanu on 23.03.2021.
//

#ifndef A45_RAZVANVRANCEANU21_A_SERVICE_H
#define A45_RAZVANVRANCEANU21_A_SERVICE_H
#include "../Repository/repo.h"

class AService{

private:
    Repository& repo;

public:
    AService(Repository& repo);
    ~AService();

    int admin_service_store_tutorial(const std::string &title, const std::string &presenter,
                                     const std::pair<int, int> &duration, int number_of_likes,
                                     const std::string &link);
    int admin_service_remove(const std::string &title,
                             const std::string &presenter,
                             const std::pair<int, int> &duration, int number_of_likes,
                             const std::string &link);
    Tutorial get_tutorial_by_position_admin_service(int position);

    int admin_service_update(const std::string &new_tutorial_title,
    const std::string &new_tutorial_presenter,
    const std::pair<int, int> &new_duration, int new_number_of_likes,
    const std::string &tutorial_to_update_link);

    std:: vector <Tutorial> admin_service_get_all();
    const Tutorial &operator[](int i) const;
    Tutorial search(std::string );
};

#endif //A45_RAZVANVRANCEANU21_A_SERVICE_H
