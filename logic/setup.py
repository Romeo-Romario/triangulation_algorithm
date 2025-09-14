from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import pybind11
import os

ext_modules = [
    Extension(
        "geometry",  # module name
        sources=[
            "bindings.cpp",
            os.path.join("src", "my_functions.cpp"),
            os.path.join("src", "figures.cpp"),
        ],
        include_dirs=[
            pybind11.get_include(),
            "headers",  # location of figures.hpp, my_functions.hpp
            "src",
        ],
        language="c++",
        extra_compile_args=["/std:c++20"],  # MSVC
    )
]

setup(
    name="geometry",
    version="0.1",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)
