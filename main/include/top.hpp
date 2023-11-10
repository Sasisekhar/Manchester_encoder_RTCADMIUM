#ifndef SASI_TOP_HPP
#define SASI_TOP_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "ME.hpp"
#include "generator.hpp"

namespace cadmium::topSystem {
    struct topSystem : public Coupled {

            /**
             * Constructor function for the blinkySystem model.
             * @param id ID of the blinkySystem model.
             */
            topSystem(const std::string& id) : Coupled(id) {
                auto ME1 = addComponent<ME>("ME", (gpio_num_t) 18, (gpio_num_t) 19, (uint32_t)80 * 1000 * 1000);
                auto generator = addComponent<Generator>("generator");

                addCoupling(generator->out, ME1->in);
            }
        };
}

#endif