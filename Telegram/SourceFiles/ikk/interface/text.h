#pragma once

#include <QtCore/QString>

namespace Ikk::Interface {

[[nodiscard]] QString HalfwidthPunctuation(QString value);
[[nodiscard]] QString UiText(QString value);
void StartUiText();

} // namespace Ikk::Interface
