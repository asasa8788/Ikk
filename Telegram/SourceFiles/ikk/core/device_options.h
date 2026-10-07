#pragma once

#include "ikk/core/options.h"

namespace Ikk::details {

[[nodiscard]] inline Options &SharedDeviceOptions(RawPrefs &prefs) {
	static auto options = Options(prefs);
	return options;
}

} // namespace Ikk::details
