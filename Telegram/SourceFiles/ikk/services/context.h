#pragma once

#include <QtCore/QStringList>

class HistoryItem;

namespace Ikk {

[[nodiscard]] QStringList CollectTranslationContext(
	not_null<HistoryItem*> item);

} // namespace Ikk
