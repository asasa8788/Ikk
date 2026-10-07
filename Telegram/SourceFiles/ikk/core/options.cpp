#include "ikk/core/options.h"
#include "ikk/core/device_options.h"
#include "ikk/interface/options.h"
#include "ikk/chats/options.h"
#include "ikk/chats/local_pins_model.h"
#include "ikk/compose/options.h"
#include "ikk/media/options.h"
#include "ikk/media/backend_options.h"
#include "ikk/media/local_faved_model.h"
#include "ikk/menu/model.h"
#include "ikk/privacy/options.h"
#include "ikk/privacy/alias.h"
#include "ikk/messages/options.h"
#include "ikk/services/auto_translate_model.h"
#include "ikk/services/model.h"
#include "ikk/services/send_translation_model.h"
#include "ikk/filters/model.h"
#include "ikk/links/model.h"
#include "ikk/links/options.h"
#include "ikk/links/inline_rules.h"
#include "ikk/links/webview.h"
#include "ikk/notifications/model.h"
#include "ikk/network/options.h"
#include "ikk/snapshot/snapshot.h"
#include "ikk/sync/model.h"
#include "ikk/core/diagnostics.h"

#include "core/application.h"
#include "core/core_settings.h"
#include "main/main_session.h"
#include "storage/storage_account.h"

#include <map>
#include <memory>

namespace Storage {

template <>
std::optional<QByteArray> Account::readPrefImpl<QByteArray>(
		std::string_view key) {
	return readPrefGeneric(key);
}

template <>
void Account::writePrefImpl<QByteArray>(
		std::string_view key,
		QByteArray value) {
	writePrefGeneric(key, value);
}

} // namespace Storage

namespace Ikk {

Options &ForDevice() {
	static auto prefs = DevicePrefs(Core::App().settings());
	return details::SharedDeviceOptions(prefs);
}

DevicePrefs::DevicePrefs(Core::Settings &settings) : _settings(settings) { }

QByteArray DevicePrefs::read(std::string_view key) {
	return _settings.readPref<QByteArray>(key);
}

void DevicePrefs::write(std::string_view key, const QByteArray &value) {
	_settings.writePref<QByteArray>(key, value);
}

void DevicePrefs::clear(std::string_view key) {
	_settings.clearPref(key);
}

AccountPrefs::AccountPrefs(Storage::Account &account) : _account(account) { }

QByteArray AccountPrefs::read(std::string_view key) {
	return _account.readPref<QByteArray>(key);
}

void AccountPrefs::write(std::string_view key, const QByteArray &value) {
	_account.writePref<QByteArray>(key, value);
}

void AccountPrefs::clear(std::string_view key) {
	_account.clearPref(key);
}

Options &ForAccount(gsl::not_null<Main::Session*> session) {
	struct State {
		explicit State(gsl::not_null<Main::Session*> session)
		: guard(base::make_weak(session))
		, prefs(session->local())
		, options(prefs, Scope::Account) { }
		base::weak_ptr<Main::Session> guard;
		AccountPrefs prefs;
		Options options;
	};
	// Called while the session is still being constructed, so its lifetime
	// can't own the state: the weak pointer tells when the session is gone.
	static auto states = std::map<Main::Session*, std::unique_ptr<State>>();
	const auto found = states.find(session);
	if (found != states.end() && found->second->guard) {
		return found->second->options;
	}
	std::erase_if(states, [](const auto &entry) {
		return !entry.second->guard;
	});
	const auto inserted = states.emplace(
		session, std::make_unique<State>(session)).first;
	return inserted->second->options;
}

const Registry &RegisteredOptions() {
	static const auto registry = [] {
		auto result = Registry();
		Chats::RegisterOptions(result);
		Chats::RegisterLocalPinOptions(result);
		Interface::RegisterOptions(result);
		Compose::RegisterOptions(result);
		Media::RegisterOptions(result);
		Media::RegisterLocalFavedOptions(result);
		Media::RegisterBackendOptions(result);
		Menu::RegisterOptions(result);
		Privacy::RegisterOptions(result);
		Privacy::RegisterAliasOptions(result);
		Messages::RegisterOptions(result);
		Filters::RegisterOptions(result);
		Links::RegisterOptions(result);
		Links::RegisterBehaviorOptions(result);
		Links::RegisterInlineOptions(result);
		Links::RegisterWebviewOptions(result);
		Network::RegisterOptions(result);
		Notifications::RegisterOptions(result);
		Snapshot::RegisterOptions(result);
		RegisterServiceOptions(result);
		AutoTranslate::RegisterOptions(result);
		SendTranslation::RegisterOptions(result);
		RegisterDiagnosticsOptions(result);
		Sync::RegisterOptions(result);
		return result;
	}();
	return registry;
}

} // namespace Ikk
