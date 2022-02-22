////
//// Created by Razvan Vranceanu on 23.03.2021.
////
//
//#ifndef A45_RAZVANVRANCEANU21_UI_H
//#define A45_RAZVANVRANCEANU21_UI_H
//#include "../Repository/repo.h"
//#include "../Service/a_service.h"
//#include "../Service/user_service.h"
//#include <iostream>
//#include <fstream>
//
//class Ui{
//protected:
//    AService& adminService;
//    Uservice& userService;
//
//public:
//    Ui(AService& adminService, Uservice& userService);
//    virtual ~Ui();
//    void print_admin_menu();
//    void ui_admin_add();
//    void ui_admin_update();
//    void ui_admin_delete();
//    void ui_admin_print_elems();
//
//    static void print_user_menu();
//    void ui_user_start_watching();
//    void ui_user_start_iterate(const std::string &presenter);
//    virtual void ui_user_see_watchlist() ;
//    void ui_user_delete_tutorial(int position);
//    void ui_user_rate_tutorial(int position);
//
//    void run();
//    void run_admin_mode();
//    void run_user_mode();
//};
//
//class PrintHTML : public Ui {
//public:
//
//    PrintHTML(AService &adminService, Uservice &userService);
//
//    ~PrintHTML();
//
//    void ui_user_see_watchlist() override {
//        std::ofstream fout("tutorial.html");
//        fout << "<!DOCTYPE html>\n";
//        fout << "<html>\n<head>\n";
//        fout << "<title>\nTutorial\n</title>\n";
//        fout << "</head>\n<body>\n";
//        fout << "<table border=\"1\">\n";
//        std::vector<Tutorial>listOfTutorials = userService.get_watchlist();
//        for(auto& tutorial: listOfTutorials) {
//            fout << "<tr>\n";
//            fout << "<td>" << tutorial.get_title() << "</td>";
//            fout << "<td>" << tutorial.get_presenter() << "</td>";
//            fout << "<td>" << tutorial.get_likes() << "</td>";
//            fout << "<td>" << tutorial.get_duration().first << "</td>";
//            fout << "<td>" << tutorial.get_duration().second << "</td>";
//        }
//        fout << "</table>\n</body>\n</html>";
//    };
//};
//
//class PrintCSV : public Ui{
//public:
//
//    PrintCSV(AService &adminService, Uservice &userService);
//
//    void ui_user_see_watchlist() override {
//        std::ofstream fout("tutorial.csv");
//        std::vector<Tutorial>listOfTutorials = userService.get_watchlist();
//        for(auto& tutorial: listOfTutorials)
//            fout << tutorial.get_title() << "," << tutorial.get_presenter() << "," << tutorial.get_likes() << "," <<
//                       tutorial.get_duration().first << "," << tutorial.get_duration().second << '\n';
//    };
//};
//
//#endif //A45_RAZVANVRANCEANU21_UI_H
//
//
