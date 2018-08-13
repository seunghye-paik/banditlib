APPNAME = 'bandit'
VERSION = '0.1.0'

CXXFLAGS = ['-O2', '-Wall', '-Wextra', '-std=c++0x', '-g']

top = '.'
out = 'build'

def options(opt):
  opt.load('compiler_cxx')

def configure(conf):
  conf.load('compiler_cxx')

def build(bld):
  bld(features = 'cxx cxxprogram', source = 'bandit/util.cpp main.cpp',includes = [".", "./bandit"], target = 'main', cxxflags = CXXFLAGS)



