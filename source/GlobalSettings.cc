#include <stdexcept>
#include <GlobalSettings.hh>

namespace settings
{
	ProgramSetups general;

  bool Initialize(const std::string& filename)
	{
	  // Possible defaults set before Load(const std::string& filename)
	  // They may be overwritten in Load(const std::string& filename).
	  // If default is not possible and is absent in settings,
	  // initialization fails.
		char path[FILENAME_MAX];
#if defined(__WIN32__)
		general.this_path = _getcwd(path, FILENAME_MAX);
#else
		general.this_path = getcwd(path, FILENAME_MAX);
#endif
		if (!general.this_path.empty())
			if (general.this_path.back()!='/')
			  general.this_path.push_back('/');

// #if defined(_WIN32)||defined(_WIN64)
// 		general.gnuplot_bin = "\"%GNUPLOT%\\gnuplot.exe\"";
// #else
// 		general.gnuplot_bin = "gnuplot";
// #endif
		// general.settings_filename = filename;
		if (!Load(filename))
		  return false;

		//=====================================================================================================================
		// Consistency checks below

    std::cout<<"This path: \""<<general.this_path<<"\""<<std::endl;
    std::cout<<"Data path: \""<<general.this_path+general.data_path<<"\""<<std::endl;

    if (general.thread_number < 1) {
      std::cout << __PRETTY_FUNCTION__ << ": Warning, thread number < 1, setting to 1." << std::endl;
      general.thread_number = 1;
    }

    const uint max_viewable_events = 200u;
    if (general.N_events > max_viewable_events && general.do_view) {
      G4Exception(__PRETTY_FUNCTION__,
            "InvalidSetup", FatalException,
            "Viewing large number of events (> "s + std::to_string(max_viewable_events) + ") is disabled.");
      return false;
    }
    return true;
	}

	bool Load(std::string fname)
	{
	  // std::cout << "Loading settings \"" << fname << "\"..." << std::endl;
    // TODO: add parsing of argc and argv**
    general.data_path = "inputs/";
    general.output_folder = "outputs/";
    general.energy_deposition_filename = "energy_histogram.dat";
    general.thread_number = 1;
    general.N_events = 1;
    general.do_view = true;
    general.check_geometry_overlap = true;
    general.source_pattern = GenerationPattern::CenterCollimated;
    general.initial_seed = 42; // time(NULL)


    // std::cout << __PRETTY_FUNCTION__ << ": successfully loaded \"" << fname << "\"" << std::endl;
    return true;
  fail_load:
    std::cerr << __PRETTY_FUNCTION__ << ": failed to load \"" << fname << "\"" << std::endl;
    return false;
	}

	
}
