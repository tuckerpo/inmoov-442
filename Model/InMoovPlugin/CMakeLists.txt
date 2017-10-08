if(NOT ENABLE_GUI)
  return()
endif()

option(BUILD_PROTOTYPE_INMOOV "Building a plugin for InMoov \"InMoovPlugin\"" OFF)

if(BUILD_PROTOTYPE_INMOOV)
  set(target CnoidInMoovPlugin)
  add_cnoid_plugin(${target} SHARED InMoovPlugin.cpp)
  target_link_libraries(${target} CnoidBodyPlugin)
  apply_common_setting_for_plugin(${target})

  if(QT5)
    qt5_use_modules(${target} Widgets)
  endif()
endif()

install_sample_source(InMoovPlugin.cpp)
