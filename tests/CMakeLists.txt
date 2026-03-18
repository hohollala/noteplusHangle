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
