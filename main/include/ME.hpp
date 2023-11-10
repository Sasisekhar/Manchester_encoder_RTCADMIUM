#ifndef ME_HPP
#define ME_HPP

#include <iostream>

#include "cadmium/modeling/devs/atomic.hpp"
#include <driver/gpio.h>
#include "esp_system.h"
#include "esp_console.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/rmt_tx.h"
#include "driver/rmt_rx.h"
#include "esp_log.h"
#include "drivers/manchester_encoder.h"

namespace cadmium {

    struct MEState {
        uint32_t data;
        double sigma;

        /**
         * Processor state constructor. By default, the processor is idling.
         * 
         */
        explicit MEState(): data(0), sigma(0){
        }
    };

    std::ostream& operator<<(std::ostream &out, const MEState& state) {
        out << "data: " << state.data;
        return out;
    }

    class ME : public Atomic<MEState> {
        private:
        const char* TAG = "ME Atomic";

        uint32_t TICK_RESOLUTION = 80 * 1000 * 1000;
        rmt_receive_config_t rx_config;
        rmt_transmit_config_t tx_config;
        rmt_channel_handle_t rx_channel;
        rmt_channel_handle_t tx_channel;
        rmt_encoder_handle_t manchester_encoder;

        void config_channel_encoders() {
            
            ESP_LOGI(TAG, "Create PHY RX channel");
            rmt_rx_channel_config_t rx_channel_cfg = {
                .gpio_num = rxpin,
                .clk_src = RMT_CLK_SRC_DEFAULT,
                .resolution_hz = TICK_RESOLUTION,
                .mem_block_symbols = 64, // amount of RMT symbols that the channel can store at a time
            };
            ESP_ERROR_CHECK(rmt_new_rx_channel(&rx_channel_cfg, &rx_channel));

            ESP_LOGI(TAG, "Create PHY TX channel");
            rmt_tx_channel_config_t tx_chan_config = {
                .gpio_num = txpin,
                .clk_src = RMT_CLK_SRC_DEFAULT, // select clock source
                .resolution_hz = TICK_RESOLUTION,
                .mem_block_symbols = 64,
                .trans_queue_depth = 3, // set the number of transactions that can be pending in the background
            };
            ESP_ERROR_CHECK(rmt_new_tx_channel(&tx_chan_config, &tx_channel));

            ESP_LOGI(TAG, "Create encoders");

            manchester_encoder_config_t manchester_encoder_config = {
                .resolution = TICK_RESOLUTION,
            };
            ESP_ERROR_CHECK(rmt_new_manchester_encoder(&manchester_encoder_config, &manchester_encoder));

            ESP_LOGI(TAG, "Enable RMT channel");
            ESP_ERROR_CHECK(rmt_enable(tx_channel));
            ESP_ERROR_CHECK(rmt_enable(rx_channel));
        }
        public:

        Port<uint32_t> in;
        Port<uint32_t> out;

        gpio_num_t txpin;
        gpio_num_t rxpin;

        //Constructor
        ME(const std::string id, gpio_num_t _txpin, gpio_num_t _rxpin, uint32_t _tickres): Atomic<MEState> (id, MEState()) {
            in = addInPort<uint32_t> ("in");
            out = addOutPort<uint32_t> ("out");

            txpin = _txpin;
            rxpin = _rxpin;

            TICK_RESOLUTION = _tickres;

            rx_config.signal_range_min_ns = 90;
            rx_config.signal_range_max_ns = 350;

            tx_config.loop_count = 0;
            config_channel_encoders();

            state.sigma = 0.1;

        }

        // internal transition
      void internalTransition(MEState& state) const override {
        // ESP_LOGI(TAG, "Hello");
      }

      // external transition
      void externalTransition(MEState& state, double e) const override {
        if(!in->empty()){
            for( const auto x : in->getBag()){
                state.data = x;
            }
        }
        ESP_LOGI(TAG, "Transmitted: %ld", state.data);
        ESP_ERROR_CHECK(rmt_transmit(tx_channel, manchester_encoder, &state.data, sizeof(uint32_t), &tx_config));
        
      }
      
      
      // output function
      void output(const MEState& state) const override {

      }

      // time_advance function
      [[nodiscard]] double timeAdvance(const MEState& state) const override {     
        //   return std::numeric_limits<double>::infinity();
        return state.sigma;
      }

    };
}

#endif