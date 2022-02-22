//
// Created by Razvan Vranceanu on 22.03.2021.
//

#ifndef A45_RAZVANVRANCEANU21_REPO_H
#define A45_RAZVANVRANCEANU21_REPO_H
#include <vector>
#include <algorithm>
#include <string>
#include <ostream>
#include <istream>
#include "../domain/tutorial.h"

class Repository{
private:
    std:: vector <Tutorial> tutorials_list;
    std::string fileName;

public:
    //constructor & destructor
    Repository(std::string nameOfTheFileUsed = "");
    ~Repository();

    //file methods
    void loadFromFile();
    void writeToFile();

    //normal functions
    int admin_repo_store(const Tutorial& tutorial);
    int admin_repo_remove(const std::string &tutorial_link);
    int admin_repo_update(const std::string &tutorial_to_update_link,
                                            const std::string& new_tutorial_title,
                                            const std::string& new_tutorial_presenter,
                                            const std::pair<int, int>& new_duration,
                                            int new_number_of_likes);
    int size_elems() const;
    Tutorial get_tutorial_by_position(int position) const;
    std:: vector <Tutorial> get_all_repo();
};

#endif //A45_RAZVANVRANCEANU21_REPO_H
