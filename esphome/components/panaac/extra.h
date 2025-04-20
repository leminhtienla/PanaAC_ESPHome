/*
 * Copyright 2025 Hoang Minh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
