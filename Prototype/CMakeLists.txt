
if(NOT ENABLE_GUI)
  return()
endif()

option(BUILD_PROTOTYPE "Building a sample plugin \"PrototypePlugin\"" OFF)

if(BUILD_PROTOTYPE)
  set(target CnoidPrototypePlugin)
  add_cnoid_plugin(${target} SHARED PrototypePlugin.cpp)
  target_link_libraries(${target} CnoidBodyPlugin)
  apply_common_setting_for_plugin(${target})

  if(QT5)
    qt5_use_modules(${target} Widgets)
  endif()
endif()

install_sample_source(PrototypePlugin.cpp)
