//
// Created by Razvan Vranceanu on 22.03.2021.
//

#include "tutorial.h"

Tutorial::Tutorial(std::string title,
                   std::string presenter,
                   std::pair<int, int> duration = std::make_pair(0, 0),
                   int likes = 0,
                   std::string link = ""):title(std::move(title)),
                                      presenter(std::move(presenter)),
                                      duration(std::move(duration)),
                                      likes(likes),
                                      link(std::move(link)) {

}

Tutorial::Tutorial(const Tutorial &t): title(t.title),
                                       presenter(t.presenter),
                                       duration(t.duration),
                                       likes(t.likes),
                                       link(t.link){
}

Tutorial::Tutorial():title{""}, presenter{""}, duration{std::make_pair(0, 0)}, likes{0}, link{""} {}

//Tutorial::Tutorial(const Tutorial& tutorial):title{tutorial.title},
//                                             presenter{tutorial.presenter},
//                                             duration{tutorial.duration},
//                                             likes{tutorial.likes},
//                                             link{tutorial.link}
//{}

void Tutorial::set_title(const std::string &tutorial_title) {
    this->title = tutorial_title;
}

void Tutorial::set_presenter(const std::string &tutorial_presenter) {
    this->presenter = tutorial_presenter;
}

void Tutorial::set_duration(const std::pair<int, int> &tutorial_duration) {
    this->duration = tutorial_duration;
}

void Tutorial::set_likes(int tutorial_likes) {
    this->likes = tutorial_likes;
}

void Tutorial::set_link(const std::string &tutorial_link) {
    this->link = tutorial_link;
}


const std::string &Tutorial::get_title() const {
    return this->title;
}

const std::string &Tutorial::get_presenter() const {
    return this->presenter;
}

const std::pair<int, int> &Tutorial::get_duration() const {
    return this->duration;
}

int Tutorial::get_likes() const {
    return this->likes;
}

const std::string &Tutorial::get_link() const {
    return this->link;
}

std::ostream &operator<<(std::ostream& os, const Tutorial& t) {
    os << t.title << " " << t.presenter << " " << t.duration.first << " " << t.duration.second << " " << t.likes << " " <<t.link;
    return os;
}

std::istream &operator>>(std::istream& is, Tutorial& t) {
    is >> t.title >> t.presenter >> t.duration.first >> t.duration.second >> t.likes >> t.link;
    return is;
}




