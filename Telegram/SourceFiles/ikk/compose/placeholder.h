#pragma once

#include "base/basic_types.h"
#include "rpl/rpl.h"

class PeerData;

namespace Ikk::Compose {

[[nodiscard]] rpl::producer<QString> InputPlaceholder(
	not_null<PeerData*> peer);

} // namespace Ikk::Compose
