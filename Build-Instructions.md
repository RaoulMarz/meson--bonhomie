# Building this application with meson

Ensure that you have meson installed. Instructions for doing so can be found [here](https://mesonbuild.com/Getting-meson.html)

***N.B. It is highly recommended to have a recent C++ compiler suite and python 3 installed***

The clang compiler version 12 or later is the recommended C/C++ compiler and meson version 0.63.2 was used to successfully build the executable in Linux

## Commands Ensemble

The starter meson.build is in the root directory and is needed to kick things off

To start with, here all the most often used commands that can be entered at the CLI of your favourite terminal

```
CC=clang CXX=clang++ meson build
CC=clang CXX=clang++ meson --reconfigure build
ninja -C build
```

The first 2 commands are similar, with the only difference that the 1st one is meant for a project where no build or an empty build directory exists in the root folder.

Once the meson command to build have been completed after any changes to the meson.build files have been made, the last command "ninja -C build" can be run. Only this last command "ninja -C build" needs to be run when editing existing source code, i.e cpp and h source files


### 1.1 The stucture of the meson build files

The meson.build in the root folder has the following content :-
```
project('bonhomie', 'cpp', default_options : ['cpp_std=c++17'],
        version : '0.22')
#subdir('src/libs')
subdir('src/executable')
```

The meson.build in the executable sub folder, showing only the important parts of the file
```
incdir_general = include_directories('../libs/include')
incdir_util = include_directories('../libs/utilities')
incdir_enums = include_directories('../libs/enums')
....
....
cpp = meson.get_compiler('cpp')
lib_signalr = cpp.find_library('microsoft-signalr',
               dirs : ['/usr/lib64'])
#add_global_arguments('-lstdc++fs', language : 'cpp')
executable('bonhomie',
# link_args : '-lstdc++fs',
cpp_args : [ '-fdeclspec', '-fpermissive' ],
dependencies : [lib_signalr],
include_directories : [ incdir_general, incdir_util, incdir_enums, incdir_datetime, incdir_models, 
incdir_service, incdir_uuid, incdir_random, incdir_jsoncpp, incdir_signalrh],
sources : ['main.cpp',
'../libs/datetime/datetime.cpp',
'../libs/datetime/timespan.cpp',
....
....
'../libs/jsoncpp/jsoncpp.cpp',
'../libs/signalRHelper/SignalRHelper.cpp'
])
```

All bots must listen to the following events that are announced by the hub:
- `Registered`
- `Disconnect`
- `ReceiveBotState`

