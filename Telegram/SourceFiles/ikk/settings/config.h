#pragma once

#include "ikk/core/exchange.h"
#include "settings/settings_common.h"

namespace Window {
class SessionController;
} // namespace Window

namespace Ikk {

[[nodiscard]] Settings::Type ConfigId();
void ShowImport(
	not_null<Window::SessionController*> controller,
	const QByteArray &bytes,
	ExchangeTarget target = ExchangeTarget::File,
	Fn<void()> applied = nullptr);

} // namespace Ikk
