# flake.nix - Hermetic Bazel build with flazel
#
# Usage:
#   nix build              # Build static binary (default)
#   nix build .#dynamic    # Build dynamic binary
#   nix develop            # Enter dev shell (dynamic, faster iteration)
#   nix fmt                # Format all files
#
# Test ROMs are fetched as flake inputs (chip8Archive, chip8-reference).
#
{
  description = "Chip8 emulator and disassembler";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    treefmt-nix.url = "github:numtide/treefmt-nix";
    flazel.url = "github:fabianbuettner/flazel";
    flazel.inputs.nixpkgs.follows = "nixpkgs";
    flazel.inputs.flake-utils.follows = "flake-utils";
    flazel.inputs.treefmt-nix.follows = "treefmt-nix";

    # ==========================================================================
    # Git submodules as flake inputs (pinned to specific commits)
    # ==========================================================================
    chip8Archive = {
      url = "github:JohnEarnest/chip8Archive/f91e83fc994b46fbe0abed775790dcc317476fef";
      flake = false;
    };
    chip8-reference = {
      url = "github:badlogic/chip8/57ee10c387cad76a7a4eb3f6afe0d7e57ae92b7b";
      flake = false;
    };
  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
      treefmt-nix,
      flazel,
      chip8Archive,
      chip8-reference,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs { inherit system; };

        # =========================================================================
        # Formatting
        # =========================================================================

        treefmtEval = treefmt-nix.lib.evalModule pkgs {
          projectRootFile = "flake.nix";

          settings.global.excludes = [
            ".bazelrc.nix"
          ];

          programs.nixfmt.enable = true;
          programs.clang-format.enable = true;

          settings.formatter.buildifier = {
            command = "${pkgs.buildifier}/bin/buildifier";
            includes = [
              "BUILD"
              "BUILD.bazel"
              "WORKSPACE"
              "WORKSPACE.bazel"
              "*.bzl"
            ];
          };
        };

        # =========================================================================
        # Project-specific configuration
        # =========================================================================

        # External libraries from nixpkgs (project dependencies)
        # Key = Bazel repo name, Value = nixpkgs package
        mkNixpkgsLibs = buildPkgs: {
          boost = buildPkgs.boost;
          sdl2 = buildPkgs.SDL2;
        };

        # =========================================================================
        # Use flazel for toolchain and build infrastructure
        # =========================================================================

        mkProjectConfig =
          {
            static,
            toolchainName ? "default",
          }:
          let
            buildPkgs = if static then pkgs.pkgsStatic else pkgs;
          in
          flazel.lib.cc.mkConfig {
            inherit pkgs static toolchainName;
            gcc = buildPkgs.gcc15;
            nixpkgsLibs = mkNixpkgsLibs buildPkgs;
          };

        configs = {
          static = mkProjectConfig { static = true; };
          dynamic = mkProjectConfig { static = false; };
        };

        # Non-BCR dependencies (archive_override in MODULE.bazel)
        nonBcrDeps = [
          {
            name = "flazel";
            url = "https://github.com/fabianbuettner/flazel/archive/d05a944c63866210456e9f598a1f7c88b3e5ca3e.tar.gz";
            hash = "sha256-0/GM90Zu1lhA6Q9j4y00XCrtCVezeJPCwQEBCWdq4Go=";
          }
          {
            name = "hedron_compile_commands";
            url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/4f28899228fb3ad0126897876f147ca15026151e.tar.gz";
            hash = "sha256-ZYEiz7HyW+duohKwD16wR9jirci8+SO5GEYfKx43zfI=";
          }
        ];

        # BCR caches
        caches = flazel.lib.mkBcrCaches {
          inherit pkgs nonBcrDeps;
          lockFile = flazel.lib.parseLockFile ./MODULE.bazel.lock;
        };

        # Common install phase
        defaultInstallPhase = ''
          mkdir -p $out/bin
          cp -rL bazel-bin/chip8_emulator $out/bin/ || true
          cp -rL bazel-bin/chip8_disassembler $out/bin/ || true
          # Include test ROMs from flake inputs
          mkdir -p $out/share/chip8/roms
          cp -r ${chip8Archive}/* $out/share/chip8/roms/ || true
        '';

        # =========================================================================
        # Build derivation
        # =========================================================================

        mkBuild =
          {
            static ? true,
          }:
          flazel.lib.cc.mkDerivation {
            inherit pkgs caches;
            name = "chip8" + (if static then "-static" else "");
            cfg = if static then configs.static else configs.dynamic;
            src = ./.;
            bazelCommand = "build --config=nix //:chip8_emulator //:chip8_disassembler";
            installPhase = defaultInstallPhase;
          };

        # =========================================================================
        # Dev shell
        # =========================================================================

        mkDevShell =
          {
            static ? false,
          }:
          flazel.lib.cc.mkDevShell {
            inherit pkgs caches;
            toolchains = {
              default = if static then configs.static else configs.dynamic;
            };
            extraPackages = with pkgs; [
              cloc
              gdb
            ];
          };

      in
      {
        packages = {
          default = mkBuild { static = false; }; # Static fails: SDL2+OpenGL requires dynamic linking
          static = mkBuild { static = true; };
          dynamic = mkBuild { static = false; };

          # ROM collections (from flake inputs)
          roms = chip8Archive.outPath;
          roms-reference = chip8-reference.outPath;

          inherit (caches) bazelRepoCache bazelRegistryCache;
        };

        devShells = {
          default = mkDevShell { static = false; };
          static = mkDevShell { static = true; };
          dynamic = mkDevShell { static = false; };
        };

        legacyPackages.debug = {
          inherit configs caches;
        };

        formatter = treefmtEval.config.build.wrapper;

        checks = {
          formatting = treefmtEval.config.build.check self;
        };
      }
    );
}
