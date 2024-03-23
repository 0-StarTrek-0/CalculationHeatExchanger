QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += qaxcontainer

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Solution.cpp \
    casing.cpp \
    lamellar.cpp \
    main.cpp \
    mainwindow.cpp \
    tubeontube.cpp

HEADERS += \
    Solution.h \
    casing.h \
    lamellar.h \
    mainwindow.h \
    tubeontube.h

FORMS += \
    casing.ui \
    lamellar.ui \
    mainwindow.ui \
    tubeontube.ui

TRANSLATIONS += \
    Heat_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    REsorce.qrc

DISTFILES += \
    Image/free-icon-add-6853377.png \
    Image/free-icon-audit-4592965.png \
    Image/free-icon-clipboard-verification-outlined-sign-58426.png \
    Image/free-icon-cold-3815125.png \
    Image/free-icon-font-angle-left-3916912.png \
    Image/free-icon-font-angle-right-3916907.png \
    Image/free-icon-font-broom-3917053.png \
    Image/free-icon-font-comment-exclamation-8034722.png \
    Image/free-icon-font-disk-3917394.png \
    Image/free-icon-font-file-3917373.png \
    Image/free-icon-font-folder-3917537.png \
    Image/free-icon-font-question-square-7931050.png \
    Image/free-icon-font-settings-3917058.png \
    Image/free-icon-font-sign-in-alt-5528136.png \
    Image/free-icon-hot-temperature-3814951.png \
    Image/free-icon-list-137932.png \
    Image/free-icon-nu-10025058.png \
    Image/free-icon-thermometer-2426704.png \
    Image/free-icon-thermometer-2426721.png \
    Image/free-icon-underfloor-heating-6165160.png
