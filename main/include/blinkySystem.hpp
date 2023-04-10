#ifndef CADMIUM_EXAMPLE_BLINKY_HPP_
#define CADMIUM_EXAMPLE_BLINKY_HPP_

#include <../../components/cadmium_v2/include/cadmium/core/modeling/coupled.hpp>

#ifdef RT_ESP32
	#include <../../components/cadmium_v2/include/cadmium/core/real_time/ESP32/io/digitalOutput.hpp>
	#include <../../components/cadmium_v2/include/cadmium/core/real_time/ESP32/io/digitalInput.hpp>
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
			// ESP32
			auto digitalOutput = addComponent<DigitalOutput>("digitalOuput", 2);	//Onboard LED
			auto digitalInput  = addComponent<DigitalInput>("digitalInput", 0);		//BOOT button
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
