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

INSTALL_HEADERS = $$HEADERS

for(header, INSTALL_HEADERS) {
  path = $${PREFIX}/include/src/$${dirname(header)}
  eval(headers_$${path}.files += $$header)
  eval(headers_$${path}.path = $$path)
  eval(INSTALLS *= headers_$${path})
}

INSTALLS += target
