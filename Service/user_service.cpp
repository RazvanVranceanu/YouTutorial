//
// Created by Razvan Vranceanu on 27.03.2021.
//

#include "user_service.h"
#include <vector>
#include <iostream>

Uservice::Uservice(Repository &repository): repository{ repository }{
    this->index = 0;
}

int Uservice::like_dislike(const std::string &option, Tutorial& tutorial) {
    if(option == "y"){
        std:: vector <Tutorial> tutorials = get_watchlist();
        bool found = false;
        for(auto& it : tutorials)
            if(tutorial.get_link() == it.get_link()) {
                found = true;
                break;
            }
        if(!found) {
            watchlist.push_back(tutorial);
            this->index++;
            return 0;
        }
        return 1;
    }
    return 0;
}

std:: vector <Tutorial> Uservice::get_watchlist() const {
    return watchlist;
}

int Uservice::delete_from_watchlist(int position) {
    watchlist.erase(watchlist.begin() + position);
    return 0;
}


Uservice::~Uservice() = default;

