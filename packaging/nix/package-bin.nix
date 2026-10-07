# Ikk Desktop as it is released: the binary that the release workflow
# builds, with the Telegram API credentials of the project. x86_64-linux only.
#
# The binary runs in an FHS environment and is left untouched: patchelf
# breaks it, even when it only changes the interpreter path.
{
  lib,
  stdenvNoCC,
  fetchurl,
  buildFHSEnv,
  version,
  hash,
  # The released Linux archive; callPackage would fill an argument named src.
  archive ? fetchurl {
    url = "https://github.com/ikk-dev/Ikk/releases/download/v${version}/Ikk-${version}-linux-x86_64.tar.xz";
    inherit hash;
  },
}:

let
  unwrapped = stdenvNoCC.mkDerivation {
    pname = "ikk-desktop-bin-unwrapped";
    inherit version;
    src = archive;

    dontConfigure = true;
    dontBuild = true;
    dontFixup = true;

    installPhase = ''
      runHook preInstall

      install -Dm755 Ikk $out/bin/Ikk
      cp -r share $out/share

      # Nix updates this copy, so the built-in updater is switched off.
      mkdir $out/bin/externalupdater.d
      echo $out/bin/Ikk > $out/bin/externalupdater.d/nix.conf

      runHook postInstall
    '';
  };
in
buildFHSEnv {
  pname = "ikk-desktop-bin";
  inherit version;
  executableName = "Ikk";
  runScript = "${unwrapped}/bin/Ikk";

  # What the binary links to, and what it loads at run time; without gtk3
  # it aborts on start.
  targetPkgs =
    pkgs: with pkgs; [
      alsa-lib
      cairo
      dbus
      fontconfig
      freetype
      geoclue2
      glib
      gtk3
      libGL
      libpulseaudio
      libva
      libx11
      libxcb
      pango
      pipewire
      wayland
      webkitgtk_4_1
      xdg-utils
    ];

  extraInstallCommands = ''
    cp -r ${unwrapped}/share $out/share
    chmod -R u+w $out/share
    substituteInPlace $out/share/dbus-1/services/*.service \
      --replace-fail /usr/bin/Ikk $out/bin/Ikk
  '';

  meta = {
    description = "Independent Telegram client based on Telegram Desktop";
    homepage = "https://github.com/ikk-dev/Ikk";
    changelog = "https://github.com/ikk-dev/Ikk/releases/tag/v${version}";
    license = lib.licenses.gpl3Only;
    sourceProvenance = [ lib.sourceTypes.binaryNativeCode ];
    platforms = [ "x86_64-linux" ];
    mainProgram = "Ikk";
  };
}
