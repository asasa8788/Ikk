#pragma once

struct InlineBotQuery;
struct TextWithTags;

namespace Main {
class Session;
} // namespace Main

namespace Ui {
class InputField;
} // namespace Ui

namespace Ikk::Links {

[[nodiscard]] bool AutoInlineBotEnabled();
[[nodiscard]] bool AutomaticInlineQuery(not_null<const Ui::InputField*> field);
void FillAutomaticInlineQuery(
	not_null<Main::Session*> session,
	const TextWithTags &text,
	InlineBotQuery &result);

} // namespace Ikk::Links
