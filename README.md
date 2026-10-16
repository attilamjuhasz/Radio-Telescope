# Radio Telescope

This repository contains the design files, 3D-printable parts, and control code for a personal radio telescope built to map the Milky Way using the 21 cm hydrogen line.

## Overview

The project includes:

- A 3D-printed chassis and enclosure for the telescope body
- A support structure and lid assembly for the main housing
- A geared motion system for up/down positioning
- Control code for stepper motor movement
- Printable STL and CAD source files for iterative prototyping and fabrication

This project was created to observe the universe in ways that are not visible to the human eye. We can only see the visible spectrum, and this project was intended to expand that view.

## Repository Structure

- `Chassis/` - Main telescope body and structural components
- `Chassis-Lid/` - Lid and support pieces for the outer shell
- `Chassis-Foot/` - Foot and mounting support
- `Gear-Plate-and-N17A-Gear/` - Gear plate and drive gear components
- `Up-Down-Motion/` - Vertical motion mechanism and associated hardware
- `Fans/` - Fan housings and airflow-related printed parts
- `Code/` - Software and firmware for motion control

## Getting Started

1. Review the relevant CAD and STL folders for the mechanical system you want to print or adjust.
2. Open the `.f3d` files in Fusion 360 or a compatible CAD tool if you need to modify the design.
3. Use the STL files for 3D printing.
4. Upload the Arduino sketch in `Code/Nema-17-StepperMotor-1/` to a compatible microcontroller.
5. Connect the stepper motor, direction pin, step pin, and potentiometer as defined in the sketch.
6. Test the motion system before integrating it with the antenna assembly and radio hardware.

## Notes

This repository is intended for amateur radio astronomy and experimentation. Several files are iterative design revisions and should be treated as engineering artifacts rather than final production parts.

## License

This project is shared for educational and experimental use. Please review the repository contents and check any applicable third-party licensing information before manufacturing or distributing physical parts.
