////
//// Created by Razvan Vranceanu on 23.03.2021.
////
//
//#include "ui.h"
//#include "../errors/ValidError.h"
//#include <iostream>
//#include <string>
//
//
//Ui::Ui(AService& adminService, Uservice& userService):adminService{adminService},  userService{userService}{}
//
//Ui::~Ui() = default;
//
/////run methods
//
//void Ui::run(){
////    adminService.admin_service_store_tutorial("C++ tutorial 1", "Eu", std::make_pair(2, 12), 43, "https://www.youtube.com/watch?v=I-hZkUa9mIs&t=2s");
////    adminService.admin_service_store_tutorial("C++ tutorial 2", "Eu", std::make_pair(32, 42), 54, "https://www.youtube.com/watch?v=XyNlqQId-nk");
////    adminService.admin_service_store_tutorial("C++ tutorial 3", "Ea", std::make_pair(52, 72), 32, "https://www.youtube.com/watch?v=tpiyEe_CqB4");
////    adminService.admin_service_store_tutorial("C++ tutorial 4", "Eu", std::make_pair(22, 1), 44, "https://www.youtube.com/watch?v=QtC3Bo9B0yI");
////    adminService.admin_service_store_tutorial("C++ tutorial 5", "Ea", std::make_pair(22, 1), 44, "https://www.youtube.com/watch?v=YEU_FIly708");
//
//    ///chose the mode of accessing
//    std::cout << "PLease choose a mode in which you wish to access the app!\n";
//    std::cout << "1. Admin mode\n";
//    std::cout << "2. User mode\n";
//    std::cout << ">>>";
//    char mode[256];
//    std::cin >> mode;
//
//    /// admin mode
//    if(strcmp(mode, "1") == 0)
//        run_admin_mode();
//
//    /// user mode
//    else if(strcmp(mode, "2") == 0)
//        run_user_mode();
//
//    else
//        std::cout << "\nInvalid input!\n";
//}
//
//void Ui::run_admin_mode() {
//    while (true) {
//        print_admin_menu();
//        int option;
//        std::cout << ">>> ";
//        std::cin >> option;
//        if (option == 0) {
//            std::cout << "See you!\n";
//            break;
//        } else if (option == 1) {
//            try{
//                ui_admin_add();
//            }catch(const ValidError& ve){
//                std::cout<<ve.get_msg();
//            }
//
//
//        } else if (option == 2) {
//            try{
//                ui_admin_update();
//            }catch(const ValidError& ve){
//                std::cout<<ve.get_msg();
//            }
//
//        } else if (option == 3) {
//            try{
//                ui_admin_delete();
//            }catch(const ValidError& ve){
//                std::cout<<ve.get_msg();
//            }
//
//        } else if (option == 4) {
//            ui_admin_print_elems();
//        } else {
//            std::cout << "Wrong command!\n";
//        }
//    }
//}
//
//void Ui::run_user_mode() {
//    int mode;
//    std::cout << "chose mode HTML(0) or CSV(1)\n";
//    std::cin >> mode;
//    while(true) {
//        print_user_menu();
//        int option;
//        std::cout << ">>> ";
//        std::cin >> option;
//        if (option == 0) {
//            std::cout << "See you!\n";
//            break;
//        } else if (option == 1) {
//            Ui::ui_user_start_watching();
//        }
//        else if (option == 2) {
//            int pos;
//            std::cout << "Enter the position (in the watchlist) of the tutorial you want to delete: ";
//            std::cin >> pos;
////
//            ui_user_rate_tutorial(pos);
//
//        }
//        else if (option == 3) {
//            if(mode == 0){
//                PrintHTML* t = new PrintHTML(adminService, userService);
//                t->ui_user_see_watchlist();
//                system("open tutorial.html");
//                delete t;
//            }
//            else if(mode == 1){
//                PrintCSV* t = new PrintCSV(adminService, userService);
//                t->ui_user_see_watchlist();
//                system("open tutorial.csv");
//                delete t;
//            }
//        }
//    }
//
//}
//
/////functions for user mode
//void Ui::print_user_menu(){
//    std::cout << "----------------\n";
//    std::cout << "0. Exit the app.\n";
//    std::cout << "1. Start watching! Enter a presenter  / leave it empty to see all tutorials in the database\n";
//    std::cout << "2. Delete a tutorial from the watchlist.\n";
//    std::cout << "3. Show the watchlist.\n";
//    std::cout << "----------------\n";
//}
//
//void Ui::ui_user_start_iterate(const std::string &presenter){
//    if(presenter == "all"){
//        std::vector<Tutorial>listOfTutorials = adminService.admin_service_get_all();
//        for (auto& tutorial : listOfTutorials){
//            std::cout << tutorial.get_title() << " " << tutorial.get_presenter() << " " << tutorial.get_likes() << tutorial.get_duration().first << " " << tutorial.get_duration().second <<'\n';
//            const std::string open = "open ";
//            const std::string url = tutorial.get_link();
//            const std::string r = open + url;
//
////            system(r.c_str());
//            std::cout<<"like and add to watchlist? (y/n)";
//            std::string option;
//            std::cout <<">>>";
//            std::cin >> option;
//            if(option != "y" && option != "n")
//                std::cout << "Wrong command!\n";
//            else {
//                int rez = userService.like_dislike(option, tutorial);
//                if (rez == 1)
//                    std::cout << "Tutorial already in the watchlist!\n";
//            }
////            system("open tutorial.get_link()");
//        }
//    }
//    else{
//        std::vector<Tutorial>listOfTutorials = adminService.admin_service_get_all();
//        for (auto& tutorial : listOfTutorials)
//            if(tutorial.get_presenter() == presenter){
//                std::cout << tutorial.get_title() << " " << tutorial.get_presenter() << " " << tutorial.get_likes() << tutorial.get_duration().first << " " << tutorial.get_duration().second <<'\n';
//                std::cout<<"like and add to watchlist? (y/n)";
//                std::string option;
//                std::cout <<">>>";
//                std::cin >> option;
//                if(option != "y" && option != "n")
//                    std::cout << "Wrong command!\n";
//                else {
//                    int rez = userService.like_dislike(option, tutorial);
//                    if (rez == 1)
//                        std::cout << "Tutorial already in the watchlist!\n";
//                }
//            }
//    }
//
//}
//
// void Ui::ui_user_see_watchlist() {
//    std::vector<Tutorial>listOfTutorials = userService.get_watchlist();
//    int index = 0;
//    for(auto& tutorial: listOfTutorials) {
//        index++;
//        std::cout << index << ". " << tutorial.get_title() << " " << tutorial.get_presenter() << " " << tutorial.get_likes()
//                  << tutorial.get_duration().first << " " << tutorial.get_duration().second << '\n';
//
//    }
//}
//
//void Ui::ui_user_start_watching(){
//    std::string presenter;
//
//    std::cout << "Enter a presenter name / write all!\n";
//    std::cout << ">>>";
//    std::cin >> presenter;
//
//    Ui::ui_user_start_iterate(presenter);
//}
//
//void Ui::ui_user_delete_tutorial(int position) {
//    userService.delete_from_watchlist(position);
//}
//
//void Ui::ui_user_rate_tutorial(int position) {
//    position--;
//    std::string answer;
//    std::cout << "Did you like the tutorial? (y)\n";
//    std::cout << ">>>";
//    std::cin >> answer;
//    if(answer == "y"){
//    // todo: user_service -> update like ratio
//        std::vector<Tutorial>listOfTutorials = userService.get_watchlist();
//        Tutorial t = listOfTutorials[position];
//        adminService.admin_service_update(t.get_link(), t.get_title(), t.get_presenter(), t.get_duration(), t.get_likes() + 1);
//    }
//    ui_user_delete_tutorial(position);
//}
//
//
///// functions for admin mode
//void Ui::ui_admin_add() {
//    std::string title, presenter, link, input;
//    int time1, time2, likes;
//
//    std::cout<<"Enter title: ";
//    std::cin >> input;
//    title = input.substr(0, input.size() );
//
//    std::cout<<"Enter presenter: ";
//    std::cin >> input;
//    presenter = input.substr(0, input.size());
//
//    std::cout<<"Enter link: ";
//    std::cin >> input;
//    link = input.substr(0, input.size());
//
//    std::cout<<"Enter time(mins): ";
//    std::cin >> time1;
////    time1 = stoi(input.substr(0, input.size() - 1));
//
//    std::cout<<"Enter time(sec): ";
//    std::cin >> time2;
////    time2 = stoi(input.substr(0, input.size() - 1));
//
//    std::cout<<"Enter likes: ";
//    std::cin >> likes;
////    likes = stoi(input.substr(0, input.size() - 1));
//
//    int rez = adminService.admin_service_store_tutorial(title, presenter, std::make_pair(time1, time2), likes, link);
//    if (rez == 1) {
//        std::cout << "Tutorial already in the list!\n";
//    }
//}
//
//void Ui::ui_admin_update(){
//    std::string title, presenter, link, input;
//    int time1, time2, likes;
//
//    std::cout<<"Enter link to update: ";
//    std::cin >> input;
//    link = input.substr(0, input.size());
//
//    std::cout<<"Enter new title: ";
//    std::cin >> input;
//    title = input.substr(0, input.size());
//
//    std::cout<<"Enter new presenter: ";
//    std::cin >> input;
//    presenter = input.substr(0, input.size());
//
//    std::cout<<"Enter new time(mins): ";
//    std::cin >> time1;
//    std::cout<<"Enter new time(sec): ";
//    std::cin >> time2;
//
//    std::cout<<"Enter new likes: ";
//    std::cin >> likes;
//
//
//
//    adminService.admin_service_update(link, title, presenter, std::make_pair(time1, time2), likes);
//}
//
//void Ui::ui_admin_delete(){
//    std::string input, link;
//
//    std::cout<<"Enter link to delete: ";
//    std::cin >> input;
//    link = input.substr(0, input.size());
//    adminService.admin_service_remove(link);
//}
//
//void Ui::ui_admin_print_elems() {
//    std::vector<Tutorial>listOfTutorials = adminService.admin_service_get_all();
//    std::cout << '\n';
//    for (auto & listOfTutorial : listOfTutorials)
//        std::cout << listOfTutorial.get_title() << " " << listOfTutorial.get_presenter() << " " << listOfTutorial.get_likes() << " " << listOfTutorial.get_link() <<'\n';
//    std::cout << '\n';
//}
//
//void Ui::print_admin_menu(){
//    std::cout << "0. exit app\n";
//    std::cout << "1. add a tutorial\n";
//    std::cout << "2. update a tutorial\n";
//    std::cout << "3. remove a tutorial\n";
//    std::cout << "4. print all\n";
//}
//
//
///// inherited methods
//
//PrintHTML::~PrintHTML() {
//
//}
//
//PrintHTML::PrintHTML(AService &adminService, Uservice &userService) : Ui(adminService, userService) {
//
//}
//
//PrintCSV::PrintCSV(AService &adminService, Uservice &userService) : Ui(adminService, userService) {
//
//}
