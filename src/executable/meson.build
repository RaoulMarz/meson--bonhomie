incdir_general = include_directories('../libs/include')
incdir_util = include_directories('../libs/utilities')
incdir_enums = include_directories('../libs/enums')
incdir_datetime = include_directories('../libs/datetime')
incdir_models = include_directories('../libs/models')
incdir_service = include_directories('../libs/service')
incdir_uuid = include_directories('../libs/uuid')
incdir_random = include_directories('../libs/random')
incdir_jsoncpp = include_directories('../libs/jsoncpp')
incdir_signalrh = include_directories('../libs/signalRHelper')
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
'../libs/utilities/extrahelper.cpp',
'../libs/utilities/CalendarDate.cpp',
'../libs/utilities/GameInfoLogger.cpp',
'../libs/utilities/json_helpers.cpp',
'../libs/models/GameConfig.cpp',
'../libs/models/World.cpp',
'../libs/models/GameState.cpp',
'../libs/models/Map.cpp',
'../libs/models/PopulationTier.cpp',
'../libs/service/BotService.cpp',
'../libs/random/FastNoise.cpp',
'../libs/random/RandomProvider.cpp',
'../libs/random/RandomUtility.cpp',
'../libs/jsoncpp/jsoncpp.cpp',
'../libs/signalRHelper/SignalRHelper.cpp'
])
#dependencies : bonhomie_dep)