#pragma once

#include "ikk/core/options.h"

#include <array>

namespace Ikk::Interface {

[[nodiscard]] bool ValidMainMenuBytes(const QByteArray &value);

inline constexpr auto kAppIconIds = std::array{
	u"block",
	u"block_black",
	u"block_blue",
	u"block_niello",
	u"block_purple",
	u"classic",
	u"colorful",
	u"cyan",
	u"black",
};
[[nodiscard]] inline bool ValidAppIcon(const QString &value) {
	if (value.isEmpty()) {
		return true;
	}
	for (const auto id : kAppIconIds) {
		if (value == QStringView(id)) {
			return true;
		}
	}
	return false;
}

inline constexpr auto kRestart = static_cast<unsigned>(Flag::RequiresRestart);
inline constexpr auto kBubbleRoundness = Option<int>{
	"ikk.bubbleRoundness", Scope::Device, 0,
	Category::Interface, "lng_ikk_bubble_roundness", kRestart,
	[](const int &value) { return !value || (value >= 10 && value <= 100); } };
inline constexpr auto kAvatarRoundness = Option<int>{
	"ikk.avatarRoundness", Scope::Device, 0,
	Category::Interface, "lng_ikk_avatar_roundness", kRestart,
	[](const int &value) { return !value || (value >= 10 && value <= 100); } };
inline constexpr auto kUniformAvatarShapes = Option<bool>{
	"ikk.uniformAvatarShapes", Scope::Device, false,
	Category::Interface, "lng_ikk_uniform_avatar_shapes", kRestart };
inline constexpr auto kTextMessageWidth = Option<int>{
	"ikk.textMessageWidth", Scope::Device, 0,
	Category::Interface, "lng_ikk_text_message_width",
	static_cast<unsigned>(Flag::RefreshMessageView),
	[](const int &value) { return !value || (value >= 50 && value <= 400); } };
inline constexpr auto kWideChannelPosts = Option<bool>{
	"ikk.wideChannelPosts", Scope::Device, false,
	Category::Interface, "lng_ikk_wide_channel_posts",
	static_cast<unsigned>(Flag::RefreshMessageView) };
inline constexpr auto kHideBubbleTail = Option<bool>{
	"ikk.hideBubbleTail", Scope::Device, false,
	Category::Interface, "lng_ikk_hide_bubble_tail",
	static_cast<unsigned>(Flag::RefreshMessageView) };
inline constexpr auto kThemeReplyColors = Option<bool>{
	"ikk.themeReplyColors", Scope::Device, false,
	Category::Interface, "lng_ikk_theme_reply_colors",
	static_cast<unsigned>(Flag::RefreshMessageView) };
inline constexpr auto kHideReplyThumbnail = Option<bool>{
	"ikk.hideReplyThumbnail", Scope::Device, false,
	Category::Interface, "lng_ikk_hide_reply_thumbnail",
	static_cast<unsigned>(Flag::RefreshMessageView) };
inline constexpr auto kIgnoreChatTheme = Option<bool>{
	"ikk.ignoreChatTheme", Scope::Device, false,
	Category::Interface, "lng_ikk_ignore_chat_theme" };
inline constexpr auto kIgnorePrivateChatTheme = Option<bool>{
	"ikk.ignorePrivateChatTheme", Scope::Device, false,
	Category::Interface, "lng_ikk_ignore_private_chat_theme" };
inline constexpr auto kIgnoreChannelChatTheme = Option<bool>{
	"ikk.ignoreChannelChatTheme", Scope::Device, false,
	Category::Interface, "lng_ikk_ignore_channel_chat_theme" };
inline constexpr auto kAccountNameInTitle = Option<bool>{
	"ikk.accountNameInTitle", Scope::Device, false,
	Category::Interface, "lng_ikk_account_name_in_title" };
inline constexpr auto kAlwaysSeasonal = Option<bool>{
	"ikk.alwaysSeasonalDecorations", Scope::Device, false,
	Category::Interface, "lng_ikk_always_seasonal", kRestart };
inline const auto kMainMenuConfig = Option<QByteArray>{
	"ikk.mainMenu", Scope::Device, QByteArray(),
	Category::Interface, "lng_ikk_main_menu", 0,
	ValidMainMenuBytes };
inline const auto kAppIcon = Option<QString>{
	"ikk.appIcon", Scope::Device, QString(),
	Category::Interface, "lng_ikk_app_icon",
	static_cast<unsigned>(Flag::LocalOnly), ValidAppIcon };
inline constexpr auto kHideAppIconBadge = Option<bool>{
	"ikk.hideAppIconBadge", Scope::Device, false,
	Category::Interface, "lng_ikk_hide_app_icon_badge" };
inline constexpr auto kNotificationDelay = Option<int>{
	"ikk.notificationDelay", Scope::Device, 0,
	Category::Interface, "lng_ikk_notification_delay", 0,
	[](const int &value) { return value == 0 || value == 500
		|| value == 1000 || value == 2000 || value == 5000
		|| value == 10000 || value == 30000 || value == 60000; } };
inline constexpr auto kOtherDeviceNotificationDelay = Option<int>{
	"ikk.otherDeviceNotificationDelay", Scope::Device, 0,
	Category::Interface, "lng_ikk_other_device_notification_delay", 0,
	kNotificationDelay.validate };
inline constexpr auto kHalfwidthUiPunctuation = Option<bool>{
	"ikk.halfwidthUiPunctuation", Scope::Device, false,
	Category::Interface, "lng_ikk_halfwidth_ui_punctuation", kRestart };

inline void RegisterOptions(Registry &registry) {
	Expects(registry.Add(kBubbleRoundness));
	Expects(registry.Add(kAvatarRoundness));
	Expects(registry.Add(kUniformAvatarShapes));
	Expects(registry.Add(kTextMessageWidth));
	Expects(registry.Add(kWideChannelPosts));
	Expects(registry.Add(kHideBubbleTail));
	Expects(registry.Add(kThemeReplyColors));
	Expects(registry.Add(kHideReplyThumbnail));
	Expects(registry.Add(kIgnoreChatTheme));
	Expects(registry.Add(kIgnorePrivateChatTheme));
	Expects(registry.Add(kIgnoreChannelChatTheme));
	Expects(registry.Add(kAccountNameInTitle));
	Expects(registry.Add(kAlwaysSeasonal));
	Expects(registry.Add(kMainMenuConfig));
	Expects(registry.Add(kAppIcon));
	Expects(registry.Add(kHideAppIconBadge));
	Expects(registry.Add(kNotificationDelay));
	Expects(registry.Add(kOtherDeviceNotificationDelay));
	Expects(registry.Add(kHalfwidthUiPunctuation));
}

} // namespace Ikk::Interface
