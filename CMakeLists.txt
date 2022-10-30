project(sail-multitran CXX)
cmake_minimum_required(VERSION 3.5)

find_package (Qt5 COMPONENTS Core Network Qml Gui Quick REQUIRED)

include(FindPkgConfig)
pkg_search_module(SAILFISH sailfishapp REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")

add_executable(sail-multitran ${CPP_SOURCES})

target_include_directories(sail-multitran PRIVATE "src")

target_compile_definitions(sail-multitran PRIVATE
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)
target_include_directories(sail-multitran PRIVATE
    $<BUILD_INTERFACE:
    ${SAILFISH_INCLUDE_DIRS}
>)
target_link_libraries(sail-multitran
    Qt5::Quick
    ${SAILFISH_LDFLAGS}
)

install(TARGETS sail-multitran
    RUNTIME DESTINATION bin
)
install(DIRECTORY qml
    DESTINATION share/sail-multitran
)
install(DIRECTORY translations
    DESTINATION share/sail-multitran
    FILES_MATCHING PATTERN "*.qm"
)
install(FILES sail-multitran.desktop
    DESTINATION share/applications
)
install(FILES icons/86x86/sail-multitran.png
    DESTINATION share/icons/hicolor/86x86/apps
)
install(FILES icons/108x108/sail-multitran.png
    DESTINATION share/icons/hicolor/108x108/apps
)
install(FILES icons/128x128/sail-multitran.png
    DESTINATION share/icons/hicolor/128x128/apps
)
install(FILES icons/172x172/sail-multitran.png
    DESTINATION share/icons/hicolor/172x172/apps
)

# Get the other files reachable from the project tree in Qt Creator
FILE(GLOB TsFiles "translations/*.ts")
FILE(GLOB_RECURSE UIFiles "qml/*.qml")
add_custom_target(distfiles
    SOURCES
        sail-multitran.desktop
        ${UIFiles}
        rpm/sail-multitran.changes.in
        rpm/sail-multitran.changes.run.in
        rpm/sail-multitran.spec
        rpm/sail-multitran.yaml
        ${TsFiles})

# Tell Qt Creator where the application executable(s) would be located on the
# device.
#
# It is not necessary to list other deployables than executables (runtime
# targets) here. The deployment process of Sailfish OS projects is opaque to
# Qt Creator and the information contained in QtCreatorDeployment.txt is only
# used to locate the executable associated with the active run configuration
# on the device in order to run it.
#
# Search the Qt Creator Manual to learn about the QtCreatorDeployment.txt file
# format.
file(WRITE "${CMAKE_BINARY_DIR}/QtCreatorDeployment.txt"
    "${CMAKE_INSTALL_PREFIX}
${CMAKE_BINARY_DIR}/sail-multitran:bin
")

