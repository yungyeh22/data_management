QT -= gui
QT += xml

CONFIG += c++11 #  console
CONFIG -= app_bundle
CONFIG -= debug_and_release
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    Test\test.cpp \
    Serialization\ISerializable.cpp \
    ObjectMgmt\Value.cpp \
    Serialization\ISerializableContainer.cpp \
    Test\SerializableObj.cpp \
    Serialization\ObjectToSerialize.cpp \
    Serialization\UniversalSerializer.cpp \
    Test\SerializableObj2.cpp \
    Serialization\XmlUtility.cpp \
    ObjectMgmt\PObject.cpp

HEADERS += \
    Test\test.h \
    Serialization\ISerializable.h \
    ObjectMgmt\Value.h \
    Serialization\ISerializableContainer.h \
    Test\SerializableObj.h \
    Serialization\ObjectToSerialize.h \
    Serialization\UniversalSerializer.h \
    Test\SerializableObj2.h \
    SerializeCore.h \
    Serialization\XmlUtility.h \
    ObjectMgmt\PObject.h
