add_executable(scintilla_qt_ime_regression
    ../src/QRegexSearch.cpp
    scintilla_qt_ime_regression.cpp
)

target_include_directories(scintilla_qt_ime_regression
    PRIVATE
        ../src
)

target_link_libraries(scintilla_qt_ime_regression
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        scintilla
)

add_test(
    NAME scintilla_qt_ime_regression
    COMMAND scintilla_qt_ime_regression
)

set_tests_properties(scintilla_qt_ime_regression PROPERTIES
    ENVIRONMENT "QT_QPA_PLATFORM=offscreen"
)

add_executable(session_defaults_regression
    ../src/ApplicationSettings.cpp
    session_defaults_regression.cpp
)

target_include_directories(session_defaults_regression
    PRIVATE
        ../src
)

target_link_libraries(session_defaults_regression
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

add_test(
    NAME session_defaults_regression
    COMMAND session_defaults_regression
)

set_tests_properties(session_defaults_regression PROPERTIES
    ENVIRONMENT "QT_QPA_PLATFORM=offscreen"
)
