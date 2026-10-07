#pragma once

#include "ui/text/text_entity.h"

#include <QtCore/QStringList>

namespace Ui {
class InputField;
} // namespace Ui

namespace Ikk::Compose {

[[nodiscard]] TextWithEntities AddChineseLatinSpacing(
	const TextWithEntities &text);
[[nodiscard]] TextWithEntities PrepareText(
	const TextWithEntities &text,
	bool editing);
[[nodiscard]] QStringList QuickReplies();
[[nodiscard]] bool SetQuickReplies(const QStringList &replies);
void InstallQuickReplies(not_null<Ui::InputField*> field);
[[nodiscard]] QString FormatMenuItemTitle(int index);
void InstallFieldHooks(not_null<Ui::InputField*> field);

} // namespace Ikk::Compose
