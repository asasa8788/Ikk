#pragma once

#include "ikk/core/options.h"

namespace Ikk::Privacy {

inline constexpr auto kDemoMode = Option<bool>{
	"ikk.demoMode", Scope::Device, false,
	Category::Privacy, "lng_ikk_demo_mode",
	static_cast<unsigned>(Flag::LocalOnly) };

[[nodiscard]] inline bool DemoMode() {
	return ForDevice().Get(kDemoMode);
}

inline constexpr auto kHideReadTime = Option<bool>{
	"ikk.hideReadTime", Scope::Device, false,
	Category::Privacy, "lng_ikk_hide_read_time" };
inline constexpr auto kHideSharePhonePrompt = Option<bool>{
	"ikk.hideSharePhonePrompt", Scope::Device, false,
	Category::Privacy, "lng_ikk_hide_share_phone_prompt" };
inline constexpr auto kDoNotSharePhone = Option<bool>{
	"ikk.doNotSharePhone", Scope::Device, false,
	Category::Privacy, "lng_ikk_do_not_share_phone" };
inline constexpr auto kForceCopy = Option<bool>{
	"ikk.forceCopy", Scope::Device, false,
	Category::Privacy, "lng_ikk_force_copy",
	static_cast<unsigned>(Flag::RefreshMessageView) };
inline constexpr auto kIgnoreContentRestrictions = Option<bool>{
	"ikk.ignoreContentRestrictions", Scope::Device, false,
	Category::Privacy, "lng_ikk_ignore_restrictions",
	static_cast<unsigned>(Flag::RefreshMessageView) };
inline constexpr auto kSkipSensitiveWarning = Option<bool>{
	"ikk.skipSensitiveWarning", Scope::Device, false,
	Category::Privacy, "lng_ikk_skip_sensitive_warning",
	static_cast<unsigned>(Flag::RefreshMessageView) };
inline constexpr auto kProfileIdFormat = Option<int>{
	"ikk.profileIdFormat", Scope::Device, 0,
	Category::Privacy, "lng_ikk_profile_id_format", 0,
	[](const int &value) { return value >= 0 && value <= 2; } };
inline constexpr auto kShowProfileDc = Option<bool>{
	"ikk.showProfileDc", Scope::Device, false,
	Category::Privacy, "lng_ikk_show_profile_dc" };
inline constexpr auto kShowRegistrationDate = Option<bool>{
	"ikk.showRegistrationDate", Scope::Device, false,
	Category::Privacy, "lng_ikk_show_registration_date" };

[[nodiscard]] constexpr bool ShowsRegistration(
		bool enabled,
		bool user,
		int month,
		int year) {
	return enabled && user && month >= 1 && month <= 12 && year > 0;
}

inline constexpr auto kHideProfileGifts = Option<bool>{
	"ikk.hideProfileGifts", Scope::Device, false,
	Category::Privacy, "lng_ikk_hide_profile_gifts" };
inline constexpr auto kHideCreateTodo = Option<bool>{
	"ikk.hideCreateTodo", Scope::Device, false,
	Category::Privacy, "lng_ikk_hide_create_todo" };

inline constexpr auto kNameOrder = Option<int>{
	"ikk.nameOrder", Scope::Device, 0,
	Category::Privacy, "lng_ikk_name_order",
	static_cast<unsigned>(Flag::RequiresRestart),
	[](const int &value) { return value >= 0 && value <= 2; } };
inline constexpr auto kPersianCalendar = Option<int>{
	"ikk.persianCalendar", Scope::Device, 0,
	Category::Privacy, "lng_ikk_persian_calendar",
	static_cast<unsigned>(Flag::RefreshMessageView),
	[](const int &value) { return value >= 0 && value <= 2; } };
inline constexpr auto kModerateDefaults = Option<int>{
	"ikk.moderateDefaults", Scope::Device, 0,
	Category::Privacy, "lng_ikk_moderate_defaults", 0,
	[](const int &value) { return value >= 0 && value <= 7; } };
inline constexpr auto kAdminShortcuts = Option<bool>{
	"ikk.adminShortcuts", Scope::Device, false,
	Category::Privacy, "lng_ikk_admin_shortcuts_option" };

inline void RegisterOptions(Registry &registry) {
	Expects(registry.Add(kDemoMode));
	Expects(registry.Add(kHideReadTime));
	Expects(registry.Add(kHideSharePhonePrompt));
	Expects(registry.Add(kProfileIdFormat));
	Expects(registry.Add(kShowProfileDc));
	Expects(registry.Add(kHideProfileGifts));
	Expects(registry.Add(kHideCreateTodo));
	Expects(registry.Add(kAdminShortcuts));
	Expects(registry.Add(kNameOrder));
	Expects(registry.Add(kPersianCalendar));
	Expects(registry.Add(kModerateDefaults));
	Expects(registry.Add(kDoNotSharePhone));
	Expects(registry.Add(kForceCopy));
	Expects(registry.Add(kIgnoreContentRestrictions));
	Expects(registry.Add(kSkipSensitiveWarning));
	Expects(registry.Add(kShowRegistrationDate));
}

} // namespace Ikk::Privacy
