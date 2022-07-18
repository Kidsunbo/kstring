from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout
from conans import tools

class KstringConan(ConanFile):
    name = "kstring"
    version = "0.0.1"

    # Optional metadata
    license = "MIT"
    author = "Kie <qiongxiaozi158@sina.com>"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "A easy to use string library"
    topics = ("String", "Basic", "Utility")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "include/*", "LICENSE"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    @property
    def _minimum_cpp_standard(self):
        return 20

    def validate(self):
        if self.settings.get_safe("compiler.cppstd"):
            tools.check_min_cppstd(self, self._minimum_cpp_standard)

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def package(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.install()

    def package_id(self):
        self.info.header_only()
