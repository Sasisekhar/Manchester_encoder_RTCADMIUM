#include <stdio.h>
#include "../components/cadmium_v2/include/cadmium/core/simulation/root_coordinator.hpp"
#include "../components/cadmium_v2/include/cadmium/core/logger/rt.hpp"
#include <limits>
#include "include/blinkySystem.hpp"

using namespace cadmium::blinkySystem;
extern "C" {
	#ifdef RT_ESP32
		void app_main() //starting point for ESP32 code
	#else
		int main()		//starting point for simulation code
	#endif
	{
		std::shared_ptr<blinkySystem> model = std::make_shared<blinkySystem> ("blinkySystem");
		auto rootCoordinator = cadmium::RootCoordinator(model);

		#ifndef NO_LOGGING
			auto logger = std::make_shared<cadmium::RTLogger>(";");
			rootCoordinator.setLogger(logger);
		#endif

		rootCoordinator.start();
	// 	rootCoordinator.simulate(std::numeric_limits<double>::infinity());
		rootCoordinator.simulate(100.0);
		rootCoordinator.stop();

		#ifndef RT_ESP32
			return 0;
		#endif
	}
}
