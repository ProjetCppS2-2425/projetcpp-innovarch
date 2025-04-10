# ...existing code...

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts)

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Charts
)

# ...existing code...