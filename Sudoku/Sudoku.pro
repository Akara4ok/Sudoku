QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    difficultywindow.cpp \
    dlx.cpp \
    main.cpp \
    mainwindow.cpp \
    solvesudokuwindow.cpp \
    sudoku.cpp \
    sudokugenerationwindow.cpp \
    topresultswindow.cpp

HEADERS += \
    Node.h \
    difficultywindow.h \
    dlx.h \
    mainwindow.h \
    solvesudokuwindow.h \
    sudoku.h \
    sudokugenerationwindow.h \
    topRLine.h \
    topresultswindow.h

FORMS += \
    difficultywindow.ui \
    mainwindow.ui \
    solvesudokuwindow.ui \
    sudokugenerationwindow.ui \
    topresultswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
