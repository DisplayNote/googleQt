## Install rules ##

BUILD_TYPE=Debug
CONFIG(release, debug|release) {
    BUILD_TYPE=Release
}

# Installation prefix and library directory
isEmpty(PREFIX) {
    PREFIX = $$PWD/../install/
    android: PREFIX = $$PREFIX/Android/$$BUILD_TYPE
    ios:     PREFIX = $$PREFIX/iOS/$$BUILD_TYPE
    macx:    PREFIX = $$PREFIX/Macos/$$BUILD_TYPE
    win32:   PREFIX = $$PREFIX/Windows/$$BUILD_TYPE
}

# Path where install the static library
target.path = $$PREFIX/lib

# Path and files for install the headers
headers.path = $$PREFIX/include/googleQt
headers.files = $$HEADERS
INSTALLS += target headers
