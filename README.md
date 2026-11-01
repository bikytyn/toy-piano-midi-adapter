# Toy Piano MIDI Adapter

An open-source project to convert a cheap 54-key children's toy keyboard into a native USB MIDI controller using an **Arduino Micro** (ATmega32U4).

## Features
- **Native USB MIDI:** Recognized automatically by Windows, macOS, and Linux as a standard MIDI device without third-party bridging software (no Hairless MIDI needed).
- **Matrix Scanning:** Efficiently scans the 7x8 key matrix.
- **Zig-Zag PCB Correction:** Software-level serpentine layout correction to ensure sequential chromatic note mapping from left to right.
- **Low Latency & Debounce:** Built-in software debounce for reliable triggering.

## Hardware Pinout

| Ribbon Cable | Function | Arduino Micro Pin |
| :--- | :--- | :--- |
| **Ribbon 1 (7 wires)** | Rows | `2`, `3`, `4`, `5`, `6`, `7`, `8` |
| **Ribbon 2 (8 wires)** | Columns | `A3`, `A2`, `A1`, `A0`, `15`, `14`, `16`, `10` |

## Requirements
- Arduino IDE
- Arduino AVR Boards package
- `MIDIUSB` library by Arduino Contributors

## Installation & Usage
1. Connect the keyboard matrix ribbons to the Arduino Micro according to the pinout table above.
2. Open the `.ino` sketch in Arduino IDE.
3. Select board: **Arduino Micro**.
4. Upload the sketch.
5. Connect to your favorite DAW (Ableton, FL Studio, Reaper, Numaplayer) and play!
