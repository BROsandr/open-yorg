import os
include = ['../include/']
libs = ['sfml-graphics', 'sfml-system', 'sfml-window']
cxxflags = ['-Wall' ,'-Wextra' ,'-pedantic' ,'-std=c++17' ,'-O2' ,'-Wshadow' ,'-Wformat=2' ,'-Wfloat-equal' ,'-Wconversion' ,'-Wcast-qual' ,'-Wcast-align' ,'-D_GLIBCXX_DEBUG' ,'-D_GLIBCXX_DEBUG_PEDANTIC' ,'-D_FORTIFY_SOURCE=2' ,'-fsanitize=address' ,'-fsanitize=undefined', '-fno-sanitize-recover', '-fstack-protector']
cxxflags_turning_off = ['-Wno-overloaded-virtual', '-Wno-float-conversion', '-Wno-implicit-int-float-conversion', '-Wno-sign-conversion', '-Wno-shorten-64-to-32', '-Wno-implicit-float-conversion']
cxxflags += cxxflags_turning_off + ['-Werror']
linkflags =['-D_GLIBCXX_DEBUG' ,'-D_GLIBCXX_DEBUG_PEDANTIC' ,'-D_FORTIFY_SOURCE=2' ,'-fsanitize=address' ,'-fsanitize=undefined', '-fno-sanitize-recover', '-fstack-protector']
env = Environment(CPPPATH=include, LINKFLAGS = linkflags, LIBS=libs, CXX = '/home/alex/Downloads/clang+llvm-14.0.0-x86_64-linux-gnu-ubuntu-18.04/bin/clang++', CXXCOMSTR = "Compiling $SOURCE", LINKCOMSTR = "Linking $TARGET"  ,CXXFLAGS = cxxflags)
env['ENV']['TERM'] = os.environ['TERM']
env.Decider('MD5-timestamp')
env.Tool('compilation_db')
env.CompilationDatabase()
sources = Glob('*/*.cpp') + Glob('*.cpp')
env.Program('open-yorg', sources)