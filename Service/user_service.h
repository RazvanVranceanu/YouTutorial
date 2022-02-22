//
// Created by Razvan Vranceanu on 27.03.2021.
//

#ifndef A45_RAZVANVRANCEANU21_USER_SERVICE_H
#define A45_RAZVANVRANCEANU21_USER_SERVICE_H

#include "../Repository/repo.h"

class Uservice{
    private:
        Repository& repository;
        std::vector<Tutorial> watchlist;
        int index;
    public:
        Uservice(Repository& repository);
        ~Uservice();
        int like_dislike(const std::string&, Tutorial& tutorial);
        std:: vector <Tutorial> get_watchlist() const;
        int delete_from_watchlist(int position);
};
#endif //A45_RAZVANVRANCEANU21_USER_SERVICE_H
