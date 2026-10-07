#pragma once

#include <QtCore/QString>

namespace Ikk {

// The upstream version followed by the Ikk revision, like "7.2.10.3".
[[nodiscard]] QString VersionString();

[[nodiscard]] bool VersionIsBeta();

// The Ikk revision, the low half of the 64-bit update version.
[[nodiscard]] quint32 UpdateRevision();

} // namespace Ikk
