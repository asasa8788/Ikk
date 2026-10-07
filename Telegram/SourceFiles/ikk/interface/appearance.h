#pragma once

#include <rpl/producer.h>

class PeerData;

namespace Ikk::Interface {

[[nodiscard]] rpl::producer<bool> IgnoreChatThemeValue(
	not_null<PeerData*> peer);
[[nodiscard]] bool AccountNameInTitle();
[[nodiscard]] bool AlwaysSeasonal();

} // namespace Ikk::Interface
