#pragma once

#include <crl/crl_time.h>
#include <gsl/pointers>

#include <optional>

class HistoryItem;

namespace Ikk::Interface {

[[nodiscard]] crl::time NotificationDelay(
	crl::time upstream,
	crl::time minimum,
	bool otherDeviceActive);
[[nodiscard]] int AppIconBadge(int unread);
// True shows the notification, false skips it, nothing leaves the choice.
[[nodiscard]] std::optional<bool> ReviewNotification(
	gsl::not_null<HistoryItem*> item,
	bool message);

} // namespace Ikk::Interface
