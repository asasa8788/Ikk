# Ikk Desktop built from source: the telegram-desktop package of nixpkgs
# with the Ikk source. A build from source cannot hide what it compiles in,
# so the caller passes Telegram API credentials of their own, see
# https://core.telegram.org/api/obtaining_api_id. package-bin.nix installs the
# released binary, which carries the credentials of the project.
{
  lib,
  stdenv,
  telegram-desktop,
  pango,
  tlottie,
  src,
  version,
  apiId,
  apiHash,
}:

telegram-desktop.override {
  pname = "ikk-desktop";
  unwrapped = telegram-desktop.unwrapped.overrideAttrs (
    finalAttrs: previousAttrs: {
      pname = "ikk-desktop-unwrapped";
      inherit version src;

      # nixpkgs adds these two only to the package named telegram-desktop-unwrapped.
      buildInputs =
        previousAttrs.buildInputs ++ [ tlottie ] ++ lib.optionals stdenv.hostPlatform.isLinux [ pango ];

      cmakeFlags = lib.filter (flag: !lib.hasInfix "TDESKTOP_API_" flag) previousAttrs.cmakeFlags ++ [
        (lib.cmakeFeature "TDESKTOP_API_ID" (toString apiId))
        (lib.cmakeFeature "TDESKTOP_API_HASH" apiHash)
      ];

      passthru = removeAttrs previousAttrs.passthru [ "updateScript" ];

      meta = previousAttrs.meta // {
        mainProgram = "Ikk";
        description = "Independent Telegram client based on Telegram Desktop";
        longDescription = ''
          Ikk Desktop is Telegram Desktop with additional interface,
          privacy and message options. Its automatic updater is not built:
          the package is updated through Nix.
        '';
        homepage = "https://github.com/ikk-dev/Ikk";
        changelog = "https://github.com/ikk-dev/Ikk/releases/tag/v${finalAttrs.version}";
        maintainers = [ ];
      };
    }
  );
}
