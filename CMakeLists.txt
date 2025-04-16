cmake_minimum_required(VERSION 3.19)
project(StarWar LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Multimedia )
find_package(Qt6 REQUIRED COMPONENTS Gui)

qt_standard_project_setup()

qt_add_executable(StarWar
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainscreen.cpp
    mainscreen.h
    mainscreen.ui
    config.h
    Resource.qrc
    Map.h Map.cpp
    heroplane.h heroplane.cpp
    bullet.h bullet.cpp
    enemyplane.h enemyplane.cpp
    bomb.h bomb.cpp
)

qt_add_translations(
    TARGETS StarWar
    TS_FILES StarWar_zh_CN.ts
)

target_link_libraries(StarWar
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Multimedia
        Qt6::Multimedia
        Qt6::Gui
)

include(GNUInstallDirs)

install(TARGETS StarWar
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET StarWar
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
