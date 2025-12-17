# Minecraft 1.12.2 Base assets

These are the base assets for Minecraft version 1.12.2. They include textures, sounds, and other resources used in the game.

Ideally, these assets should be a submodule, so that we dont need to store them here as well.

For the Original asset location, see: [InventivetalentDev / minecraft-assets | Github](https://github.com/InventivetalentDev/minecraft-assets/tree/1.12.2)

In order for the base assets to be recognized, they need to be modified to include a `pack.mcmeta` and `pack.png` file in the root directory.
- for `pack.mcmeta`: You need to move the `pack.mcmeta` from `/assets/pack.mcmeta` to the root directory (`/`), and add a `pack.png` file to the root directory as well.
- for `pack.png`: You can copy the 32x `icon_32x32.png` from `/assets/icons/icon_32x32.png` to the root directory and rename it to `pack.png`.

This is how minecraft texture packs are structured. We can just treat this as a texture pack for minecraft 1.12.2.

the `.mcassetsroot` file is there for the MCModelLoader to recognize these as base assets. *DO NOT REMOVE IT*.