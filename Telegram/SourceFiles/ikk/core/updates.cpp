#include "ikk/core/updates.h"

#include "ikk/core/version.h"
#include "core/version.h"

namespace Ikk::Updates {

QString ReleasesUrl() {
	return u"https://github.com/ikk-dev/Ikk/releases"_q;
}

QString DownloadPrefix() {
	return ReleasesUrl() + u"/download"_q;
}

QString FeedUrl() {
	return DownloadPrefix() + u"/updates/ikk-updates.json"_q;
}

quint64 FeedVersion() {
	return quint64(AppVersion) * 1000 + UpdateRevision();
}

bool SkipTelegramFeed() {
	return true;
}

} // namespace Ikk::Updates
