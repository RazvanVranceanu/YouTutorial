////
//// Created by Razvan Vranceanu on 22.03.2021.
////
//
//#include "test.h"
//#include <iostream>
//#include "../domain/tutorial.h"
//#include "../DV/dv.h"
//#include "../Repository/repo.h"
//#include "../Service/a_service.h"
//#include "../validator/TutorialValidator.h"
//#include "../errors/ValidError.h"
//
//void Tests::run_all_tests(){
//    std::cout << "Starting the tests...\n" << '\n';
//    Tests::run_domain_tests();
//    Tests::run_dynamical_vector_tests();
//    Tests::run_repository_tests();
//    run_service_tests();
//    run_validator_tests();
//    std::cout << "\nEnding the tests ... \n";
//}
//
//void Tests::run_domain_tests() {
//    std::cout << "Starting domain tests\n";
//    Tutorial t = {"Titlu", "Margineanu", std::make_pair(4, 20), 20, "https://www.youtube.com/ceva"};
//    assert(t.get_title() == "Titlu");
//    assert(t.get_presenter() == "Margineanu");
//    assert(t.get_duration() == std::make_pair(4, 20));
//    assert(t.get_likes() == 20);
//    assert(t.get_link() == "https://www.youtube.com/ceva");
//
//    t.set_title("New");
//    t.set_presenter("Eu");
//    t.set_duration(std::make_pair(6, 9));
//    t.set_likes(99);
//    t.set_link("New link");
//
//    assert(t.get_title() == "New");
//    assert(t.get_presenter() == "Eu");
//    assert(t.get_duration() == std::make_pair(6, 9));
//    assert(t.get_likes() == 99);
//    assert(t.get_link() == "New link");
//    std::cout << "Ending domain tests\n";
//}
//
//void Tests::run_dynamical_vector_tests() {
//    std::cout << "Starting dynamical vector tests\n";
//
//    ///test create
//    Dv<int> array{2};
//    assert(array.capacity_dv() == 2);
//    ///test resize
//    array.resize_dv();
//    assert(array.capacity_dv() == 4);
//    ///test append(and over limit)
//    array.append(2);
//    array.append(21);
//    array.append(3);
//    array.append(31);
//    array.append(4);
//    assert(array.size_dv() == 5);
//    assert(array.capacity_dv() == 8);
//    ///test search
//    int poz = array.search(2);
//    assert(poz == 0);
//    int poz2 = array.search(5678);
//    assert(poz2 == -1);
//
//    //todo: make delete tests
//    std::cout << "Ending dynamical vector tests\n";
//
//}
//
//void Tests::run_repository_tests(){
//    std::cout << "Starting repository tests\n";
//    Repository repo;
//    /// tests for adding
//    assert(repo.size_elems() == 0);
//    Tutorial t1 = {"title", "someone", std::make_pair(4, 4), 235, "something"};
//    int rez = repo.admin_repo_store(t1);
//    assert(repo.size_elems() == 1);
//    assert(rez == 0);
//    int rez2 = repo.admin_repo_store(t1);
//    assert(repo.size_elems() == 1);
//    assert(rez2 == 1);
//
//
//    /// tests for removing
//    Tutorial t2 = {"titlu2", "someone", std::make_pair(32, 54), 3421, "something2"};
//    int success;
//    success = repo.admin_repo_store(t2);
//    assert(success == 0);
//    success = repo.admin_repo_remove("something2");
//    assert(success == 0);
//    assert(repo.size_elems() == 1);
//    success = repo.admin_repo_remove("not a link");
//    assert(success == 1);
//
//    ///tests for updating
//    success = repo.admin_repo_update("something", "new_title", "new_presenter", std::make_pair(6, 6), 0);
//    assert(success == 0);
//    Tutorial t0 = repo.get_tutorial_by_position(0);
//    assert(t0.get_title() == "new_title");
//    assert(t0.get_presenter() == "new_presenter");
//    assert(t0.get_duration() == std::make_pair(6, 6));
//    assert(t0.get_likes() == 0);
//
//    success = repo.admin_repo_update("something232", "new_title", "new_presenter", std::make_pair(6, 6), 0);
//    assert(success == 1);
//
//
//    ///tests for getting an element by position - exception
//    try{
//        Tutorial tx = repo.get_tutorial_by_position(-1);
//    }  catch (std::exception Exception){
//        assert(true);
//    }
//
//    std::cout << "Ending repository tests\n";
//}
//
//void Tests::run_service_tests() {
//    std::cout << "Starting service tests\n";
//    Repository repo;
//    AService asrv(repo);
//    ///testing add
//    int rez = asrv.admin_service_store_tutorial("titlu", "eu", std::make_pair(1, 1), 100, "link1");
//    assert(rez == 0);
//    assert(asrv.admin_service_get_all().size() == 1);
//
//    ///testing update
//    rez = asrv.admin_service_update("link1", "new_title", "me", std::make_pair(10, 0), 9);
//    Tutorial t_updated = asrv.get_tutorial_by_position_admin_service(0);
//    assert(t_updated.get_title() == "new_title");
//    assert(t_updated.get_presenter() == "me");
//    assert(t_updated.get_duration() == std::make_pair(10, 0));
//    assert(t_updated.get_likes() == 9);
//
//    ///testing remove
//    rez = asrv.admin_service_remove("link1");
//    assert(rez == 0);
//    assert(asrv.admin_service_get_all().empty());
//
//
//    std::cout << "Ending service tests\n";
//}
//
//void Tests::run_validator_tests() {
//    std::cout << "Starting validation tests\n";
//
//    Tutorial t{"t", "p", std::make_pair(1, 1), 20, "link"};
//    TutorialValidator::validate_tutorial(t);
//
//
//    Tutorial t1{"t1", "p1", std::make_pair(-1, -1), -20, "link1"};
//    try{
//        TutorialValidator::validate_tutorial(t1);
//        assert(false);
//    }catch(const ValidError& ve){
//        assert(ve.get_msg() == "invalid duration!\ninvalid likes!\n");
//    }
//
//
//    std::cout << "Ending validation tests\n";
//}
