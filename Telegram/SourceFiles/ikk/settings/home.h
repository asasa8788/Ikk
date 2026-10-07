#pragma once

#include "settings/settings_type.h"

namespace Settings::Builder {
class SectionBuilder;
} // namespace Settings::Builder

namespace Ikk {

[[nodiscard]] Settings::Type HomeId();
void AddSettingsEntry(Settings::Builder::SectionBuilder &builder);

} // namespace Ikk
