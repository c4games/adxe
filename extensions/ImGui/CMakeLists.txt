set(target_name ImGui)

include_directories(src/ImGui/imgui)

set(HEADER
    src/ImGui/ImGuiPresenter.h
    # CCImGuiColorTextEdit.h
    src/ImGui/imgui/imconfig.h
    src/ImGui/imgui/imgui.h
    src/ImGui/imgui/imgui_internal.h
    src/ImGui/imgui/imstb_rectpack.h
    src/ImGui/imgui/imstb_textedit.h
    src/ImGui/imgui/imstb_truetype.h
    src/ImGui/imgui/misc/cpp/imgui_stdlib.h
    #~ imgui_markdown/imgui_markdown.h
    #~ ImGuiColorTextEdit/TextEditor.h
    #~ implot/implot.h
)

set(SOURCE
    src/ImGui/ImGuiPresenter.cpp
    # CCImGuiColorTextEdit.cpp
    src/ImGui/imgui/imgui.cpp
    src/ImGui/imgui/imgui_demo.cpp
    src/ImGui/imgui/imgui_draw.cpp
    src/ImGui/imgui/imgui_widgets.cpp
    src/ImGui/imgui/imgui_tables.cpp
    src/ImGui/imgui/misc/cpp/imgui_stdlib.cpp
    #~ ImGuiColorTextEdit/TextEditor.cpp
    #~ implot/implot.cpp
    #~ implot/implot_demo.cpp
)

if(ANDROID)
    list(APPEND SOURCE src/ImGui/imgui_impl_ax_android.cpp)
    list(APPEND HEADER src/ImGui/imgui_impl_ax_android.h)
else()
    list(APPEND SOURCE src/ImGui/imgui_impl_ax.cpp)
    list(APPEND HEADER src/ImGui/imgui_impl_ax.h)
endif()

#~ if(AX_ENABLE_EXT_LUA)
#~     include_directories(
#~         lua-bindings
#~         ${_AX_ROOT}/3rdparty/lua/luajit/include
#~         ${_AX_ROOT}/3rdparty/lua/tolua
#~     )
#~     list(APPEND HEADER
#~         lua-bindings/imgui_lua.hpp
#~         lua-bindings/lua_conversion.hpp
#~         lua-bindings/lua_imgui_auto.hpp
#~         lua-bindings/lua_imguiDrawList_auto.hpp
#~         lua-bindings/lua_imguiFont_auto.hpp
#~         lua-bindings/lua_imguiIO_auto.hpp
#~         lua-bindings/lua_imguiStyle_auto.hpp
#~         lua-bindings/lua_imguiViewport_auto.hpp
#~         lua-bindings/lua_ImGuiColorTextEdit_auto.hpp
#~         lua-bindings/lua_implot_auto.hpp
#~     )
#~     list(APPEND SOURCE
#~         lua-bindings/imgui_lua.cpp
#~         lua-bindings/lua_imguiDrawList_auto.cpp
#~         lua-bindings/lua_imguiFont_auto.cpp
#~         lua-bindings/lua_imguiIO_auto.cpp
#~         lua-bindings/lua_imguiStyle_auto.cpp
#~         lua-bindings/lua_imguiViewport_auto.cpp
#~         lua-bindings/lua_imgui_auto.cpp
#~         lua-bindings/lua_ImGuiColorTextEdit_auto.cpp
#~         lua-bindings/lua_implot_auto.cpp
#~     )
#~ endif()

add_library(${target_name} STATIC
        ${HEADER}
        ${SOURCE})

if(WASM)
    target_compile_definitions(${target_name} PRIVATE EMSCRIPTEN_USE_EMBEDDED_GLFW3=1)
endif()

target_include_directories(${target_name} 
    PUBLIC src
    PUBLIC src/ImGui/imgui
    
    INTERFACE src
    INTERFACE src/ImGui/imgui
    )

ax_find_shaders(${CMAKE_CURRENT_LIST_DIR}/shaders IMGUI_SHADER_SOURCES)
ax_target_compile_shaders(${target_name} FILES ${IMGUI_SHADER_SOURCES} CUSTOM)

setup_ax_extension_config(${target_name})
