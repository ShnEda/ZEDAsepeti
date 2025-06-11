# ZEDAsepeti Restaurant Management System

## Overview
ZEDAsepeti is a simple restaurant management system written in C. The project simulates a restaurant workflow with three main modules:
- **musteri.exe**: Customer interface for registration, login, and placing/viewing orders.
- **restoran.exe**: Restaurant management for menu editing, order approval, and reporting.
- **mutfak.exe**: Kitchen module for chef assignment and order tracking (currently not fully functional).

This project was developed by two contributors as part of a programming course.

## Project Structure

```
proje/REYETAP/
    musteri.exe/
        main.c
        musteri.h
        ...
    restoran.exe/
        main.c
        restoran.h
        ...
    mutfak.exe/
        main.c
        mutfak.h
        ...
```

Each folder contains the source code and data files for its respective module.

## How to Build
Each module can be built separately using the provided Code::Blocks project files with their `.c`.

## How to Run
1. *restoran.exe*: Run to manage the menu, approve/reject orders, and view reports.
2. *musteri.exe*: Run to register, log in, and place orders as a customer.
3. *mutfak.exe*: Intended for kitchen staff to track and manage order preparation (currently not working properly).

## Known Issues
- The **mutfak.exe** (kitchen module) does not work properly and may not assign chefs or display orders as intended.
- Data files are shared between modules and must be present in the correct directories for the system to function.

## Authors
- TurkanAYT
- ShnEda

## License
This project is for educational purposes.
