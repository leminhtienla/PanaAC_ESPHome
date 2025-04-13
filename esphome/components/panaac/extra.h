#pragma once

#include "definitions.h"
#include <cinttypes>

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
            void set_parent_climate(PanaACClimate *climate) { this->climate_ = climate; }
            void set_fanlevel(FanLevel fanlevel);

        protected:
            PanaACClimate *climate_{nullptr};
        };

        class PanaACSwingV : public select::Select, public Component
        {
        public:
            void setup() override;
            void dump_config() override;
            void control(const std::string &value) override;
            void set_parent_climate(PanaACClimate *climate) { this->climate_ = climate; }
            void set_swingvpos(SwingVPos swingvpos);

        protected:
            PanaACClimate *climate_{nullptr};
        };

        class PanaACSwingH : public select::Select, public Component
        {
        public:
            void setup() override;
            void dump_config() override;
            void control(const std::string &value) override;
            void set_parent_climate(PanaACClimate *climate) { this->climate_ = climate; }
            void set_swinghpos(SwingHPos swinghpos);

        protected:
            PanaACClimate *climate_{nullptr};
        };

    } // namespace panaac
} // namespace esphome
