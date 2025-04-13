#pragma once

#include "esphome/components/select/select.h"
#include "esphome/components/climate_ir/climate_ir.h"
#include <cinttypes>
#include "definitions.h"

namespace esphome
{
    namespace panaac
    {
        class PanaACFanLevel : public select::Select, public Component
        {
        public:
            void setup() override;
            void dump_config() override;
            void control(const std::string &value) override;
            void set_parent_climate(climate_ir::ClimateIR *climate) { this->climate_ = climate; }
            void set_fanlevel(FanLevel fanlevel);

        protected:
            climate_ir::ClimateIR *climate_{nullptr};
        };

        class PanaACSwingV : public select::Select, public Component
        {
        public:
            void setup() override;
            void dump_config() override;
            void control(const std::string &value) override;
            void set_parent_climate(climate_ir::ClimateIR *climate) { this->climate_ = climate; }
            void set_swingvpos(SwingVPos swingvpos);

        protected:
            climate_ir::ClimateIR *climate_{nullptr};
        };

        class PanaACSwingH : public select::Select, public Component
        {
        public:
            void setup() override;
            void dump_config() override;
            void control(const std::string &value) override;
            void set_parent_climate(climate_ir::ClimateIR *climate) { this->climate_ = climate; }
            void set_swinghpos(SwingHPos swinghpos);

        protected:
            climate_ir::ClimateIR *climate_{nullptr};
        };
        
    }
}
