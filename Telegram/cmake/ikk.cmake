set(ikk_sources
    ikk/chats/layout.cpp
    ikk/chats/list_refresher.cpp
    ikk/chats/promotions.cpp
    ikk/compose/channel.cpp
    ikk/compose/confirm.cpp
    ikk/compose/format_toolbar.cpp
    ikk/compose/placeholder.cpp
    ikk/compose/spacing.cpp
    ikk/compose/text.cpp
    ikk/core/language.cpp
    ikk/core/exchange.cpp
    ikk/core/options.cpp
    ikk/core/regex.cpp
    ikk/core/diagnostics.cpp
    ikk/core/relaunch.cpp
    ikk/core/updates.cpp
    ikk/core/version.cpp
    ikk/display/view_refresher.cpp
    ikk/export/range_model.cpp
    ikk/interface/main_menu.cpp
    ikk/interface/main_menu_model.cpp
    ikk/interface/notifications.cpp
    ikk/interface/text.cpp
    ikk/interface/appearance.cpp
    ikk/interface/app_icon.cpp
    ikk/chats/startup_folder.cpp
    ikk/chats/sort.cpp
    ikk/chats/recent_chats.cpp
    ikk/chats/local_pins.cpp
    ikk/chats/local_pins_model.cpp
    ikk/chats/cleanup.cpp
    ikk/chats/cleanup_model.cpp
    ikk/chats/reading_position.cpp
    ikk/chats/tools.cpp
    ikk/chats/community.cpp
    ikk/chats/folders.cpp
    ikk/chats/managed_folders.cpp
    ikk/interface/roundness.cpp
    ikk/settings/interface.cpp
    ikk/settings/restart.cpp
    ikk/menu/actions.cpp
    ikk/menu/batch.cpp
    ikk/menu/media.cpp
    ikk/menu/download.cpp
    ikk/menu/draft.cpp
    ikk/menu/rating.cpp
    ikk/menu/message_tools.cpp
    ikk/menu/model.cpp
    ikk/menu/repeat.cpp
    ikk/menu/reading.cpp
    ikk/menu/selection.cpp
	ikk/media/sticker_catalog.cpp
    ikk/media/audio.cpp
    ikk/media/cover.cpp
    ikk/media/sticker_export.cpp
    ikk/media/sticker_export_model.cpp
    ikk/media/url_template.cpp
    ikk/media/extras.cpp
    ikk/media/local_faved.cpp
    ikk/media/local_faved_model.cpp
    ikk/messages/format.cpp
    ikk/messages/markdown.cpp
    ikk/messages/content.cpp
    ikk/messages/badges.cpp
    ikk/messages/effects.cpp
    ikk/messages/online.cpp
    ikk/messages/reactions.cpp
    ikk/messages/reading.cpp
    ikk/tests/menu_scenario.cpp
    ikk/filters/model.cpp
    ikk/filters/view.cpp
    ikk/filters/settings.cpp
    ikk/filters/menu.cpp
    ikk/filters/hidden_messages.cpp
    ikk/links/model.cpp
    ikk/links/open.cpp
    ikk/links/behavior.cpp
    ikk/links/inline_bot.cpp
    ikk/links/inline_rules.cpp
    ikk/links/inline_settings.cpp
    ikk/links/webview.cpp
    ikk/links/settings.cpp
    ikk/network/model.cpp
    ikk/network/runtime.cpp
    ikk/notifications/model.cpp
    ikk/notifications/review.cpp
    ikk/notifications/settings.cpp
    ikk/snapshot/snapshot.cpp
    ikk/snapshot/cloud_theme.cpp
    ikk/snapshot/cloud_theme_model.cpp
    ikk/privacy/profile.cpp
    ikk/privacy/alias.cpp
    ikk/privacy/admin_shortcuts.cpp
    ikk/privacy/display.cpp
    ikk/privacy/alias_model.cpp
    ikk/privacy/protection.cpp
    ikk/privacy/protection_model.cpp
    ikk/settings/home.cpp
    ikk/settings/rules.cpp
    ikk/settings/network.cpp
    ikk/settings/chats.cpp
    ikk/settings/compose.cpp
	ikk/settings/config.cpp
    ikk/settings/cloud_sync.cpp
    ikk/sync/model.cpp
    ikk/sync/saved_messages.cpp
    ikk/sync/service.cpp
    ikk/settings/media.cpp
    ikk/settings/menu.cpp
    ikk/settings/privacy.cpp
    ikk/settings/messages.cpp
    ikk/settings/services.cpp
    ikk/services/credentials.cpp
    ikk/services/auto_translate.cpp
    ikk/services/auto_translate_model.cpp
    ikk/services/chat_translation.cpp
    ikk/services/chat_translation_model.cpp
    ikk/services/context.cpp
    ikk/services/context_model.cpp
    ikk/services/model.cpp
    ikk/services/presets.cpp
    ikk/services/store.cpp
    ikk/services/summary.cpp
    ikk/services/summary_model.cpp
    ikk/services/request.cpp
    ikk/services/translation.cpp
    ikk/services/draft_translation.cpp
    ikk/services/send_translation.cpp
    ikk/services/send_translation_model.cpp
    ikk/services/transcription.cpp
    ikk/services/transcription_queue.cpp
    ikk/services/system_ai.cpp
)

if (ikk_sources)
    nice_target_sources(Telegram ${src_loc} PRIVATE ${ikk_sources})
endif()

include(${CMAKE_CURRENT_LIST_DIR}/ikk_version.cmake)

if (NOT DESKTOP_APP_DISABLE_AUTOUPDATE)
    # The packer signs only v2 packages and needs no upstream private keys.
    # Its target is created after this file is included.
    cmake_language(DEFER CALL
        target_compile_definitions Packer PRIVATE PACKER_DISABLE_PRIVATE)
endif()

if (APPLE AND NOT DESKTOP_APP_DISABLE_SWIFT6)
    enable_language(Swift)
    set_target_properties(Telegram PROPERTIES LINKER_LANGUAGE CXX)
    set(ikk_swift_deployment "${CMAKE_OSX_DEPLOYMENT_TARGET}")
    if (NOT ikk_swift_deployment OR ikk_swift_deployment VERSION_LESS 11.0)
        set(ikk_swift_deployment 11.0)
    endif()
    if (NOT CMAKE_GENERATOR STREQUAL "Xcode")
        set(ikk_swift_arch "${CMAKE_OSX_ARCHITECTURES}")
        if (NOT ikk_swift_arch)
            set(ikk_swift_arch "${CMAKE_SYSTEM_PROCESSOR}")
        endif()
        list(LENGTH ikk_swift_arch ikk_swift_arch_count)
        if (NOT ikk_swift_arch_count EQUAL 1)
            message(FATAL_ERROR "Use Xcode for a universal Swift build, or select one CMAKE_OSX_ARCHITECTURES value.")
        endif()
    endif()
    function(ikk_configure_swift_target target_name)
        if (CMAKE_GENERATOR STREQUAL "Xcode")
            set_target_properties(${target_name} PROPERTIES
                XCODE_ATTRIBUTE_MACOSX_DEPLOYMENT_TARGET "${ikk_swift_deployment}")
        else()
            target_compile_options(${target_name} PRIVATE
                "-target" "${ikk_swift_arch}-apple-macos${ikk_swift_deployment}")
        endif()
    endfunction()
    ikk_configure_swift_target(lib_translate)
    find_library(IKK_FOUNDATION_MODELS FoundationModels)
    if (IKK_FOUNDATION_MODELS)
        add_library(ikk_system_ai STATIC
            ${src_loc}/ikk/services/system_ai.swift)
        set_target_properties(ikk_system_ai PROPERTIES
            Swift_LANGUAGE_VERSION 6
            Swift_COMPILATION_MODE wholemodule)
        ikk_configure_swift_target(ikk_system_ai)
        target_link_options(ikk_system_ai INTERFACE
            "SHELL:-weak_framework FoundationModels")
        target_link_libraries(Telegram PRIVATE ikk_system_ai)
        target_compile_definitions(Telegram PRIVATE IKK_SYSTEM_AI)
    endif()
endif()

nice_target_sources(Telegram ${res_loc} PRIVATE qrc/ikk.qrc)
if (APPLE)
    nice_target_sources(Telegram ${res_loc} PRIVATE qrc/ikk_mac.qrc)
endif()

# Compiles the Icon Composer document so macOS renders the app icon itself.
function(ikk_mac_app_icon result)
    set(${result} FALSE PARENT_SCOPE)
    execute_process(
        COMMAND xcodebuild -version
        OUTPUT_VARIABLE xcode_version_output
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET)
    if (NOT xcode_version_output MATCHES "Xcode ([0-9]+)")
        message(STATUS "Ikk: Xcode not found, using the static app icon.")
        return()
    elseif (CMAKE_MATCH_1 LESS 26)
        message(STATUS "Ikk: Xcode ${CMAKE_MATCH_1} cannot compile .icon documents, using the static app icon.")
        return()
    endif()
    set(icon_source ${res_loc}/branding/Ikk.icon)
    set(icon_output ${CMAKE_CURRENT_BINARY_DIR}/ikk_icon)
    set(icon_deployment "${CMAKE_OSX_DEPLOYMENT_TARGET}")
    if (NOT icon_deployment)
        set(icon_deployment 11.0)
    endif()
    file(GLOB_RECURSE icon_inputs CONFIGURE_DEPENDS ${icon_source}/*)
    add_custom_command(
        OUTPUT ${icon_output}/Assets.car ${icon_output}/Ikk.icns
        COMMAND ${CMAKE_COMMAND} -E make_directory ${icon_output}
        COMMAND xcrun actool ${icon_source}
            --compile ${icon_output}
            --app-icon Ikk
            --platform macosx
            --minimum-deployment-target ${icon_deployment}
            --output-partial-info-plist ${icon_output}/partial.plist
            --output-format human-readable-text
        DEPENDS ${icon_inputs}
        VERBATIM)
    set_source_files_properties(
        ${icon_output}/Assets.car
        ${icon_output}/Ikk.icns
        PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    target_add_resource(Telegram
        ${icon_output}/Assets.car
        ${icon_output}/Ikk.icns)
    set(${result} TRUE PARENT_SCOPE)
endfunction()

if (DESKTOP_APP_TEST_APPS)
    add_executable(test_ikk)
    init_target(test_ikk "(tests)")

    nice_target_sources(test_ikk ${src_loc} PRIVATE
        ikk/tests/test_lang.cpp
        ikk/tests/test_options.cpp
        ikk/tests/test_spacing.cpp
        ikk/tests/test_services.cpp
        ikk/tests/test_chat_translation.cpp
        ikk/tests/test_auto_translate.cpp
        ikk/tests/test_filters.cpp
        ikk/tests/test_filter_scopes.cpp
        ikk/tests/test_links.cpp
        ikk/tests/test_inline_rules.cpp
        ikk/tests/test_privacy.cpp
        ikk/tests/test_p3_misc.cpp
        ikk/tests/test_local_lists.cpp
        ikk/tests/test_network.cpp
        ikk/tests/test_media.cpp
        ikk/tests/test_sync.cpp
        ikk/tests/test_export.cpp
        ikk/tests/test_markdown.cpp
        ikk/tests/test_cleanup.cpp
        ikk/tests/test_notifications.cpp
        ikk/tests/test_send_translation.cpp
        ikk/compose/spacing.cpp
        ikk/core/exchange.cpp
        ikk/core/regex.cpp
        ikk/export/range_model.cpp
        ikk/interface/main_menu_model.cpp
        ikk/menu/model.cpp
        ikk/messages/markdown.cpp
        ikk/services/auto_translate_model.cpp
        ikk/services/chat_translation_model.cpp
        ikk/services/context_model.cpp
        ikk/services/model.cpp
        ikk/services/presets.cpp
        ikk/services/summary_model.cpp
        ikk/services/send_translation_model.cpp
        ikk/services/transcription_queue.cpp
        ikk/filters/model.cpp
        ikk/links/model.cpp
        ikk/links/inline_rules.cpp
        ikk/links/webview.cpp
        ikk/privacy/protection_model.cpp
        ikk/chats/local_pins_model.cpp
        ikk/chats/cleanup_model.cpp
        ikk/media/local_faved_model.cpp
        ikk/network/model.cpp
        ikk/notifications/model.cpp
        ikk/media/url_template.cpp
        ikk/media/sticker_export_model.cpp
        ikk/snapshot/cloud_theme_model.cpp
        ikk/sync/model.cpp
    )

    target_include_directories(test_ikk PRIVATE
        ${src_loc}
        ${CMAKE_CURRENT_SOURCE_DIR}/lib_ui)

    target_link_libraries(test_ikk PRIVATE
        desktop-app::lib_base
        desktop-app::lib_crl
        desktop-app::external_qt
    )

    target_compile_definitions(test_ikk PRIVATE
        IKK_LANG_SOURCE_DIR="${res_loc}/langs"
    )

    set_target_properties(test_ikk PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/ikk-tests/$<CONFIG>"
    )

    add_dependencies(Telegram test_ikk)
endif()
