#pragma once

class DocumentData;
class DownloadLocation;

namespace Ikk::Media {

[[nodiscard]] DownloadLocation CoverLocation(
	not_null<DocumentData*> document,
	DownloadLocation upstream);

} // namespace Ikk::Media
