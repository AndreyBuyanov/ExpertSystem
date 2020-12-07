ExpertSystem
===========
![License](https://img.shields.io/badge/Code%20License-MIT-blue.svg)
---------------
Лабораторная работа №1 по дисциплине "Интеллектуальные системы".

Сборка и запуск
---------------
```bash
cmake -S . -B build && cmake --build build --config RelWithDebInfo
```

Запуск в докере
---------------
```bash
docker build -t intelligent-systems/expert-system .
docker run -it intelligent-systems/expert-system
```
