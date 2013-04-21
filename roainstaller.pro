#-------------------------------------------------
#
# Project created by QtCreator 2012-11-21T09:57:59
#
#-------------------------------------------------

QT       += core gui network widgets

#QTPLUGIN += xcb

TARGET = roainstaller
TEMPLATE = app

# Special libs for windows build
win32 {
    message( "Building for windows")

    win32-msvc*:contains(QMAKE_TARGET.arch, x86_64) {
        message( "Building for 64 bit")

        # Add libs
        LIBS += "C:/buildenv/w8sdk/Lib/win8/um/x64/shell32.lib"
        LIBS += "D:/03_dist/02_openssl-static/out64/libeay32.lib"
        LIBS += "D:/03_dist/02_openssl-static/out64/ssleay32.lib"
    } else {
        message( "Building for 32 bit")

        # Add libs
        LIBS += "C:/buildenv/w8sdk/Lib/win8/um/x86/shell32.lib"
        LIBS += "D:/03_dist/02_openssl-static/out32/libeay32.lib"
        LIBS += "D:/03_dist/02_openssl-static/out32/ssleay32.lib"
    }
}

SOURCES +=      src/cpp/main.cpp\
                src/cpp/roapagewelcome.cpp \
                src/cpp/roapagelicense.cpp \
                src/cpp/roapagecomponents.cpp \
                src/cpp/roapageinstall.cpp \
                src/cpp/roapagestatus.cpp \
                src/cpp/roapagefinish.cpp \
                src/cpp/roainstaller.cpp \
                src/cpp/roamainwidget.cpp \
                src/cpp/windowsprocess.cpp

HEADERS  +=     src/h/roapagewelcome.h \
                src/h/roapagelicense.h \
                src/h/roapagecomponents.h \
                src/h/roapageinstall.h \
                src/h/roapagestatus.h \
                src/h/roapagefinish.h \
                src/h/roainstaller.h \
                src/h/roamainwidget.h \
    src/h/windowsprocess.h

FORMS    +=     src/ui/roapagewelcome.ui \
                src/ui/roapagelicense.ui \
                src/ui/roapagecomponents.ui \
                src/ui/roapageinstall.ui \
                src/ui/roapagestatus.ui \
                src/ui/roapagefinish.ui \
                src/ui/roamainwidget.ui

TRANSLATIONS =  resources/translations/roai_french.ts \
                resources/translations/roai_greek.ts \
                resources/translations/roai_italian.ts \
                resources/translations/roai_polish.ts \
                resources/translations/roai_portuguese.ts \
                resources/translations/roai_spanish.ts \
                resources/translations/roai_swedish.ts \
                resources/translations/roai_english.ts \
                resources/translations/roai_german.ts

RESOURCES +=    resources/res.qrc

RC_FILE =       src/roainstaller.rc

OTHER_FILES +=

