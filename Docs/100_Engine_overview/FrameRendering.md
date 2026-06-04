# Frame rendering

## Target to render

All rendering is done on a `RenderTarget` object.
`RenderTarget` is like a part of the canvas we draw our image on.
It mainly binds 2 other objects:
- a `Viewport` - Describes which part of a frame we will draw on.
Imagine split-screen games - they have multiple `Viewport`s.
- a `FrameStore` - Describes all images we will draw on,
and memory buffers that are needed for rendering.
This is among the rest contains the image that will be shown to the player.

So multiple `RenderTargets` can use the same `FrameStore`,
and multiple `RenderTargets` can use the same `Viewport`,
but they can also combine them however they want
(usually you won't have multiple `RenderTarget`s that describe the same set of the two).

Let's say we have this screen configuration for a 3-player split-screen game:
```mermaid
block-beta
    block:F["Framestore"]
        columns 2
        A["\nViewport A\n\n"]:2
        B["\nViewport B\n\n"]:1
        C["\nViewport C\n\n"]:1
    end

    class A,B,C vpStyle
    class F fsStyle
    classDef fsStyle fill:yellow,fill-opacity:0.15,stroke:darkkhaki;
    classDef vpStyle fill:ghostwhite,fill-opacity:0.15,stroke:gray,stroke-dasharray:9;
```

In that case we would need 3 `RenderTarget`s, one for each `Viewport`:
```mermaid
graph TB
    F[Framestore]:::fsStyle

    A[Viewport A]:::vpStyle --> RA([RenderTarget A])
    F --> RA
    F ~~~ A
    
    B[Viewport B]:::vpStyle --> RB([RenderTarget B])
    F --> RB
    F ~~~ B

    C[Viewport C]:::vpStyle --> RC([RenderTarget C])
    F --> RC
    F ~~~ C

    classDef fsStyle fill:yellow,fill-opacity:0.15,stroke:darkkhaki;
    classDef vpStyle fill:ghostwhite,fill-opacity:0.15,stroke:gray,stroke-dasharray:9;
```

## Composition graph
```mermaid
flowchart LR
    CVP(Create Viewport)
    PFS(Prepare FrameStore)
    PRT(Prepare RenderTarget)
    R(Render scene)
    URT(Have used RenderTarget)
    ET(Extract rendered Textures)

    CVP --> PRT
    PFS --> PRT
    PRT --> R
    R --> URT
    URT --> ET
```