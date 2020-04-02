import os
from conans import ConanFile
from conans import tools

class GoogleQtConan(ConanFile):
    name = "GoogleQt"
    version = "1.0.0"
    settings = "os", "compiler", "build_type", "arch"
    description = "Package for GoogleQt"
    url = "None"
    license = "None"
    generators = "qmake"

    def package(self):
        self.copy('*', 'include', os.path.join('install', str(self.settings.os), str(self.settings.build_type), 'include'))
        self.copy('*', 'lib', os.path.join('install', str(self.settings.os), str(self.settings.build_type), 'lib'))

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
