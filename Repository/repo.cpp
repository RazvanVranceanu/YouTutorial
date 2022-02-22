//
// Created by Razvan Vranceanu on 22.03.2021.
//

#include <fstream>
#include <iostream>
#include <utility>
#include "repo.h"

Repository::Repository(std::string nameOfTheFileUsed){
    this->fileName = std::move(nameOfTheFileUsed);
    loadFromFile();
}

Repository::~Repository() = default;

/// file operations

void Repository::loadFromFile() {
    if (this->fileName.empty())
        return ;

    Tutorial t;

    std::ifstream fin(this->fileName);

    while(fin >> t){
//        if (std::find(tutorialList.begin(), tutorialList.end(), t) == tutorialList.end())  // todo: ?
        tutorials_list.push_back(t);
    }
    fin.close();
}

void Repository::writeToFile() {
    if(this->fileName.empty())
        return;
    std::ofstream fout(this->fileName);
    for(const Tutorial& t : tutorials_list)
        fout << t << '\n';
    fout.close();
}

int Repository::size_elems() const
{
    return tutorials_list.size();
}


int Repository::admin_repo_store(const Tutorial& tutorial)
{
    for (auto & it : tutorials_list)
    {
        if (it.get_link() == tutorial.get_link())
            return 1;
    }
    tutorials_list.push_back(tutorial);
    writeToFile();
    return 0;
}

int Repository::admin_repo_remove(const std::string &tutorial_link)
{
    for (auto it = tutorials_list.begin(); it != tutorials_list.end(); it++)
    {
        if (it->get_link() == tutorial_link)
        {
            tutorials_list.erase(it);
            writeToFile();
            return 0;
        }
    }
    return 1;
}

int Repository::admin_repo_update(const std::string &tutorial_to_update_link,
                                                    const std::string &new_tutorial_title,
                                                    const std::string &new_tutorial_presenter,
                                                    const std::pair<int, int> &new_duration,
                                                    int new_number_of_likes)
{
    for (auto & it : tutorials_list)
    {
        if (it.get_link() == tutorial_to_update_link)
        {
            it.set_title(new_tutorial_title);
            it.set_presenter(new_tutorial_presenter);
            it.set_duration(new_duration);
            it.set_likes(new_number_of_likes);
            writeToFile();
            return 0;
        }
    }

    return 1;

}

Tutorial Repository::get_tutorial_by_position(int position) const
{
    if (position < 0 || position >= tutorials_list.size())
        throw std::runtime_error("Invalid position");
    return tutorials_list[position];
}

std::vector<Tutorial> Repository::get_all_repo(){
    return tutorials_list;
}