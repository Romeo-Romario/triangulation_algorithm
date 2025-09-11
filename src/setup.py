from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import pybind11

ext_modules = [
    Extension(
        "geometry",  # module name
        sources=["bindings.cpp"],  # your binding code
        include_dirs=[
            pybind11.get_include(),
            "src/headers",  # location of figures.hpp, my_functions.hpp
        ],
        language="c++",
        extra_compile_args=["-std=c++17"],  # or "/std:c++17" on MSVC
    )
]

setup(
    name="geometry",
    version="0.1",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)
