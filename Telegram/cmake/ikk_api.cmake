# Ikk Desktop: api_id and api_hash come from the environment
# (IKK_API_ID, IKK_API_HASH) or from the uncommitted file
# Telegram/build/api_credentials.local.cmake. Both are ignored with
# -D TDESKTOP_API_TEST=ON; explicit -D TDESKTOP_API_ID / TDESKTOP_API_HASH
# values are used only while neither source is set.

set(ikk_api_local ${CMAKE_CURRENT_SOURCE_DIR}/build/api_credentials.local.cmake)
if (EXISTS ${ikk_api_local})
    include(${ikk_api_local})
endif()
if (DEFINED ENV{IKK_API_ID} AND NOT "$ENV{IKK_API_ID}" STREQUAL "")
    set(IKK_API_ID "$ENV{IKK_API_ID}")
endif()
if (DEFINED ENV{IKK_API_HASH} AND NOT "$ENV{IKK_API_HASH}" STREQUAL "")
    set(IKK_API_HASH "$ENV{IKK_API_HASH}")
endif()

if (NOT TDESKTOP_API_TEST
    AND (NOT TDESKTOP_API_ID OR TDESKTOP_API_ID STREQUAL "0" OR IKK_API_FROM_LOCAL)
    AND DEFINED IKK_API_ID)
    if (NOT IKK_API_ID MATCHES "^[1-9][0-9]*$")
        message(FATAL_ERROR "IKK_API_ID must be a positive integer.")
    endif()
    string(LENGTH "${IKK_API_HASH}" ikk_api_hash_length)
    if (NOT IKK_API_HASH MATCHES "^[0-9a-f]+$"
        OR NOT ikk_api_hash_length EQUAL 32)
        message(FATAL_ERROR "IKK_API_HASH must be 32 lowercase hex digits.")
    endif()
    set(TDESKTOP_API_ID ${IKK_API_ID} CACHE STRING "Provide 'api_id' for the Telegram API access." FORCE)
    set(TDESKTOP_API_HASH ${IKK_API_HASH} CACHE STRING "Provide 'api_hash' for the Telegram API access." FORCE)
    set(IKK_API_FROM_LOCAL ON CACHE INTERNAL "api_id and api_hash were taken from IKK_API_*.")
    message(STATUS "Ikk: using api_id ${IKK_API_ID} from the environment or local credentials file.")
endif()
