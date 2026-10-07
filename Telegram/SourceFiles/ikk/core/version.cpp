#include "ikk/core/version.h"

#include "ikk_version_data.h"

namespace Ikk {

QString VersionString() {
	return QString::fromLatin1(kVersionStr);
}

bool VersionIsBeta() {
	return kVersionBeta;
}

quint32 UpdateRevision() {
	return kVersionRevision;
}

} // namespace Ikk
