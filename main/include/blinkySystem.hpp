#ifndef CADMIUM_EXAMPLE_BLINKY_HPP_
#define CADMIUM_EXAMPLE_BLINKY_HPP_

#include <cadmium/modeling/devs/coupled.hpp>
#include "blinky.hpp"

#ifdef RT_ESP32
	#include "digitalOutput.hpp"
	#include "digitalInput.hpp"
#else
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
// 			// ESP32
			auto digitalOutput = addComponent<DigitalOutput>("digital_output", 2);	//Onboard LED
			auto digitalInput  = addComponent<DigitalInput>("digital_input", 0);		//BOOT button
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
