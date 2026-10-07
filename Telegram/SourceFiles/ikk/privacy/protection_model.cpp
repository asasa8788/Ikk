#include "ikk/privacy/protection.h"

namespace Ikk::Privacy {

bool CopyAllowed(bool force, bool allowsForwarding) {
	return force || allowsForwarding;
}

bool CopyForbidden(bool force, bool forbidsForward) {
	return !force && forbidsForward;
}

bool SensitiveWarningSkipped(
		bool enabled,
		bool loaded,
		bool canChange,
		bool ageVerifyNeeded) {
	return enabled && loaded && canChange && !ageVerifyNeeded;
}

} // namespace Ikk::Privacy
