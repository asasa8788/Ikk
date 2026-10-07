#pragma once

#include <QtCore/QString>

namespace Lang {
class Instance;
} // namespace Lang

namespace Ikk {

[[nodiscard]] QString LocalizedValue(const Lang::Instance &instance, ushort key);

} // namespace Ikk
