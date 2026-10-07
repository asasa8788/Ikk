#pragma once

#include "lang/translate_provider.h"

class History;

namespace Ikk {

[[nodiscard]] std::unique_ptr<Ui::TranslateProvider> CreateChatTranslateProvider(
	not_null<History*> history);
void CancelChatTranslation(Ui::TranslateProvider *provider);
[[nodiscard]] bool ChatTranslationServiceActive();

} // namespace Ikk
