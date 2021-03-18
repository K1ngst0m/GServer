project(DemoPlugin)

add_library(
        ${PROJECT_NAME}

        "PlugInMain.cpp"
        "DemoModule.cpp"
        "DemoPlugin.cpp"
)