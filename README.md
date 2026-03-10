# ems
Electronic Management System for BMW Airhead & K Bike Motorcycles

## Project structure

This repository now follows a sketch-first layout:

- `ems.ino`: Arduino sketch entry point (`setup()` / `loop()`).
- `src/`: First-party EMS modules (`.h/.cpp`).
- `src/vendor/`: Vendored third-party libraries compiled with the sketch (`SSD1306Ascii`, `rfid`).

```text
.
├── ems.ino
├── src/
│   ├── motorcycle.h
│   ├── motorcycle.cpp
│   ├── engine.h
│   ├── engine.cpp
│   └── ...
└── src/
    ├── ...
    └── vendor/
        ├── SSD1306Ascii/
        └── rfid/
```
