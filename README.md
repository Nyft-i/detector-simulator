[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/LiKsGfCu)

- Identifier is not deep copied.
- I hae decided that `true_energy` is the energy of the particle minus the rest mass. Therefore there doesn't need to be complicated verification over the minimum `true_energy` of a particle.
- All energies and masses are in GeV.

You can compile the program with the command:
`g++ -std=c++17 -fdiagnostics-color=always -g detector_simulation.cpp depositor_particle.cpp particle.cpp photon.cpp electron.cpp nucleon.cpp muon.cpp tau.cpp neutrino.cpp sub_detector.cpp tracker.cpp detector.cpp collision_event.cpp calorimeter.cpp muon_detector.cpp col_result_container.cpp -o detector_simulation.exe`