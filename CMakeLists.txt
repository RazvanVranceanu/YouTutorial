cmake_minimum_required(VERSION 3.21)
project(YouTutorial)

set(CMAKE_CXX_STANDARD 14)

include_directories(domain)
include_directories(tests)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "/Users/razvanvranceanu/Qt/5.15.2/clang_64/lib/cmake")
set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)


add_executable(YouTutorial
        tests/test.cpp
        tests/test.h
        domain/tutorial.cpp
        domain/tutorial.h
        main.cpp
        DV/dv.cpp
        DV/dv.h
        Repository/repo.cpp
        Repository/repo.h
        Service/a_service.cpp
        Service/a_service.h
        Ui/ui.cpp
        Ui/ui.h
        Service/user_service.cpp
        Service/user_service.h
        validator/TutorialValidator.cpp
        validator/TutorialValidator.h
        errors/ValidError.cpp
        errors/ValidError.h GUI/AdminGUI.cpp GUI/AdminGUI.h GUI/QtMenu.cpp GUI/QtMenu.h GUI/UserGUI.cpp GUI/UserGUI.h undo_redo/action.cpp undo_redo/action.h undo_redo/undo_redo.cpp undo_redo/undo_redo.h)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})