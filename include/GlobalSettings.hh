/*  Global parameters such as filenames, detector dimensions, etc., shared between all classes.
 *  The difference from GlobalData is that this class only stores simple parameters which all
 *  may be easily changed without silent breaking of simulation.
 *  All parameters must be read only during simulation after their initialization.
 */
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>

#include <G4SystemOfUnits.hh>
#include <G4PhysicalConstants.hh>
#include <G4ThreeVector.hh>

static constexpr double hc = hbarc * twopi; // for recalculating photon energy to wavelength and back. E*lambda = h*c = const.

namespace settings
{
    enum GenerationPattern {
        CenterCollimated, // All gammas are produced at the source center and have momentum along z axis. 
        CenterIsotropic, // All gammas are produced at the source center and have isotropic momentum distribution.
        UniformIsotropic // Gammas are produced uniformily in the source volume with isotropic momentum distribution.
    };

    struct ProgramSetups {
        std::string this_path;
        std::string data_path;
        // std::string settings_filename;
        std::string output_folder;
        std::string geometry_fname;
        std::string energy_deposition_filename;
        // std::string gnuplot_bin;
        uint thread_number;
        uint N_events;
        bool do_view;
        bool check_geometry_overlap;
        std::string sensor_volume_name; // name of physical volume
        GenerationPattern source_pattern;
        G4long initial_seed; // If not specified in settings, random time(NULL) is used as starting seed for the simulation
    };

    bool Initialize(const std::string& filename);
    bool Load(const std::string& filename);

    extern ProgramSetups general;
}
