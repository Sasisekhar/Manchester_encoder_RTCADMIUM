#ifndef CADMIUM_EXAMPLE_BLINKY_HPP_
#define CADMIUM_EXAMPLE_BLINKY_HPP_

#include <../../components/cadmium_v2/include/cadmium/core/modeling/coupled.hpp>

#ifdef RT_ESP32
	#include <../../components/cadmium_v2/include/cadmium/core/real_time/arm_mbed/io/digitalOutput.hpp>
	#include <../../components/cadmium_v2/include/cadmium/core/real_time/arm_mbed/io/digitalInput.hpp>
#endif

#include "blinky.hpp"

#ifndef RT_ESP32
	#include "generator.hpp"
#endif

namespace cadmium::blinkySystem {

	struct blinkySystem : public Coupled {

		/**
		 * Constructor function for the blinkySystem model.
		 * @param id ID of the blinkySystem model.
		 */
		blinkySystem(const std::string& id) : Coupled(id) {
            auto blinky = addComponent<Blinky>("blinky");
#ifdef RT_ESP32		
			// NUCLEO F401RE
			auto digitalOutput = addComponent<DigitalOutput>("digitalOuput", 2);
			auto digitalInput  = addComponent<DigitalInput>("digitalInput", 0);
			// BLUE PILL
			// auto digitalOutput = addComponent<DigitalOutput>("digitalOuput", PC_13);
			// auto digitalInput  = addComponent<DigitalInput>("digitalInput", PB_14);
			addCoupling(digitalInput->out, blinky->in);
			addCoupling(blinky->out, digitalOutput->in);
#else
			auto generator = addComponent<Generator>("generator");
			addCoupling(generator->out, blinky->in);
#endif
		}
	};
}  //namespace cadmium::blinkySystem

#endif //CADMIUM_EXAMPLE_BLINKY_HPP_
