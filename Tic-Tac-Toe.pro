QT       += core gui sql testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Main application target
TARGET = Tic-Tac-Toe

# Sources for the main application
SOURCES += main.cpp \
           aiwindow.cpp \
           authenticationwindow.cpp \
           chooseaiwindow.cpp \
           dialog.cpp \
           historywindow.cpp \
           loginwindow.cpp \
           mainwindow.cpp \
           multiplayerwindow.cpp \
           replaygamewindow.cpp \
           replaywindow.cpp \
           signupwindow.cpp \
           user2window.cpp

HEADERS += aiwindow.h \
           authenticationwindow.h \
           chooseaiwindow.h \
           dialog.h \
           historywindow.h \
           loginwindow.h \
           mainwindow.h \
           multiplayerwindow.h \
           replaygamewindow.h \
           replaywindow.h \
           sessionmanager.h \
           signupwindow.h \
           user2window.h

FORMS += aiwindow.ui \
         authenticationwindow.ui \
         chooseaiwindow.ui \
         dialog.ui \
         historywindow.ui \
         loginwindow.ui \
         mainwindow.ui \
         multiplayerwindow.ui \
         replaygamewindow.ui \
         replaywindow.ui \
         signupwindow.ui \
         user2window.ui

# Test application target
test {
    TEMPLATE = app
    TARGET = tests

    CONFIG += testcase
    DEFINES += RUNNING_TESTS

    # Sources for the test application
    SOURCES += tests/all_tests.cpp \
               tests/test_aiwindow.cpp \
               tests/test_aiwindow_intigration.cpp \
               tests/test_multiPlayerWindow_intigration.cpp \
               tests/test_multiplayerwindow.cpp \
               tests/test_usersignuplogin.cpp
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
