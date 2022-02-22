//
// Created by Razvan Vranceanu on 22.03.2021.
//

#ifndef A45_RAZVANVRANCEANU21_TUTORIAL_H
#define A45_RAZVANVRANCEANU21_TUTORIAL_H

#include <string>
#include <iostream>

class Tutorial{
private:
    std::string title;
    std::string presenter;
    std::pair <int, int> duration;
    int likes;
    std::string link;

public:
    Tutorial(std::string title,
             std::string presenter,
             std::pair <int, int>  duration,
             int likes,
             std::string link);
    Tutorial(const Tutorial& t);
    Tutorial();

//    Tutorial(const Tutorial& tutorial);

    void set_title(const std::string& tutorial_title);
    void set_presenter(const std::string& presenter);
    void set_duration(const std::pair<int, int>& duration);
    void set_likes(int);
    void set_link(const std::string& link);

    // ------ getters
    const std::string& get_title() const;
    const std::string& get_presenter() const;
    const std::pair <int, int>& get_duration() const;
    int get_likes() const;
    const std::string& get_link() const;


    // overloading operators
    friend std::ostream& operator<<(std::ostream&, const Tutorial&);
    friend std::istream& operator>>(std::istream&, Tutorial&);
};
#endif //A45_RAZVANVRANCEANU21_TUTORIAL_H
