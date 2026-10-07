# Ikk Desktop: a release is <upstream version>.<revision>. The revision and
# the channel of the latest release are kept in build/ikk_version, so the
# upstream version files stay as upstream wrote them.

set(ikk_version_file ${CMAKE_CURRENT_SOURCE_DIR}/build/ikk_version)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${ikk_version_file})

set(ikk_revision "")
set(ikk_channel "")
file(STRINGS ${ikk_version_file} ikk_version_lines)
foreach (line ${ikk_version_lines})
    if (line MATCHES "^IkkRevision +([1-9][0-9]?[0-9]?)$" AND ikk_revision STREQUAL "")
        set(ikk_revision ${CMAKE_MATCH_1})
    elseif (line MATCHES "^IkkChannel +(stable|beta)$" AND ikk_channel STREQUAL "")
        set(ikk_channel ${CMAKE_MATCH_1})
    else()
        message(FATAL_ERROR "Bad line in ${ikk_version_file}: ${line}")
    endif()
endforeach()
if (ikk_revision STREQUAL "" OR ikk_channel STREQUAL "")
    message(FATAL_ERROR "${ikk_version_file} must set IkkRevision and IkkChannel.")
endif()

set(ikk_version_string ${desktop_app_version_string}.${ikk_revision})
if (ikk_channel STREQUAL "beta")
    set(ikk_version_beta true)
else()
    set(ikk_version_beta false)
endif()
message(STATUS "Ikk: version ${ikk_version_string} (${ikk_channel}).")

# A generated header keeps a revision bump from recompiling the whole target.
set(ikk_version_gen ${CMAKE_CURRENT_BINARY_DIR}/gen)
file(CONFIGURE
    OUTPUT ${ikk_version_gen}/ikk_version_data.h
    CONTENT "// Generated from Telegram/build/ikk_version.
#pragma once

namespace Ikk {

inline constexpr auto kVersionStr = \"@ikk_version_string@\";
inline constexpr auto kVersionRevision = @ikk_revision@;
inline constexpr auto kVersionBeta = @ikk_version_beta@;

} // namespace Ikk
"
    @ONLY)
target_include_directories(Telegram PRIVATE ${ikk_version_gen})
