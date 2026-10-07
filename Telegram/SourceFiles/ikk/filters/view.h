#pragma once

#include "ikk/filters/model.h"

class HistoryItem;

namespace Ikk::Filters {

[[nodiscard]] Result Project(
	HistoryItem *item,
	const TextWithEntities &source);
[[nodiscard]] bool Hidden(HistoryItem *item);
[[nodiscard]] TextWithEntities DisplayText(const Result &result);

} // namespace Ikk::Filters
