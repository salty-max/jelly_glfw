# Jelly: 2D Game Framework Specifications

## Framework Design Goals
- **Ease of Use**: Simple API, minimal setup for game developers.
- **ECS Integration**: Modular and flexible game object management system.
- **Cross-Platform**: Support for Windows, macOS, and Linux.
- **Lightweight**: Keep the library minimal, focusing on 2D game development.
- **Extendable**: Allow users to add custom components, systems, or functionality.

## Core Features

### Core Modules

#### 1. **Window and Input Management**
- **Library**: GLFW
- **Features**:
  - Window creation and management.
  - Input handling (keyboard, mouse, and basic gamepad support).
  - Abstracted into `Window` and `Input` classes/modules for simplicity.

#### 2. **2D Rendering**
- **Library**: OpenGL
- **Features**:
  - Sprite rendering.
  - Batch rendering for performance.
  - Basic primitives (lines, rectangles, circles).
  - Texture and animation support.

#### 3. **Audio**
- **Library**: OpenAL
- **Features**:
  - Background music playback.
  - Sound effects.
  - Simple API for controlling audio.

#### 4. **Math Library**
- **Library**: Custom Implementation
- **Features**:
  - Vectors, matrices, and transformations.
  - Core utilities for physics and rendering calculations.

#### 5. **Entity-Component System (ECS)**
- **Features**:
  - **Entities**: Unique identifiers.
  - **Components**: Modular data storage (e.g., Position, Velocity, Sprite).
  - **Systems**: Logic modules operating on components (e.g., RenderSystem, PhysicsSystem).

### Additional Features

#### 1. **File I/O**
- **Library**: Standard C++
- **Features**:
  - Loading textures, audio files, and other assets.
  - File operations using standard C++ I/O libraries.

#### 2. **UI**
- **Library**: Dear ImGui (for debugging UI).
- **Features**:
  - Basic UI components (buttons, sliders, text boxes).
  - Debugging overlays.

#### 3. **Debugging Tools**
- **Features**:
  - FPS counters.
  - Entity/component inspection.
  - In-game debugging menus.

## ECS Architecture

### Components:
- Data structures associated with entities.
- Examples: `Position`, `Velocity`, `Sprite`, `Health`.

### Entities:
- Unique identifiers for game objects.
- Associated with a collection of components.

### Systems:
- Logic modules operating on entities with specific components.
- Examples:
  - **RenderSystem**: Draw entities with `Sprite` components.
  - **PhysicsSystem**: Update entities with `Position` and `Velocity` components.
  - **InputSystem**: Process player input.

## Framework API

### Initialization
```cpp
JellyInit(800, 600, "My Game"); // Initialize the framework

Entity player = EntityManager::CreateEntity();
player.AddComponent<Transform>(0, 0, 0);
player.AddComponent<Sprite>("player.png");
player.AddComponent<Velocity>(5, 0);
```

### Game Loop
```cpp
while (JellyRunning()) {
    InputSystem::Update();
    PhysicsSystem::Update();
    RenderSystem::Update();
}
JellyClose();
```

## Development Roadmap

### Phase 1: Core Framework
- Implement window management, input handling, and a basic renderer.
- Build a simple ECS with entities and components.

### Phase 2: Feature Expansion
- Add audio playback and asset loading.
- Integrate text rendering and animations.

### Phase 3: Testing and Tools
- Test cross-platform support.
- Add debugging and profiling tools.

### Phase 4: Documentation and Examples
- Write clear documentation and provide example games to demonstrate usage.

## Recommended Libraries
- **Window/Input**: GLFW
- **Rendering**: OpenGL
- **Audio**: OpenAL
- **Math**: Custom Implementation
- **File I/O**: Standard C++
- **UI Tools**: Dear ImGui (for debugging)

## Long-Term Vision
- Modular system for adding custom components and systems.
- Templates for common 2D game genres (e.g., platformers, top-down shooters).
- Toolchain for asset management and deployment.

## Summary
Jelly aims to simplify and accelerate 2D game development by coupling a lightweight ECS with modern rendering and input libraries. It offers modularity, cross-platform support, and extensibility, enabling rapid game prototyping and development.
