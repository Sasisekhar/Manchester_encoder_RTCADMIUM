#include <cadmium/simulation/logger/rt.hpp>
#include <include/cadmium/simulation/rt_root_coordinator.hpp>
#include <include/cadmium/simulation/rt_clock/chrono.hpp>
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
		cadmium::ChronoClock clock;
		auto rootCoordinator = cadmium::RealTimeRootCoordinator<cadmium::ChronoClock<std::chrono::steady_clock>>(model, clock);
		cadmium::Logger logger = std::make_shared<cadmium::RTLogger>(";");
		rootCoordinator.setLogger(model, &logger);

		rootCoordinator.start();
		rootCoordinator.simulate(std::numeric_limits<double>::infinity());
		// rootCoordinator.simulate(100.0);
		rootCoordinator.stop();	

		#ifndef RT_ESP32
						return 0;
		#endif
	}
}
