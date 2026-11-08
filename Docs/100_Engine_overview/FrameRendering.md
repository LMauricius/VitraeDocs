# Frame rendering

## Canvas to render on

All rendering is done on a part of a `Canvas` asset.
Which part is specified with a `DrawRegion` object.

A `Canvas` describes all images we will draw on,
and memory buffers that are needed for rendering.
This among the others contains the image that will be shown to the player.

A `DrawRegion` describes which part of a frame we will draw on.
Imagine split-screen games - they have multiple `DrawRegion`s.

This is often used to repeat the same composition (a sequence of `ComposeMethod`s)
on multiple parts of the `Canvas` while adjusting a small number of parameters and values.
So multiple compositions can use the same `Canvas`,
and multiple compositions can use the same `DrawRegion`,
but they can also combine them however they want.

Let's say we have this screen configuration for a 3-player split-screen game:
```mermaid
block-beta
    block:F["Canvas"]
        columns 2
        A["\nDrawRegion A\n\n"]:2
        B["\nDrawRegion B\n\n"]:1
        C["\nDrawRegion C\n\n"]:1
    end

    class A,B,C daStyle
    class F canvasStyle
    classDef canvasStyle fill:yellow,fill-opacity:0.15,stroke:darkkhaki;
    classDef daStyle fill:ghostwhite,fill-opacity:0.15,stroke:gray,stroke-dasharray:9;
```

In that case we would need 3 `DrawRegions`s, one for each composition:
```mermaid
graph TB
    F[Canvas]:::canvasStyle

    A[DrawRegion A]:::daStyle --> RA([Composition A])
    F --> RA
    F ~~~ A
    
    B[DrawRegion B]:::daStyle --> RB([Composition B])
    F --> RB
    F ~~~ B

    C[DrawRegion C]:::daStyle --> RC([Composition C])
    F --> RC
    F ~~~ C

    classDef canvasStyle fill:yellow,fill-opacity:0.15,stroke:darkkhaki;
    classDef daStyle fill:ghostwhite,fill-opacity:0.15,stroke:gray,stroke-dasharray:9;
```

## Composition graph
```mermaid
flowchart LR
    CD(Create DrawRegion)
    PCNV(Prepare Canvas)
    R(Render scene)
    UCNV(Have a finished Canvas)
    ET(Extract rendered Textures)

    CD --> PCNV
    PCNV --> R
    R --> UCNV
    UCNV --> ET
```