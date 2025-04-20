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

#include "extra.h"
#include "panaac.h"

namespace esphome
{
    namespace panaac
    {
        // ---------------- PanaACFanLevel ----------------

        void PanaACFanLevel::dump_config()
        {
            ESP_LOGCONFIG(TAG, "PanaACFanLevel:");
            LOG_SELECT("  Fan Level: ", "fan_level", this);
        }

        void PanaACFanLevel::control(const std::string &value)
        {
            ESP_LOGI(TAG, "Fan level selected: %s", value.c_str());

            if (value == STR_FAN_AUTO)
            {
                this->climate_->ac_state.fan_mode = climate::CLIMATE_FAN_AUTO;
                this->climate_->ac_state.fan_level = PANAAC_FAN_AUTO;
            }
            else if (value == STR_FAN_L1)
            {
                this->climate_->ac_state.fan_mode = climate::CLIMATE_FAN_LOW;
                this->climate_->ac_state.fan_level = PANAAC_FAN_LEVEL_1;
            }
            else if (value == STR_FAN_L2)
            {
                this->climate_->ac_state.fan_mode = climate::CLIMATE_FAN_LOW;
                this->climate_->ac_state.fan_level = PANAAC_FAN_LEVEL_2;
            }
            else if (value == STR_FAN_L3)
            {
                this->climate_->ac_state.fan_mode = climate::CLIMATE_FAN_MEDIUM;
                this->climate_->ac_state.fan_level = PANAAC_FAN_LEVEL_3;
            }
            else if (value == STR_FAN_L4)
            {
                this->climate_->ac_state.fan_mode = climate::CLIMATE_FAN_MEDIUM;
                this->climate_->ac_state.fan_level = PANAAC_FAN_LEVEL_4;
            }
            else if (value == STR_FAN_L5)
            {
                this->climate_->ac_state.fan_mode = climate::CLIMATE_FAN_HIGH;
                this->climate_->ac_state.fan_level = PANAAC_FAN_LEVEL_5;
            }
            else if (value == STR_FAN_QUIET)
            {
                this->climate_->ac_state.fan_mode = climate::CLIMATE_FAN_QUIET;
                this->climate_->ac_state.fan_level = PANAAC_FAN_QUIET;
            }
            else
            {
                return;
            }

            this->climate_->update_state();

        }

        void PanaACFanLevel::setup()
        {
        }

        void PanaACFanLevel::set_fanlevel(FanLevel fanlevel)
        {
            std::string value;
            switch (fanlevel)
            {
                case PANAAC_FAN_LEVEL_1:
                    value = STR_FAN_L1;
                    break;
                case PANAAC_FAN_LEVEL_2:
                    value = STR_FAN_L2;
                    break;
                case PANAAC_FAN_LEVEL_3:
                    value = STR_FAN_L3;
                    break;
                case PANAAC_FAN_LEVEL_4:
                    value = STR_FAN_L4;
                    break;
                case PANAAC_FAN_LEVEL_5:
                    value = STR_FAN_L5;
                    break;
                case PANAAC_FAN_QUIET:
                    value = STR_FAN_QUIET;
                    break;
                default:
                case PANAAC_FAN_AUTO:
                    value = STR_FAN_AUTO;
                    break;
            }

            this->publish_state(value);
        }

        // ---------------- PanaACSwingV ----------------

        void PanaACSwingV::dump_config()
        {
            ESP_LOGCONFIG(TAG, "PanaACSwingV:");
            LOG_SELECT("  Swing Vertical: ", "swingv", this);
        }

        void PanaACSwingV::control(const std::string &value)
        {
            ESP_LOGI(TAG, "Swing Vertical selected: %s", value.c_str());

            if (value == STR_SWINGV_AUTO)
            {
                this->climate_->ac_state.swing_v_pos = PANAAC_SWINGV_AUTO;
            }
            else if (value == STR_SWINGV_HIGHEST)
            {
                this->climate_->ac_state.swing_v_pos = PANAAC_SWINGV_HIGHEST;
                this->climate_->ac_state.last_swing_v_pos = PANAAC_SWINGV_HIGHEST;
            }
            else if (value == STR_SWINGV_HIGH)
            {
                this->climate_->ac_state.swing_v_pos = PANAAC_SWINGV_HIGH;
                this->climate_->ac_state.last_swing_v_pos = PANAAC_SWINGV_HIGH;
            }
            else if (value == STR_SWINGV_MIDDLE)
            {
                this->climate_->ac_state.swing_v_pos = PANAAC_SWINGV_MIDDLE;
                this->climate_->ac_state.last_swing_v_pos = PANAAC_SWINGV_MIDDLE;
            }
            else if (value == STR_SWINGV_LOW)
            {
                this->climate_->ac_state.swing_v_pos = PANAAC_SWINGV_LOW;
                this->climate_->ac_state.last_swing_v_pos = PANAAC_SWINGV_LOW;
            }
            else if (value == STR_SWINGV_LOWEST)
            {
                this->climate_->ac_state.swing_v_pos = PANAAC_SWINGV_LOWEST;
                this->climate_->ac_state.last_swing_v_pos = PANAAC_SWINGV_LOWEST;
            }
            else
            {
                return;
            }

            // swing mode
            if (this->climate_->swing_horizontal_)
            {
                if (this->climate_->ac_state.swing_v_pos == PANAAC_SWINGV_AUTO)
                {
                    if (this->climate_->ac_state.swing_h_pos == PANAAC_SWINGH_AUTO)
                    {
                        this->climate_->ac_state.swing_mode = climate::CLIMATE_SWING_BOTH;
                    }
                    else
                    {
                        this->climate_->ac_state.swing_mode = climate::CLIMATE_SWING_VERTICAL;
                    }
                }
                else
                {
                    if (this->climate_->ac_state.swing_h_pos == PANAAC_SWINGH_AUTO)
                    {
                        this->climate_->ac_state.swing_mode = climate::CLIMATE_SWING_HORIZONTAL;
                    }
                    else
                    {
                        this->climate_->ac_state.swing_mode = climate::CLIMATE_SWING_OFF;
                    }
                }
            }
            else
            {
                if (this->climate_->ac_state.swing_v_pos == PANAAC_SWINGV_AUTO)
                {
                    this->climate_->ac_state.swing_mode = climate::CLIMATE_SWING_VERTICAL;
                }
                else
                {
                    this->climate_->ac_state.swing_mode = climate::CLIMATE_SWING_OFF;
                }
            }

            this->climate_->update_state();

        }

        void PanaACSwingV::set_swingvpos(SwingVPos swingvpos)
        {
            std::string value;
            switch (swingvpos)
            {
                case PANAAC_SWINGV_HIGHEST:
                    value = STR_SWINGV_HIGHEST;
                    break;
                case PANAAC_SWINGV_HIGH:
                    value = STR_SWINGV_HIGH;
                    break;
                case PANAAC_SWINGV_MIDDLE:
                    value = STR_SWINGV_MIDDLE;
                    break;
                case PANAAC_SWINGV_LOW:
                    value = STR_SWINGV_LOW;
                    break;
                case PANAAC_SWINGV_LOWEST:
                    value = STR_SWINGV_LOWEST;
                    break;
                default:
                case PANAAC_SWINGV_AUTO:
                    value = STR_SWINGV_AUTO;
                    break;
            }

            this->publish_state(value);
        }

        void PanaACSwingV::setup()
        {
        }

        // ---------------- PanaACSwingH ----------------

        void PanaACSwingH::dump_config()
        {
            ESP_LOGCONFIG(TAG, "PanaACSwingH:");
            LOG_SELECT("  Swing Horizontal: ", "swingv", this);
        }

        void PanaACSwingH::control(const std::string &value)
        {
            ESP_LOGI(TAG, "Swing Horizontal selected: %s", value.c_str());

            if (value == STR_SWINGH_AUTO)
            {
                this->climate_->ac_state.swing_h_pos = PANAAC_SWINGH_AUTO;
            }
            else if (value == STR_SWINGH_LEFTMAX)
            {
                this->climate_->ac_state.swing_h_pos = PANAAC_SWINGH_LEFTMAX;
                this->climate_->ac_state.last_swing_h_pos = PANAAC_SWINGH_LEFTMAX;
            }
            else if (value == STR_SWINGH_LEFT)
            {
                this->climate_->ac_state.swing_h_pos = PANAAC_SWINGH_LEFT;
                this->climate_->ac_state.last_swing_h_pos = PANAAC_SWINGH_LEFT;
            }
            else if (value == STR_SWINGH_MIDDLE)
            {
                this->climate_->ac_state.swing_h_pos = PANAAC_SWINGH_MIDDLE;
                this->climate_->ac_state.last_swing_h_pos = PANAAC_SWINGH_MIDDLE;
            }
            else if (value == STR_SWINGH_RIGHT)
            {
                this->climate_->ac_state.swing_h_pos = PANAAC_SWINGH_RIGHT;
                this->climate_->ac_state.last_swing_h_pos = PANAAC_SWINGH_RIGHT;
            }
            else if (value == STR_SWINGH_RIGHTMAX)
            {
                this->climate_->ac_state.swing_h_pos = PANAAC_SWINGH_RIGHTMAX;
                this->climate_->ac_state.last_swing_h_pos = PANAAC_SWINGH_RIGHTMAX;
            }
            else
            {
                return;
            }

            // swing mode
            if (this->climate_->swing_horizontal_)
            {
                if (this->climate_->ac_state.swing_v_pos == PANAAC_SWINGV_AUTO)
                {
                    if (this->climate_->ac_state.swing_h_pos == PANAAC_SWINGH_AUTO)
                    {
                        this->climate_->ac_state.swing_mode = climate::CLIMATE_SWING_BOTH;
                    }
                    else
                    {
                        this->climate_->ac_state.swing_mode = climate::CLIMATE_SWING_VERTICAL;
                    }
                }
                else
                {
                    if (this->climate_->ac_state.swing_h_pos == PANAAC_SWINGH_AUTO)
                    {
                        this->climate_->ac_state.swing_mode = climate::CLIMATE_SWING_HORIZONTAL;
                    }
                    else
                    {
                        this->climate_->ac_state.swing_mode = climate::CLIMATE_SWING_OFF;
                    }
                }
            }
            else
            {
                if (this->climate_->ac_state.swing_v_pos == PANAAC_SWINGV_AUTO)
                {
                    this->climate_->ac_state.swing_mode = climate::CLIMATE_SWING_VERTICAL;
                }
                else
                {
                    this->climate_->ac_state.swing_mode = climate::CLIMATE_SWING_OFF;
                }
            }

            this->climate_->update_state();

        }

        void PanaACSwingH::set_swinghpos(SwingHPos swinghpos)
        {
            std::string value;

            if (swinghpos == PANAAC_SWINGH_NONE)
                return;

            switch (swinghpos)
            {
                case PANAAC_SWINGH_LEFTMAX:
                    value = STR_SWINGH_LEFTMAX;
                    break;
                case PANAAC_SWINGH_LEFT:
                    value = STR_SWINGH_LEFT;
                    break;
                case PANAAC_SWINGH_MIDDLE:
                    value = STR_SWINGH_MIDDLE;
                    break;
                case PANAAC_SWINGH_RIGHT:
                    value = STR_SWINGH_RIGHT;
                    break;
                case PANAAC_SWINGH_RIGHTMAX:
                    value = STR_SWINGH_RIGHTMAX;
                    break;
                default:
                case PANAAC_SWINGH_AUTO:
                    value = STR_SWINGH_AUTO;
                    break;
            }

            this->publish_state(value);
        }


        void PanaACSwingH::setup()
        {
        }

    } // namespace panaac
} // namespace esphome
