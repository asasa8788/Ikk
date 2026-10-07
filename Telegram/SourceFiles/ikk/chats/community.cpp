#include "ikk/chats/community.h"

#include "ikk/chats/options.h"

namespace Ikk::Chats {

bool CommunityGroupingDisabled() {
	// Read once: chat list membership is built from it at startup.
	static const auto result = ForDevice().Get(kDisableCommunityGrouping);
	return result;
}

} // namespace Ikk::Chats
