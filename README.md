# MCModelRenderer3DS
A small demo project about rendering Minecraft models from assetjsons & Textures as well as hardcoded Models
- Its ment for learning on how the minecraft models work together. This is not a library of any form.
- This micorproject is ment for my main project [Re::Craft 3DS](https://github.com/SomeRandoLameo/Re-Craft-3DS). If you want to port this to PC: Go for it! 

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
- inventivetalent for [MCAssets](https://mcasset.cloud) - This is a very helpful resource
- People behind [The Minecraft Wiki](https://minecraft.wiki) - This is a very helpful resource as well!
- inventivetalent for [MineRenderer](https://github.com/InventivetalentDev/MineRender) - This is a very helpful resource to learn on how to handle the asset data
- Tobid7 for [Amethyst](https://github.com/tobid7/amethyst)
- Tobid7 for [imgui-impl-ctr](https://github.com/npid7/imgui-impl-ctr)
- [imgui-ctr](https://github.com/npid7/imgui-impl-ctr/tree/e67a33579fa6424171ec1a583b6baffa077ee2d3)
- nhlohman for the [Json loader](https://github.com/nlohmann/json)
- People behind [Dear ImGui](https://github.com/ocornut/imgui)

If i used your code and you dont feel credited, dm me so we can change that!

### AI Code
AI Is a tool, not a fullstack programmer.
  
- You can use AI to explain how things work
- You can use AI to help sketching out features/Idea concepts

- PRs that are 100% AI Code will NOT be accepted.
- You cannot use AI to write ccode that you could have wrote yourself
- You cannot use AI to automate development processes
- You cannot use AI to vibecode here, unless someone allows you to
- You cannot use AI to communicate to other devs, speak for yourself

- We want human written - human readable and human usable code, not AI Slop
