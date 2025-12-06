# Chip8 flazel demo: Overkill? Maybe. Awesome? Absolutely.

This project uses [flazel](https://github.com/fabianbuettner/flazel) – because why choose between Nix and Bazel when you can have both?

## The Flex

You know how most projects have a README section that says "Prerequisites: install gcc, cmake, libboost-dev, libsdl2-dev, pray to the linker gods..."?

Yeah, we don't do that here.

```bash
nix develop    # You now have everything. Yes, everything.
bazel build    # It's already done. Wait, you blinked.
```

## What's Actually Happening

We let each tool do what it's *disgustingly good* at:

**Nix** handles the "what goes into the build":
- Pins your toolchain to the exact GCC commit from 3 weeks ago? ✓
- Guarantees the same build on your laptop, CI, and your friend's weird Arch setup? ✓
- Makes "dependency hell" a phrase you'll tell your grandchildren about? ✓

**Bazel** handles the "how fast can we go":
- Changed one file? Rebuilds one file. Revolutionary, I know.
- Content-addressed caching that actually works? ✓
- Makes you mass-rename files for fun because rebuilds are cheap? ✓

## The Party Tricks

| Trick | How |
|-------|-----|
| Build works on any Linux box | `nix build` – that's it, that's the trick |
| Offline builds | BCR cached in Nix store. Airplane mode? No problem. |
| Switch compilers | Change one line in `flake.nix`. Get coffee. Come back. Done. |
| Cross-compile | Add a toolchain. Bazel figures out the rest. |
| Reproduce a build from 6 months ago | `git checkout` + `nix build` = identical binary |

## The Developer Experience

```bash
# Day 1 on the project
$ nix develop
$ bazel build //...
# There is no day 2 of setup. You're already coding.
```

No Docker containers. No version managers. No "oh you need the *other* libssl".

Just vibes and reproducible builds.

## "But Isn't This Overkill for a Chip8 Emulator?"

Yes. Gloriously, unapologetically yes.

But also: the build system took a weekend. It'll work unchanged for years. And now I mass-refactor for fun because rebuilds take 200ms.

Worth it? *chef's kiss*
