#pragma once

class QString;
class QVariant;

namespace Ikk::Links {

[[nodiscard]] bool HandleExternalLink(
	const QString &url,
	const QVariant &context);

} // namespace Ikk::Links
