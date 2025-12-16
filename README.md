# MCModelRenderer3DS
A small demo project about rendering Minecraft models from assetjsons

### The Idea:
3D Minecraft assets & Models are written in Json. They determine the Shape, textures and UV Locations of a Model. These Models are built at runtime.
[Minecraft Wiki Model Documentation](https://minecraft.wiki/w/Model)

### The Project:
In order to propperly test this, we need some parts:
- Json loading    We can use nhlohman´s json for that. MCLib comes with this, so this can be swapped easily
- Rendering       We can use Amethyst for this, since ReCraft3DS uses Amethyst
- Debug menus     We can use ImGui CTR for this. Performance really doesnt matter here.

### Proposed Features:
- Load minecraft Texture atlasses
- Render Blocks
- Render Items
- Render TileEntities
- Render Hardcoded Entity Models preferrably with animation, doesnt need to be tho
- Wireframe view
- Camera controller
- Hide cubes (using imgui) because why not :D
- Minecraft Version independent**
- "Resource pack support" Alternative texture metadata loader*

*By that i mean just being able to show other textues rather than vanilla textures. 
If i want, i can add fully fledged resource pack support with fallback textures later.

**By that i mean supporting data from 1.0 (the lowest version that makes sense for [Re::Craft 3DS](https://github.com/SomeRandoLameo/Re-Craft-3DS)) to the newest version

### Credits:
- Tobid7 for [Amethyst](https://github.com/tobid7/amethyst)
- Tobid7 for [imgui-impl-ctr](https://github.com/npid7/imgui-impl-ctr)
- [imgui-ctr](https://github.com/npid7/imgui-impl-ctr/tree/e67a33579fa6424171ec1a583b6baffa077ee2d3)
- nhlohman for the [Json loader](https://github.com/nlohmann/json)
- People behind [The Minecraft Wiki](https://minecraft.wiki)
- People behind [Dear ImGui](https://github.com/ocornut/imgui)

If i used your code and you dont feel credited, dm me so we can change that!
