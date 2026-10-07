#pragma once

#include "ikk/core/options.h"

#include <QtCore/QJsonArray>

namespace Ikk::Compose {

inline constexpr auto kRefreshButtons = static_cast<unsigned>(
	Flag::RefreshComposeButtons);

inline constexpr auto kHideAttachButton = Option<bool>{
	"ikk.hideAttachButton", Scope::Device, false,
	Category::Compose, "lng_ikk_hide_attach_button", kRefreshButtons };
inline constexpr auto kHideEmojiButton = Option<bool>{
	"ikk.hideEmojiButton", Scope::Device, false,
	Category::Compose, "lng_ikk_hide_emoji_button", kRefreshButtons };
inline constexpr auto kHideRecordingButton = Option<bool>{
	"ikk.hideRecordingButton", Scope::Device, false,
	Category::Compose, "lng_ikk_hide_recording_button", kRefreshButtons };
inline constexpr auto kHideBotCommandButton = Option<bool>{
	"ikk.hideBotCommandButton", Scope::Device, false,
	Category::Compose, "lng_ikk_hide_bot_command_button", kRefreshButtons };
inline constexpr auto kHideBotMenu = Option<bool>{
	"ikk.hideBotMenu", Scope::Device, false,
	Category::Compose, "lng_ikk_hide_bot_menu", kRefreshButtons };
inline constexpr auto kHideAutoDeleteButton = Option<bool>{
	"ikk.hideAutoDeleteButton", Scope::Device, false,
	Category::Compose, "lng_ikk_hide_auto_delete_button", kRefreshButtons };
inline constexpr auto kHideGiftButton = Option<bool>{
	"ikk.hideGiftButton", Scope::Device, false,
	Category::Compose, "lng_ikk_hide_gift_button", kRefreshButtons };
inline constexpr auto kHideAiButton = Option<bool>{
	"ikk.hideAiButton", Scope::Device, false,
	Category::Compose, "lng_ikk_hide_ai_button", kRefreshButtons };
inline constexpr auto kHideSendAsButton = Option<bool>{
	"ikk.hideSendAsButton", Scope::Device, false,
	Category::Compose, "lng_ikk_hide_send_as_button", kRefreshButtons };
inline constexpr auto kHideStarsReactionButton = Option<bool>{
	"ikk.hideStarsReactionButton", Scope::Device, false,
	Category::Compose, "lng_ikk_hide_stars_reaction_button", kRefreshButtons };
inline constexpr auto kHideChannelMuteButton = Option<bool>{
	"ikk.hideChannelMuteButton", Scope::Device, false,
	Category::Compose, "lng_ikk_hide_channel_mute_button", kRefreshButtons };
inline constexpr auto kChannelDiscussButton = Option<bool>{
	"ikk.channelDiscussButton", Scope::Device, false,
	Category::Compose, "lng_ikk_channel_discuss_button", kRefreshButtons };
inline constexpr auto kDisableEmojiHover = Option<bool>{
	"ikk.disableEmojiHover", Scope::Device, false,
	Category::Compose, "lng_ikk_disable_emoji_hover" };
inline constexpr auto kDisableAttachHover = Option<bool>{
	"ikk.disableAttachHover", Scope::Device, false,
	Category::Compose, "lng_ikk_disable_attach_hover" };
inline constexpr auto kBotCommandsToDraft = Option<bool>{
	"ikk.botCommandsToDraft", Scope::Device, false,
	Category::Compose, "lng_ikk_bot_commands_to_draft" };
inline constexpr auto kInputPlaceholderMode = Option<int>{
	"ikk.inputPlaceholderMode", Scope::Device, 0,
	Category::Compose, "lng_ikk_input_placeholder", 0,
	[](const int &value) { return value >= 0 && value <= 2; } };
inline constexpr auto kFormatToolbar = Option<bool>{
	"ikk.formatToolbar", Scope::Device, false,
	Category::Compose, "lng_ikk_format_toolbar" };
inline constexpr auto kFormatMenuItemCount = 9;
inline constexpr auto kHiddenFormatItems = Option<int>{
	"ikk.hiddenFormatItems", Scope::Device, 0,
	Category::Compose, "lng_ikk_format_menu_items", 0,
	[](const int &value) {
		return value >= 0 && value < (1 << kFormatMenuItemCount);
	} };
inline constexpr auto kInputChinese = Option<int>{
	"ikk.inputChinese", Scope::Device, 0,
	Category::Compose, "lng_ikk_input_chinese", 0,
	[](const int &value) { return value >= 0 && value <= 2; } };
inline constexpr auto kDisableAutoMarkdown = Option<bool>{
	"ikk.disableAutoMarkdown", Scope::Device, false,
	Category::Compose, "lng_ikk_disable_auto_markdown" };
inline constexpr auto kDisableLinkPreview = Option<bool>{
	"ikk.disableLinkPreview", Scope::Device, false,
	Category::Compose, "lng_ikk_disable_link_preview" };
inline constexpr auto kSpaceOnSend = Option<bool>{
	"ikk.spaceOnSend", Scope::Device, false,
	Category::Compose, "lng_ikk_space_on_send" };
inline constexpr auto kSpaceOnEdit = Option<bool>{
	"ikk.spaceOnEdit", Scope::Device, false,
	Category::Compose, "lng_ikk_space_on_edit" };
inline const auto kDefaultCodeLanguage = Option<QString>{
	"ikk.defaultCodeLanguage", Scope::Device, QString(),
	Category::Compose, "lng_ikk_default_code_language", 0,
	[](const QString &value) {
		if (value.size() > 32) return false;
		for (const auto &ch : value) {
			const auto code = ch.unicode();
			if (!((code >= 'a' && code <= 'z')
				|| (code >= 'A' && code <= 'Z')
				|| (code >= '0' && code <= '9')
				|| code == '+' || code == '-')) {
				return false;
			}
		}
		return true;
	} };
inline const auto kQuickReplies = Option<QByteArray>{
	"ikk.quickReplies", Scope::Device,
	QByteArray("{\"version\":1,\"replies\":[\"\",\"\"]}"),
	Category::Compose, "lng_ikk_quick_replies", 0,
	[](const QByteArray &value) {
		const auto json = QJsonDocument::fromJson(value);
		if (!json.isObject()) return false;
		const auto object = json.object();
		const auto replies = object.value(QString::fromLatin1("replies")).toArray();
		return object.size() == 2
			&& object.value(QString::fromLatin1("version")) == 1
			&& replies.size() == 2
			&& replies[0].isString()
			&& replies[1].isString();
	} };
inline constexpr auto kConfirmSticker = Option<bool>{
	"ikk.confirmSticker", Scope::Device, false,
	Category::Compose, "lng_ikk_confirm_sticker" };
inline constexpr auto kConfirmGif = Option<bool>{
	"ikk.confirmGif", Scope::Device, false,
	Category::Compose, "lng_ikk_confirm_gif" };
inline constexpr auto kPreviewVoice = Option<bool>{
	"ikk.previewVoice", Scope::Device, false,
	Category::Compose, "lng_ikk_preview_voice" };
inline constexpr auto kPreviewRoundVideo = Option<bool>{
	"ikk.previewRoundVideo", Scope::Device, false,
	Category::Compose, "lng_ikk_preview_round_video" };
inline constexpr auto kConfirmPrivateCall = Option<bool>{
	"ikk.confirmPrivateCall", Scope::Device, false,
	Category::Compose, "lng_ikk_confirm_private_call" };
inline constexpr auto kForwardBeforeComment = Option<bool>{
	"ikk.forwardBeforeComment", Scope::Device, false,
	Category::Compose, "lng_ikk_forward_before_comment" };

inline void RegisterOptions(Registry &registry) {
	Expects(registry.Add(kHideAttachButton));
	Expects(registry.Add(kHideEmojiButton));
	Expects(registry.Add(kHideRecordingButton));
	Expects(registry.Add(kHideBotCommandButton));
	Expects(registry.Add(kHideBotMenu));
	Expects(registry.Add(kHideAutoDeleteButton));
	Expects(registry.Add(kHideGiftButton));
	Expects(registry.Add(kHideAiButton));
	Expects(registry.Add(kHideSendAsButton));
	Expects(registry.Add(kHideStarsReactionButton));
	Expects(registry.Add(kHideChannelMuteButton));
	Expects(registry.Add(kChannelDiscussButton));
	Expects(registry.Add(kDisableEmojiHover));
	Expects(registry.Add(kDisableAttachHover));
	Expects(registry.Add(kBotCommandsToDraft));
	Expects(registry.Add(kInputPlaceholderMode));
	Expects(registry.Add(kFormatToolbar));
	Expects(registry.Add(kHiddenFormatItems));
	Expects(registry.Add(kInputChinese));
	Expects(registry.Add(kDisableAutoMarkdown));
	Expects(registry.Add(kDisableLinkPreview));
	Expects(registry.Add(kSpaceOnSend));
	Expects(registry.Add(kSpaceOnEdit));
	Expects(registry.Add(kDefaultCodeLanguage));
	Expects(registry.Add(kQuickReplies));
	Expects(registry.Add(kConfirmSticker));
	Expects(registry.Add(kConfirmGif));
	Expects(registry.Add(kPreviewVoice));
	Expects(registry.Add(kPreviewRoundVideo));
	Expects(registry.Add(kConfirmPrivateCall));
	Expects(registry.Add(kForwardBeforeComment));
}

} // namespace Ikk::Compose
