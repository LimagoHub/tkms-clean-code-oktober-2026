# TBB Parallel-For Demo

Kleines C++17-Projekt, das mit Intel oneTBB (`tbb::parallel_for` und `tbb::parallel_reduce`) eine Schleife über 50 Mio. Elemente parallel abarbeitet.

## Projektstruktur

```
CMakeLists.txt        Build-Definition
src/main.cpp          Demo (parallel_for + parallel_reduce)
third_party/oneTBB/   oneTBB v2021.12.0 als Quellcode (eingebettet, kein Download nötig)
```

## Voraussetzungen

- CMake >= 3.20 (getestet mit 3.29.2, `C:\Program Files\CMake\bin`)
- MinGW-w64 GCC. Zwei Toolchains getestet:
  - **UCRT-MinGW** GCC 13.2, `C:\applications\mingw64\bin` (enthält Ninja und mingw32-make). **Empfohlen für die Auslieferung.**
  - **In CLion gebündeltes MinGW** (msvcrt, GCC 15.2). Gut zum Entwickeln und Debuggen.
- CLion (optional)

## Schritte zur Erstellung

1. Projektdateien `CMakeLists.txt` und `src/main.cpp` anlegen.
2. oneTBB wurde zunächst per `FetchContent` von GitHub geladen. Da beim Kunden die Firewall das verhindert, wurde der Quellcode in `third_party/oneTBB` abgelegt (ohne `.git`, Tests, Beispiele, Doku; ca. 4 MB) und wird per `add_subdirectory(third_party/oneTBB EXCLUDE_FROM_ALL)` eingebunden. Der Build braucht keinen Netzzugriff.
3. `TBB_TEST`, `TBB_STRICT` und `TBB_EXAMPLES` sind ausgeschaltet. Die Meldungen zu `HWLOC` beim Konfigurieren sind harmlos (nur die optionale NUMA-Unterstützung fehlt).
4. Nach dem Build kopiert ein Post-Build-Schritt die TBB-DLL neben die `.exe`.
5. Die MinGW-Laufzeit wird statisch gelinkt (siehe unten).
6. oneTBB wurde lokal gepatcht, damit der Debug-Build unter MinGW kompiliert (siehe unten).

## Bauen und Starten per Kommandozeile

```powershell
$env:PATH = "C:\applications\mingw64\bin;C:\Program Files\CMake\bin;$env:PATH"
cmake -S . -B cmake-build-release -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build cmake-build-release
.\cmake-build-release\parallel_sum.exe
```

Beispielausgabe:

```
Threads: 22
Summe:   -6569.78
Zeit:    142 ms
```

## Bauen mit CLion

1. `File > Open` und den Ordner `tkms` wählen.
2. `Settings > Build, Execution, Deployment > Toolchains`: Toolchain wählen.
   - Entwickeln/Debuggen: das gebündelte MinGW genügt.
   - Auslieferung: MinGW auf `C:\applications\mingw64` stellen.
3. Beim ersten Öffnen legt CLion ein Debug-Profil an. Für Performance-Messungen und die Auslieferung ein Release-Profil ergänzen (`Settings > Build, Execution, Deployment > CMake`, Build type `Release`).
4. Target `parallel_sum` auswählen und starten.
5. Nach einem Toolchain-Wechsel: `Tools > CMake > Reset Cache and Reload Project`.

## Auslieferung an den Kunden

| Build / Toolchain | Mitzuliefern |
|---|---|
| Release mit `C:\applications\mingw64` (UCRT) | `parallel_sum.exe`, `libtbb12.dll` |
| Debug mit CLion-MinGW (msvcrt) | `parallel_sum.exe`, `libtbb12_debug.dll`, `libwinpthread-1.dll` |

Mit dem UCRT-MinGW wird voll statisch gelinkt, es hängt nur noch an Windows-DLLs. Beim CLion-MinGW geht statisches `winpthread` nicht (siehe unten), daher muss `libwinpthread-1.dll` dazu. Sie liegt unter `...\CLion 2025.3.2\bin\mingw\bin`. In CLion läuft das Programm auch ohne, weil CLion den `PATH` setzt. Alle Dateien gehören in denselben Ordner.

## Hinweise

### Statisches Linken der MinGW-Laufzeit

`CMakeLists.txt` prüft beim Konfigurieren per `check_cxx_source_compiles`, ob `-static` funktioniert:

- **Ja (UCRT-MinGW):** `-static`. Gilt auch für die TBB-DLL, es sind keine MinGW-DLLs nötig.
- **Nein (CLion-MinGW, msvcrt):** CMake gibt eine Warnung aus und linkt nur `-static-libstdc++ -static-libgcc`. Das statische `libwinpthread` scheitert dort mit `undefined reference to '__intrinsic_setjmpex'`, weil Symbole der UCRT fehlen.

### Lokaler Patch an oneTBB 2021.12.0

In `third_party/oneTBB/include/oneapi/tbb/profiling.h` wurde bei `itt_set_sync_name` die Bedingung `&& !__MINGW32__` entfernt (`#if (_WIN32||_WIN64)`). Ohne den Patch scheitert der Debug-Build unter MinGW mit `cannot convert 'const char*' to 'const wchar_t*'`. Der Release-Build war nicht betroffen. Bei einem oneTBB-Update prüfen, ob der Patch noch nötig ist.

### Bekannte, harmlose Meldungen

- `HWLOC target ... doesn't exist` beim Konfigurieren: nur die optionale NUMA-Unterstützung (`tbbbind`) wird nicht gebaut.
- `warning: value computed is not used` in `dynamic_link.cpp`: Warnung im oneTBB-Code selbst.

### Lizenz

oneTBB steht unter Apache 2.0 (`third_party/oneTBB/LICENSE.txt`).
