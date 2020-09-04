from distutils.core import setup, Extension

module1 = Extension('demo',
                    sources = ['demomodule.cpp', 'myclass.cpp'])

setup (name = 'PackageName',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [module1])
