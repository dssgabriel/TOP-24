project('vector', 'c',
  version : '0.1',
  default_options : ['c_std=c2x', 'warning_level=2'])

incdir = include_directories('include')

executable('vector',
           'src/compute.c',
           'src/main.c',
           'src/vector.c',
           include_directories: incdir)
