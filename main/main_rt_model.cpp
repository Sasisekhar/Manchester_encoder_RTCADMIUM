#include <stdio.h>
#include "../components/cadmium_v2/include/cadmium/core/simulation/root_coordinator.hpp"
#include "../components/cadmium_v2/include/cadmium/core/logger/rt.hpp"
#include <limits>
#include "include/blinkySystem.hpp"

// #if CONFIG_FREERTOS_UNICORE
// 	static const BaseType_t app_cpu = 0;
// #else
// 	static const BaseType_t app_cpu = 2;
// #endif

using namespace cadmium::blinkySystem;
extern "C" {
	void app_main() {

		std::shared_ptr<blinkySystem> model = std::make_shared<blinkySystem> ("blinkySystem");
		auto rootCoordinator = cadmium::RootCoordinator(model);
		ESP_LOGI("APP MAIN", "Created System");

		#ifndef NO_LOGGING
			auto logger = std::make_shared<cadmium::RTLogger>(";");
			rootCoordinator.setLogger(logger);
			ESP_LOGI("APP_MAIN", "Logger Set");
		#endif

		rootCoordinator.start();
	// 	rootCoordinator.simulate(std::numeric_limits<double>::infinity());
		rootCoordinator.simulate(1000000.0);
		rootCoordinator.stop();
	}
}
