with import <nixpkgs> {};

stdenv.mkDerivation rec {
  name = "chip8-${version}";
  version = "0.0.1";
  src = if lib.inNixShell then null else ./.;
  enableParallelBuilding = true;
  env = buildEnv { name = name; paths = buildInputs; };
  buildInputs = [
    boost168
    cloc
    SDL2
  ];

  nativeBuildInputs = [
    cmake
  ];
}
