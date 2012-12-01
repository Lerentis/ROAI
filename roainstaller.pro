#-------------------------------------------------
#
# Project created by QtCreator 2012-11-21T09:57:59
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = roainstaller
TEMPLATE = app

# Special libs for windows build
#win32
#{
#    win32-msvc*:contains(QMAKE_TARGET.arch, x86_64):
#    {
#        LIBS += "C:/Program Files/Microsoft SDKs/Windows/v7.1/Lib/x64/Shell32.lib"
#    }
#    else
#    {
#    }
#}

SOURCES +=      src/cpp/main.cpp\
                src/cpp/roapagewelcome.cpp \
                src/cpp/roapagelicense.cpp \
                src/cpp/roapagecomponents.cpp \
                src/cpp/roapageinstall.cpp \
                src/cpp/roapagestatus.cpp \
                src/cpp/roapagefinish.cpp \
                src/cpp/roainstaller.cpp

HEADERS  +=     src/h/roapagewelcome.h \
                src/h/roapagelicense.h \
                src/h/roapagecomponents.h \
                src/h/roapageinstall.h \
                src/h/roapagestatus.h \
                src/h/roapagefinish.h \
                src/h/roainstaller.h

FORMS    +=     src/ui/roapagewelcome.ui \
                src/ui/roapagelicense.ui \
                src/ui/roapagecomponents.ui \
                src/ui/roapageinstall.ui \
                src/ui/roapagestatus.ui \
                src/ui/roapagefinish.ui

TRANSLATIONS =  resources/translation/roai_eng.ts \
                resources/translation/roai_ger.ts \
                resources/translation/roai_fra.ts \
                resources/translation/roai_spa.ts \
                resources/translation/roai_ita.ts

RESOURCES +=    resources/res.qrc

OTHER_FILES +=

